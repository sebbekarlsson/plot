#include <Font.hpp>
#include <ft2build.h>
#include <string.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <ShaderManager.hpp>
#include <algorithm>

extern ShaderManager* SHADER_MANAGER;

void draw_text(const char* text, float x, float y, float z, Color color, float scale,
               float font_size, const char* family)
{
  if (!SHADER_MANAGER)
    return;
  ShaderProgram* program = SHADER_MANAGER->set("texture");
  if (!program)
    return;

  GlyphMap* characters = get_text(text, font_size, family);
  program->bind();

  for (GlyphMap::iterator it = characters->begin(); it != characters->end(); it++) {
    Character ch = (*it);

    float xpos = x + ch.bearing.x * scale;
    float ypos = y - ((ch.size.y - ch.bearing.y)) * scale;

    float w = ch.size.x * scale;
    float h = ch.size.y * scale;

    ch.image->set_color(color);
    ch.image->set_width(w);
    ch.image->set_height(h);
    ch.image->set_x(xpos);
    ch.image->set_y(ypos);
    ch.image->set_z(z);
    ch.image->set_reversed(true);

    ch.image->draw();
    x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
                                    //
    delete ch.image;
  }

  free(characters);
  // glBindVertexArray(0);
}

GlyphMap* get_text(const char* text, float font_size, const char* family)
{
  GlyphMap* characters = new GlyphMap();
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    printf("Could not load freetype library.\n");
    return characters;
  }

  std::map<char, Character> Characters;

  size_t len = strlen(text);
  FT_Face face;
  if (FT_New_Face(ft, family, 0, &face)) {
    printf("Could not load family: %s\n", family);
    return characters;
  }
  FT_Set_Pixel_Sizes(face, 0, (int)font_size);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
                                         //
                                         //
  for (size_t i = 0; i < len; i++) {
    char c = text[i];

    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      printf("Could not load character.\n");
      return characters;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0,
                 GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    Character character = { new Image(texture),
                            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                            face->glyph->advance.x, c };
    characters->push_back(character);
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  return characters;
}

float get_text_width(GlyphMap* characters)
{
  float width = 0;
  for (GlyphMap::iterator it = characters->begin(); it != characters->end(); it++) {
    Character ch = (*it);
    float w = ch.size.x;
    width += w;
  }

  return width;
}

float get_text_height(GlyphMap* characters)
{
  std::vector<float> sizes;
  for (GlyphMap::iterator it = characters->begin(); it != characters->end(); it++) {
    Character ch = (*it);
    float h = ch.size.y;
    sizes.push_back(h);
  }

  float max_h = *std::max_element(sizes.begin(), sizes.end());
  return max_h;
}

TextMeasure get_text_measurement(const char* text, float font_size, const char* family)
{
  GlyphMap* characters = get_text(text, font_size, family);

  return (TextMeasure){ get_text_width(characters), get_text_height(characters) };
}
