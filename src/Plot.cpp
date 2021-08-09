#include <Plot.hpp>
#include <PlotWindow.hpp>
#include <draw.hpp>
#include <stdio.h>
#include <utils.hpp>

Plot::Plot(float x, float y, int width, int height)
  : Actor(x, y)
  , data(0)
  , len(0)
  , width(width)
  , height(height)
  , t(0)
{
  this->bmp = new BMP(width, height);
  this->computed_data = (float*)calloc(width + 1, sizeof(float));
}

Plot::Plot(int width, int height)
  : Actor(0, 0)
  , data(0)
  , len(0)
  , width(width)
  , height(height)
  , t(0)
{
  this->bmp = new BMP(width, height);
  this->computed_data = (float*)calloc(width + 1, sizeof(float));
}

void Plot::set_data(float* data, int len)
{
  this->data = data;

  this->len = len;
}

int Plot::get_width()
{
  return width;
}

int Plot::get_height()
{
  return height;
}

BMP* Plot::get_bitmap()
{
  return bmp;
}

void Plot::compute()
{
  float peak = largest<float>(data, len);

  for (int i = 0; i < width; i++) {
    int data_index = (int)(((float)i / (float)width) * (float)len);
    float value = (data[data_index] / peak) * ((float)height / 8.0f);

    bmp->set_pixel(i, height - value, { 255, 0, 0 });
    computed_data[i] = value;
  }
}

void Plot::save(const char* filename)
{
  bmp->write(filename);
}

void* plot_thread(void* ref)
{

  Plot* plot = (Plot*)ref;

  PlotWindow* window = new PlotWindow(plot->get_width(), plot->get_height());
  window->add(plot);
  window->show();

  return 0;
}

void Plot::show()
{
  if (t)
    pthread_join(t, 0);

  if (pthread_create(&t, 0, plot_thread, this)) {
    printf("Error creating plot thread.\n");
    return;
  }
}

void Plot::close() {}

float* Plot::get_data()
{
  return this->computed_data;
}

int Plot::get_og_data_len()
{
  return len;
}

void Plot::draw()
{
  draw_plot(this->program, this, get_x(), get_y(), 0, { 255, 0, 0 });

  // TODO: Draw x, y text
}

void Plot::update() {}
