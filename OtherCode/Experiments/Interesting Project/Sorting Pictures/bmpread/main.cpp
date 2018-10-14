#include "bmpread.h"
#include <iostream>
#include <set>
using namespace std;

int main()
{
	image img;
	//if (!bmpread("1.bmp", img))
	if (!bmpread(cin, img)) //works only if cin is open in binary mode (not for Windows)
		return 1;

	cout << "Image size: " << img.width() << 'x' << img.height() << endl;

	set<BGR> colors;
	unsigned x, y;
	for (y = 0; y != img.height(); ++y)
		for (x = 0; x != img.width(); ++x)
			colors.insert(img(x,y));

	cout << "Distinct colors: " << colors.size() << endl;

	return 0;
}
