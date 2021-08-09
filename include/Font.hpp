#ifndef PLOT_FONT_H
#define PLOT_FONT_H
#include <Color.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <ShaderProgram.hpp>
#include <Image.hpp>

struct Character {
    Image* image;  // ID handle of the glyph texture
    glm::ivec2   size;       // Size of glyph
    glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
    long int advance;    // Offset to advance to next glyph
};

typedef std::vector<Character> GlyphMap;

void draw_text(GlyphMap* characters, float x, float y, float z, ShaderProgram* program, Color color, float scale);

GlyphMap* get_text(const char* text, float font_size, const char* family);


float get_text_width(GlyphMap* characters);
float get_text_height(GlyphMap* characters);

#endif
