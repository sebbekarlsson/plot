#include <Plot.hpp>
#include <cmath>
#include <perlin.h>

#define DATA_LEN 3000

int main(int argc, char* argv[])
{

  // Generate some data
  float data[DATA_LEN];
  for (int i = 0; i < DATA_LEN; i++) {
    data[i] = 0;
  }

  Plot* plot = new Plot(1080, 720);
  plot->set_data(data, DATA_LEN);
  plot->compute();
  plot->save("plot.bmp"); // can be saved as .bmp if you want
  plot->show();           // opens up a real-time window of your plot

  plot->set_smooth(false);

  // Update the plot information while the plot window is showing.
  // The plot will be updated in real-time.
  float k = 0;
  while (1) {
    for (int i = 0; i < DATA_LEN; i++) {
      data[i] = (perlin_get2d(k, i, 0.1f, 1, 23422));
    }

    plot->set_data(data, DATA_LEN);
    plot->compute();

    k += 0.003f;
  }

  delete plot;

  return 0;
}
