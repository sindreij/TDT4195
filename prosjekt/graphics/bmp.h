#ifndef BMP
#define BMP

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


struct bmp_id{
  uint8_t magic1;
  uint8_t magic2;
};

struct bmp_header{
  uint32_t file_size;
  uint16_t creator1;
  uint16_t creator2;
  uint32_t pixel_offset;
};

struct bmp_dib_header{
  uint32_t header_size;
  int32_t width;
  int32_t height;
  uint16_t num_planes;
  uint16_t bit_pr_pixel;
  uint32_t compress_type;
  uint32_t data_size;
  int32_t hres;
  int32_t vres;
  uint32_t num_colors;
  uint32_t num_imp_colors;
};

unsigned char* read_bmp(char* filename){

    FILE* fp = fopen(filename, "rb");

    int width, height, offset;

    fseek(fp, 18, SEEK_SET);
    fread(&width, 4, 1, fp);
    fseek(fp, 22, SEEK_SET);
    fread(&height, 4, 1, fp);
    fseek(fp, 10, SEEK_SET);
    fread(&offset, 4, 1, fp);

    unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char)*height*width);

    fseek(fp, offset, SEEK_SET);
    fread(data, sizeof(unsigned char), height*width, fp);

    fclose(fp);

    return data;
}


#endif
