#include <GL/glew.h>
#include <ShaderProgram.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

ShaderProgram::ShaderProgram()
  : program(0)
{}

void ShaderProgram::add_shader(Shader* shader)
{
  this->shaders.push_back(shader);
}

void ShaderProgram::compile()
{
  printf("Compiling shader program %p\n", this);

  program = glCreateProgram();

  for (Shader*& shader : this->shaders) {
    shader->load();
    shader->compile();
    glAttachShader(program, shader->get_id());
  }

  glLinkProgram(program);

  int success;
  char infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    printf("Error compiling shader program: %s\n", infoLog);
    return;
  }

  printf("Done compiling shader %p\n", this);
}

void ShaderProgram::bind()
{
  glUseProgram(program);
  release_shaders();
}

void ShaderProgram::unbind()
{
  glUseProgram(0);
}

void ShaderProgram::release_shaders()
{
  for (Shader*& shader : this->shaders) {
    shader->release();
  }
}

void ShaderProgram::set_value4f(const char* key, float a, float b, float c, float d)
{
  glUniform4f(glGetUniformLocation(program, key), a, b, c, d);
}

void ShaderProgram::set_valuemat4(const char* key, glm::mat4 mat)
{
  glUniformMatrix4fv(glGetUniformLocation(program, key), 1, GL_FALSE, glm::value_ptr(mat));
}
