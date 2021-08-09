#include <utils.hpp>
#include <stdlib.h>


std::vector<double> linspace(double start, double end, double num)
{
  std::vector<double> linspaced;

  if (0 != num) {
    if (1 == num) {
      linspaced.push_back(static_cast<double>(start));
    } else {
      double delta = (end - start) / (num - 1);

      for (auto i = 0; i < (num - 1); ++i) {
        linspaced.push_back(static_cast<double>(start + delta * i));
      }
      // ensure that start and end are exactly the same as the input
      linspaced.push_back(static_cast<double>(end));
    }
  }
  return linspaced;
}


float* convolve(float* invec, int len, float* kernel, int K, float mix)
{

  float* outvec = (float*)calloc(len, sizeof(float));
  for (size_t i = K / 2; i < len - K / 2; ++i) {
    outvec[i] = 0.0;
    for (size_t j = 0; j < K + 1; j++) {
      outvec[i - K / 2] += invec[i - K / 2 + j] * (kernel[j] * mix);
    }
  }

  return outvec;
}


float* smoothen(float* data, int data_len, float mix) {
  float kernel[15] = { 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.5f, 0.6f, 1.0f,
  0.6f, 0.5f, 0.5f, 0.4f, 0.3f, 0.2f, 0.1f };

  return convolve(data, data_len, kernel, 15, mix);
}
