#include <BMP.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BMP::BMP(int width, int height)
  : width(width)
  , height(height)
  , gl_texture(0)
{
  this->data = (uint8_t*)malloc(3 * width * height);
  memset(this->data, 0, 3 * width * height);
}

BMP::~BMP()
{
  if (this->data)
    free(this->data);
}

BMPPixel BMP::get_pixel(int x, int y)
{
  BMPPixel px = {};

  px.red = this->data[x + y * width * 3 + 2];
  px.green = this->data[x + y * width * 3 + 1];
  px.blue = this->data[x + y * width * 3 + 0];

  return px;
}

void BMP::set_pixel(int x, int y, BMPPixel pixel)
{
  if (x > this->width - 1 || y > this->height - 1 || x < 0 || y < 0)
    return;

  this->data[(x + y * width) * 3 + 2] = pixel.red;
  this->data[(x + y * width) * 3 + 1] = pixel.green;
  this->data[(x + y * width) * 3 + 0] = pixel.blue;
}

void BMP::write(const char* filename)
{
  bmp_write(filename, this->data, this->width, this->height);
}

void bmp_write(const char* filename, uint8_t* data, int width, int height)
{
  unsigned char fileHeader[14] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 };
  unsigned char imageHeader[40] = { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };
  unsigned char bmppad[3] = { 0, 0, 0 };
  static_assert(sizeof(fileHeader) == 14, "fileHeader");
  static_assert(sizeof(imageHeader) == 40, "imageHeader");

  uint8_t filesize = 54 + 3 * width * height;

  fileHeader[2] = (unsigned char)(filesize);
  fileHeader[3] = (unsigned char)(filesize >> 8);
  fileHeader[4] = (unsigned char)(filesize >> 16);
  fileHeader[5] = (unsigned char)(filesize >> 24);

  imageHeader[4] = (unsigned char)(width);
  imageHeader[5] = (unsigned char)(width >> 8);
  imageHeader[6] = (unsigned char)(width >> 16);
  imageHeader[7] = (unsigned char)(width >> 24);
  imageHeader[8] = (unsigned char)(height);
  imageHeader[9] = (unsigned char)(height >> 8);
  imageHeader[10] = (unsigned char)(height >> 16);
  imageHeader[11] = (unsigned char)(height >> 24);

  FILE* fp = fopen(filename, "wb");

  if (fp == NULL) {
    printf("Cannot write to %s\n", filename);
    return;
  }

  fwrite(fileHeader, 1, 14, fp);
  fwrite(imageHeader, 1, 40, fp);

  for (int i = 0; i < height; i++) {
    fwrite(data + (width * (height - i - 1) * 3), 3, width, fp);
    fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, fp);
  }

  fclose(fp);

  printf("Wrote %s\n", filename);
}
