#include <iostream>
#include <set>

using namespace std;


typedef unsigned char	byte;
typedef unsigned short	int16u;
typedef int		int32s;
typedef unsigned	int32u;

const int16u	BM_TYPE = 0x4d42;  // 0x42 = "B" 0x4d = "M"
const int32u	BM_RGB	= 0;

#pragma pack (push,2)
struct file_header {
	int16u		type;
	int32u		size;
	int16u		reserved1;
	int16u		reserved2;
	int32u		offbits;
} bf;

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
} bi;
#pragma pack (pop)


int main()
{


    cin.read((char *)&bf, sizeof(bf));
    cin.read((char *)&bi, sizeof(bi));

    cout << "Width=" << bi.width << " Height=" << bi.height << endl;

    if (bf.type != BM_TYPE)
        return 1; //throw unsupported(unsupported::file_type, bf.type);
    if (bi.compression != BM_RGB)
	return 2; //throw unsupported(unsupported::compression, bi.compression);
    
    long color = 0;;
    byte brg[3];
    set<long> colors;
    
    long w, h;
    for(h = 0; h < bi.height; h++)
    {
        for(w = 0; w < bi.width ; w++)
        {
            cin.read((char *)brg, 3);
            colors.insert( brg[0] + 256*brg[1] + 256*256*brg[2]);
        }
        if(bi.width % 4) cin.read((char*)brg, bi.width%4);
    }
    cout << "Distinct colors: " << colors.size() << endl;
    return 0;
}
