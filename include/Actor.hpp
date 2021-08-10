#ifndef PLOT_ACTOR_H
#define PLOT_ACTOR_H
#include <ShaderProgram.hpp>

class Actor {
  public:
    Actor(float x, float y);
    virtual ~Actor() {};

    virtual void draw() {};
    virtual void update() {};

    float get_x();
    float get_y();

    void set_x(float x);
    void set_y(float y);

  private:
    float x;
    float y;
};
#endif
