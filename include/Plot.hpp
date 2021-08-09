#ifndef PLOT_H
#define PLOT_H
#include <BMP.h>
#include <pthread.h>
#include <Actor.hpp>
#include <Font.hpp>

class Plot: public Actor {
  public:
    Plot(float x, float y, int width, int height);
    Plot(int width, int height);

    void set_data(float* data, int len);
    void save(const char* filename);
    void compute();
    void show();
    void close();

    int get_width();
    int get_height();

    BMP* get_bitmap();

    float* get_data();

    int get_og_data_len();

    void draw();

    void update();

  private:
    float* data;
    float* computed_data;
    int len;
    int width;
    int height;
    BMP* bmp;
    pthread_t t;
    std::vector<GlyphMap*> x_text;
    std::vector<GlyphMap*> y_text;
};


#endif
