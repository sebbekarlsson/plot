#include <Color.hpp>
#include <string>

Color color_from_rgba(float r, float g, float b, float a)
{
  return { r / 255.0f, g / 255.0f, b / 255.0f, a };
}

Color color_from_hex(const char* hexvaluestr)
{
  if (hexvaluestr[0] == '#')
    hexvaluestr++;
  unsigned int hexvalue = std::stoul(hexvaluestr, nullptr, 16);
  Color rgba;
  rgba.r = ((hexvalue >> 16) & 0xFF) / 255.0; // Extract the RR byte
  rgba.g = ((hexvalue >> 8) & 0xFF) / 255.0;  // Extract the GG byte
  rgba.b = ((hexvalue)&0xFF) / 255.0;         // Extract the BB byte
  rgba.a = 1;
  return (rgba);
}
