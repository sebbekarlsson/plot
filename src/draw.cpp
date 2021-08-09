#include <Font.hpp>
#include <GL/glew.h>
#include <cassert>
#include <draw.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <utils.hpp>

void draw_quad(ShaderProgram* program, float x, float y, float z, float width, float height,
               Color color)
{
  assert(program != 0);

  unsigned int VBO;
  unsigned int EBO;

  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  float w = width;
  float h = height;
  float r = 0;
  float g = 0;
  float b = 0;

  float vertices[] = {
    0.0f, 0.0f, 0.0f, r, g, b, 0.0f, 0.0f, w,    0.0f, 0.0f, r, g, b, 1.0f, 0.0f,
    w,    h,    0.0f, r, g, b, 1.0f, 1.0f, 0.0f, h,    0.0f, r, g, b, 0.0f, 1.0f
  };

  unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(x, y, z));
  program->set_valuemat4("model", model);
  program->set_value4f("color", color.r, color.g, color.b, color.a);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  // glBindVertexArray(0);
}

void draw_quad_reversed(ShaderProgram* program, float x, float y, float z, float width,
                        float height, Color color)
{
  assert(program != 0);

  unsigned int VBO;
  unsigned int EBO;

  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  float w = width;
  float h = height;
  float r = 0;
  float g = 0;
  float b = 0;

  float vertices[] = {
    0.0f, 0.0f, 0.0f, r, g, b, 0.0f, 0.0f, w,    0.0f, 0.0f, r, g, b, 1.0f, 0.0f,
    w,    -h,   0.0f, r, g, b, 1.0f, 1.0f, 0.0f, -h,   0.0f, r, g, b, 0.0f, 1.0f
  };

  unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(x, y, z));
  program->set_valuemat4("model", model);
  program->set_value4f("color", color.r, color.g, color.b, color.a);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  // glBindVertexArray(0);
}

void draw_line(ShaderProgram* program, glm::vec3 start, glm::vec3 end, Color color)
{
  assert(program != 0);

  unsigned int VBO;
  unsigned int EBO;

  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(start.x, start.y, start.z));
  program->set_valuemat4("model", model);

  program->set_value4f("color", color.r, color.g, color.b, color.a);

  // translate
  float VERTICES[] = { // positions               // colors
                       0,
                       0,
                       /*start.x, start.y,*/ start.z,
                       color.r / 255.0f,
                       color.g / 255.0f,
                       color.b / 255.0f,
                       color.a,
                       end.x,
                       end.y,
                       end.z,
                       color.r / 255.0f,
                       color.g / 255.0f,
                       color.b / 255.0f,
                       color.a
  };

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glDrawArrays(GL_LINES, 0, 3);

  // glBindVertexArray(0);
}

void draw_plot(ShaderProgram* program, Plot* plot, float x, float y, float z, Color color)
{
  assert(program != 0);

  float* data = plot->get_data();

  assert(data != 0);

  int w = plot->get_width();
  int h = plot->get_height();

  for (int x = 0; x < w; x++) {
    float y = data[x];
    draw_quad(program, x, h / 2, 0, 1, -y, color);
  }
}
