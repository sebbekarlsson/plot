#ifndef PLOT_UTILS_H
#define PLOT_UTILS_H
#include <vector>



float* convolve(float* invec, int len, float* kernel, int K, float mix);
float* smoothen(float* data, int data_len, float mix);

std::vector<double> linspace(double start, double end, double numi);

  template<typename T>
T largest(T* arr, int len)
{
  T max = arr[0];
  for (int i = 1; i < len; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  return max;
}
#endif
