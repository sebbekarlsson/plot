#ifndef PLOT_SHADER_MANAGER_H
#define PLOT_SHADER_MANAGER_H
#include <ShaderProgram.hpp>
#include <map>

class ShaderManager {
  public:
    ShaderProgram* add_program(std::vector<Shader*> shaders, const char* name);
    void push_program(ShaderProgram* program, const char* name);
    ShaderProgram* get_program(const char* name);
    ShaderProgram* current();
    ShaderProgram* set(const char* name);
    void save();
    void restore();



  private:
    ShaderProgram* prev;
    ShaderProgram* current_program;
    std::map<std::string, ShaderProgram*> programs;

};
#endif
