#include <ShaderManager.hpp>

ShaderProgram* ShaderManager::add_program(std::vector<Shader*> shaders, const char* name)
{
  ShaderProgram* program = new ShaderProgram();

  for (std::vector<Shader*>::iterator it = shaders.begin(); it != shaders.end(); it++)
    program->add_shader(*it);

  this->programs.insert({ std::string(name), program });
  return program;
}

void ShaderManager::push_program(ShaderProgram* program, const char* name)
{
  this->programs[std::string(name)] = program;
}

ShaderProgram* ShaderManager::get_program(const char* name)
{
  if (programs.find(std::string(name)) == programs.end()) {
    printf("Could not find ShaderProgram: %s\n", name);
    return 0;
  }

  ShaderProgram* program = programs[std::string(name)];
  if (program == 0) {
    printf("Could not find ShaderProgram: %s\n", name);
    return 0;
  }

  program->compile();

  return program;
}

ShaderProgram* ShaderManager::current()
{
  return current_program;
}

ShaderProgram* ShaderManager::set(const char* name)
{
  ShaderProgram* program = ShaderManager::get_program(name);
  assert(program != 0);

  if (program) {
    program->bind();
    current_program = program;
  }

  return program;
}

void ShaderManager::save()
{
  this->prev = current_program;
}
void ShaderManager::restore()
{
  this->current_program = prev;
}
