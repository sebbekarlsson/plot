#ifndef EQ_GUI_SHADER_PROGRAM_H
#define EQ_GUI_SHADER_PROGRAM_H
#include <Shader.hpp>
#include <vector>
#include <glm/glm.hpp>

class ShaderProgram {
  public:
    ShaderProgram();

    void add_shader(Shader* shader);

    void compile();

    void bind();

    void set_value4f(const char* key, float a, float b, float c, float d);

    void set_valuemat4(const char* key, glm::mat4 mat);

    void unbind();

    void release_shaders();

  private:
    unsigned int program;
    unsigned int compiled;
    std::vector<Shader*> shaders;
};

#endif
