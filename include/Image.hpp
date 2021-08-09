#ifndef PLOT_IMAGE_HPP
#define PLOT_IMAGE_HPP
#include <png.h>
#include <Color.hpp>
#include <ShaderProgram.hpp>


class Image  {
  public:
    Image(unsigned int id);

    static Image* from_file(const char* filepath);

    unsigned int get_id();

    void bind();

    void draw();

    void unbind();

    float get_x();
    float get_y();
        float get_z();

        void set_reversed(bool reversed);

    float get_width();
    float get_height();

    void set_color(Color color);

    void set_width(float w);
    void set_height(float h);

    void set_x(float x);
    void set_y(float y);
    void set_z(float z);

    void set_shader_program(ShaderProgram* program);

  private:
    unsigned int id;
    float x;
    float y;
    float z;
    float width;
    float height;
        Color color;
    bool reversed;
    ShaderProgram* program;
};

#endif
