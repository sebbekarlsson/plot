#ifndef EQ_GUI_DRAW_H
#define EQ_GUI_DRAW_H
#include <ShaderProgram.hpp>
#include <Color.hpp>
#include <Plot.hpp>

void draw_quad(float x, float y, float z, float width, float height, Color color);
void draw_quad_reversed(float x, float y, float z, float width, float height, Color color);
void draw_line(glm::vec3 start, glm::vec3 end, Color color);

void draw_plot(Plot* plot, float x, float y, float z, Color color);
#endif
