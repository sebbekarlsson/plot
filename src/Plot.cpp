#include <Plot.hpp>
#include <PlotWindow.hpp>
#include <ShaderManager.hpp>
#include <draw.hpp>
#include <stdio.h>
#include <utils.hpp>

extern ShaderManager* SHADER_MANAGER;

Plot::Plot(float x, float y, int width, int height)
  : Actor(x, y)
  , smooth(false)
  , scale(8)
  , data(0)
  , computed_data(0)
  , peak(0)
  , bottom(0)
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
  , smooth(false)
  , scale(8)
  , data(0)
  , len(0)
  , width(width)
  , height(height)
  , t(0)
{
  this->bmp = new BMP(width, height);
  this->computed_data = (float*)calloc(width + 1, sizeof(float));
}

Plot::~Plot()
{
  if (this->bmp)
    delete this->bmp;
  if (this->computed_data)
    free(this->computed_data);
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
  float* data_to_use = (smooth && data) ? smoothen(data, len, 1) : data;

  float new_peak = largest<float>(data_to_use, len);

  if (new_peak > peak)
    peak = new_peak;

  bottom = smallest<float>(data_to_use, len);

  for (int i = 0; i < width; i++) {
    int data_index = (int)(((float)i / (float)width) * (float)len);


    data_index = index_modifier ? index_modifier(i, data_index) : data_index;

    float value = (data_to_use[data_index] / peak) * ((float)height / scale);

    bmp->set_pixel(i, height - value, { 255, 0, 0 });
    computed_data[i] = value;
  }

  if (smooth && data_to_use) {
    free(data_to_use);
  }
}

void Plot::save(const char* filename)
{
  bmp->write(filename);
}

float Plot::get_scale()
{
  return scale;
}

void* plot_thread(void* ref)
{

  Plot* plot = (Plot*)ref;

  PlotWindow* window = new PlotWindow(plot->get_width(), plot->get_height());

  window->add_eventlistener(EventType::MOUSE_WHEEL, ([plot](Event event) {
                              plot->set_scale(
                                std::max(2.0f, plot->get_scale() + (event.dy * 0.5f)));
                            }));

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

void Plot::set_scale(float scale)
{
  this->scale = std::max<float>(1, scale);
}

void Plot::draw()
{
  draw_plot(this, get_x(), get_y(), 2.0f, { 255, 0, 0 });

  int inc = 10;
  const char* family = "assets/font/VT323-Regular.ttf";
  float font_size = 14;

  // draw X
  for (int i = 0; i < (float)width / inc; i += inc) {
    char text[128];
    sprintf(text, "%1.2f", ((float)(i * inc) / (float)width) * len);
    TextMeasure measure = get_text_measurement(text, font_size, family);
    float x = (i * inc);
    int y = get_height() - measure.height;
    float c_w = measure.width;

    SHADER_MANAGER->set("color");
    draw_quad(x, get_height(), 0.0f, 1, -get_height(),
              { 48.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f });

    draw_text(text, x - (c_w / 2), y, 3.0f, { 255, 255, 255 }, 1, font_size, family);
  }

  // draw Y
  for (float i = -height / scale; i < height / scale; i += inc) {
    char text[128];
    float value = ((i / ((float)height / scale)) * peak) * -1.0f;
    sprintf(text, "%1.2f", value);
    TextMeasure measure = get_text_measurement(text, font_size, family);
    float x = font_size;
    float y = (height / 2) + i;

    SHADER_MANAGER->set("color");
    draw_quad(x, y, 1.0f, get_width(), 1, { 48.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f });

    draw_text(text, x - (font_size / 2), y + (measure.height / 2), 3.0f, { 255, 255, 255 }, 1,
              font_size, family);
  }
}

void Plot::update() {}

void Plot::set_smooth(bool smooth)
{
  this->smooth = smooth;
}


void Plot::set_index_modifier(IndexModifierFunction index_modifier) {
  this->index_modifier = index_modifier;
}
