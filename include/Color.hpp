#ifndef EQ_GUI_COLOR_H
#define EQ_GUI_COLOR_H
struct Color {
  float r;
  float g;
  float b;
  float a;
};

Color color_from_rgba(float r, float g, float b, float a);

Color color_from_hex(const char* hexvaluestr);

#define COLOR(r, g, b, a)                       \
  color_from_rgba(r, g, b, a)


#define COLORHEX(hexvaluestr)                   \
  color_from_hex(hexvaluestr)



#define COLOR_WHITE "#FFFFFF"
#define COLOR_BG_LIGHT "#dfe6e9"
#define COLOR_BG_LIGHT_DARK "#636e72"
#define COLOR_BG_LIGHT_DARK_LIGHT "#b2bec3"

#endif
