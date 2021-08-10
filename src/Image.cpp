#include <Actor.hpp>
#include <GL/glew.h>
#include <Image.hpp>
#include <ShaderManager.hpp>
#include <ShaderProgram.hpp>
#include <draw.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>
extern ShaderManager* SHADER_MANAGER;

Image::Image(unsigned int id)
  : id(id)
  , x(0)
  , y(0)
  , color({ 1, 1, 1, 1 })
  , reversed(false)
{}

Image::~Image()
{
  if (id) {
    glDeleteTextures(1, &id);
  }
}

void Image::bind()
{
  glBindTexture(GL_TEXTURE_2D, id);
}

void Image::unbind()
{
  glBindTexture(GL_TEXTURE_2D, 0);
};

Image* Image::from_file(const char* filepath)
{
  /**
   * Texture will be stored in this unsigned integer.
   */

  unsigned int id;

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  png_image image = {};
  image.version = PNG_IMAGE_VERSION;

  if (!png_image_begin_read_from_file(&image, filepath))
    fprintf(stderr, "Could not read file `%s`: %s\n", filepath, image.message);

  image.format = PNG_FORMAT_RGBA;

  uint32_t* image_pixels = (uint32_t*)malloc(sizeof(uint32_t) * image.width * image.height);
  if (image_pixels == NULL)
    fprintf(stderr, "Could not allocate memory for an image\n");

  if (!png_image_finish_read(&image, NULL, image_pixels, 0, NULL))
    fprintf(stderr, "libpng error: %s\n", image.message);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               image_pixels);

  glGenerateMipmap(GL_TEXTURE_2D);

  Image* img = new Image(id);
  img->set_width(image.width);
  img->set_height(image.height);

  return img;
}

unsigned int Image::get_id()
{
  return this->id;
}

float Image::get_x()
{
  return x;
}
float Image::get_y()
{
  return y;
}
float Image::get_z()
{
  return z;
}

void Image::set_x(float x)
{
  this->x = x;
}
void Image::set_y(float y)
{
  this->y = y;
}
void Image::set_z(float z)
{
  this->z = z;
}

void Image::draw()
{
  ShaderProgram* program = SHADER_MANAGER->current();

  assert(program != 0);

  this->bind();
  program->bind();
  program->set_value4f("color", color.r, color.g, color.b, color.a);

  if (reversed) {
    draw_quad_reversed(this->get_x(), this->get_y(), this->get_z(), this->get_width(),
                       this->get_height(), { 255, 255, 255, 1 });
  } else {
    draw_quad(this->get_x(), this->get_y(), this->get_z(), this->get_width(), this->get_height(),
              { 255, 255, 255, 1 });
  }
  this->unbind();
}

float Image::get_width()
{
  return width;
}
float Image::get_height()
{
  return height;
}

void Image::set_width(float w)
{
  width = w;
}
void Image::set_height(float h)
{
  height = h;
}

void Image::set_color(Color color)
{
  this->color = color;
}

void Image::set_reversed(bool reversed)
{
  this->reversed = reversed;
}
