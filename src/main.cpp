#include <Plot.hpp>
#include <cmath>

#define DATA_LEN 400


int main(int argc, char* argv[])
{
  float data[DATA_LEN];


  for (int i = 0; i < DATA_LEN; i++) {
    data[i] = cos((float)i/24.0f);
  }

  Plot* plot = new Plot(640, 480);
  plot->set_data(data, DATA_LEN);
  plot->compute();
  //plot->save("plot.bmp");

  plot->show();

  float k = 0;
  while(1) {
    for (int i = 0; i < DATA_LEN; i++) {
      data[i] = cos((float)(k+i)/24.0f);
    }

    plot->set_data(data, DATA_LEN);
    plot->compute();

    k += 0.003f;
  };

  return 0;
}
