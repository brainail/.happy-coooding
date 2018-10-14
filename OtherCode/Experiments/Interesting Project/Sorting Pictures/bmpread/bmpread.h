#ifndef _bmpread_h_
#define _bmpread_h_

#include "image.h"
#include <fstream>

typedef unsigned char	byte;
typedef unsigned short	int16u;
typedef int				int32s;
typedef unsigned		int32u;

const int16u	BM_TYPE = 0x4d42;  // 0x42 = "B" 0x4d = "M"
const int32u	BM_RGB	= 0;

#pragma pack (push, 2)

struct file_header {
	int16u		type;
	int32u		size;
	int16u		reserved1;
	int16u		reserved2;
	int32u		offbits;
};

struct info_header {
	int32u		size;
	int32s		width;
	int32s		height;
	int16u		planes;
	int16u		bit_count;
	int32u		compression;
	int32u		size_image;
	int32s		x_pels_per_meter;
	int32s		y_pels_per_meter;
	int32u		clr_used;
	int32u		clr_important;
};

#pragma pack (pop)

typedef BGR colorx;

bool bmpread(std::istream & file, image & img) 
{
	file_header bf;
	info_header	bi;
	std::ios::pos_type pos;
	
	pos = file.tellg();
	file.read(reinterpret_cast<char *>(&bf), sizeof(bf));
	file.read(reinterpret_cast<char *>(&bi), sizeof(bi));

	if (bf.type != BM_TYPE)
		return false; //throw unsupported(unsupported::file_type, bf.type);
	if (bi.compression != BM_RGB)
		return false; //throw unsupported(unsupported::compression, bi.compression);
	if (bi.width < 0)
		return false; //throw unsupported(unsupported::width, bi.width);

	switch (bi.bit_count) {
	case 24: 
		if (bi.height < 0) {
			img.order(top_down);
			bi.height = - bi.height;
		} else
			img.order(bottom_up);
		img.resize(bi.width, bi.height, 4);
		//this check gives significant performance boost on STLport with its slow seekg(),read() combination
		if (file.tellg() != pos + std::ios::off_type(bf.offbits))
			file.seekg(pos + std::ios::off_type(bf.offbits));
		file.read(reinterpret_cast<char *>(img.data()), img.bytes());
		return true;
	default:
		return false; //throw unsupported(unsupported::bit_count, r.bi.bit_count);
	}
}

bool bmpread(const char * filename, image & img) 
{
	std::ifstream file;

	#if defined __GNUC__
	//buffer may increase IO speed in some STL implementations
	char buffer[16*1024];
	file.rdbuf()->pubsetbuf(buffer, 16*1024);
	#endif 

	file.open(filename, std::ios::in | std::ios::binary);
	bool r = bmpread(file, img);
	return r && file;
}

#endif //_bmpread_h_
