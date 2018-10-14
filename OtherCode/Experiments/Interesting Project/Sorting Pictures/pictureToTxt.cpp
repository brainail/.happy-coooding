#include <stdio.h>

typedef unsigned char   byte;
typedef unsigned short  int16u;
typedef int             int32s;
typedef unsigned        int32u;


#pragma pack (push, 2)
struct file_header {
    int16u              type;
    int32u              size;
    int16u              reserved1;
    int16u              reserved2;
    int32u              offbits;
} bf;

struct info_header {
    int32u              size;
    int32s              width;
    int32s              height;
    int16u              planes;
    int16u              bit_count;
    int32u              compression;
    int32u              size_image;
    int32s              x_pels_per_meter;
    int32s              y_pels_per_meter;
    int32u              clr_used;
    int32u              clr_important;
} bi;
#pragma pack (pop)

int main()
{
//    FILE *f = fopen("a.bmp", "r");    
    FILE *f = stdin;
    long w, h, W,H;

    fread(&bf, sizeof(bf), 1, f);
    printf("Header size = %u (bytes)\n",  bf.size);
    
    fread(&bi, sizeof(bi), 1, f);
    printf("Image size = %d x %d \n", bi.width, bi.height);

    W = bi.width; 
    H = bi.height;
    
    byte color[3];
    
    for(h = 0; h < H; h++)
    {
        for(w = 0; w < W; w++)
        {
            fread(color, 3, 1, f);
            printf("%02x%02x%02x ", color[0], color[1], color[2]);
        }
        printf("\n");
        if(W%4) fread(color, W%4, 1, f);
    }

    return 0;
}
