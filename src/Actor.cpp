#include <Actor.hpp>


Actor::Actor(float x, float y): x(x), y(y) {}

float Actor::get_x() { return x; }
float Actor::get_y() {  return y; }

void Actor::set_x(float x) { this->x = x; }
void Actor::set_y(float y) { this->y = y; }


void Actor::set_shader_program(ShaderProgram* program) { this->program = program; }
ShaderProgram* Actor::get_shader_program() { return program; }
