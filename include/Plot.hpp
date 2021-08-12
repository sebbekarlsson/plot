#ifndef PLOT_H
#define PLOT_H
#include <BMP.h>
#include <pthread.h>
#include <Actor.hpp>
#include <Font.hpp>
#include <functional>


typedef std::function<int(int pre, int post)> IndexModifierFunction;

class Plot: public Actor {
  public:
    Plot(float x, float y, int width, int height);
    Plot(int width, int height);
    ~Plot();

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

    void set_scale(float scale);
    float get_scale();

    void set_smooth(bool smooth);

    void set_index_modifier(IndexModifierFunction index_modifier);

    void update();

    private:
    bool smooth;
    float scale;
    float* data;
    float* computed_data;
    float peak;
    float bottom;
    int len;
    int width;
    int height;
    BMP* bmp;
    pthread_t t;
    IndexModifierFunction index_modifier;
};


#endif
