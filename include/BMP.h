#ifndef BMP_H
#define BMP_H
#include <stdint.h>

typedef struct BMP_PIXEL {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} BMPPixel;

class BMP {
 public:
  BMP(int width, int height);

  ~BMP();

  void set_pixel(int x, int y, BMPPixel pixel);
  BMPPixel get_pixel(int x, int y);
  void write(const char* filename);

 private:
  int width;
  int height;
  uint8_t* data;
  unsigned int gl_texture;
};

void bmp_write(const char* filename, uint8_t* data, int width, int height);

#endif
