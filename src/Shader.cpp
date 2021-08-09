#include <GL/glew.h>
#include <Shader.hpp>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Shader::Shader(int type, char* source)
  : type(type)
  , id(0)
{
  this->source = source;
}

void Shader::load()
{
  id = glCreateShader(type);
}

void Shader::compile()
{
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);

  int success;
  char infoLog[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(id, 512, NULL, infoLog);
    printf("Error compiling shader: %s\n", infoLog);
  }
}

unsigned int Shader::get_id()
{
  return this->id;
}

Shader* Shader::from_file(int type, const char* filepath)
{
  std::ifstream ifs(filepath);
  std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

  return new Shader(type, strdup(content.c_str()));
}

void Shader::release()
{
  glDeleteShader(id);
}
