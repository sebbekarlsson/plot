#ifndef EQ_WINDOW_H
#define EQ_WINDOW_H
#include <GLFW/glfw3.h>
#include <Color.hpp>
#include <ShaderProgram.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include <vector>
#include <Actor.hpp>
#include <EventEmiter.hpp>


class PlotWindow : public EventEmiter {
  public:
    PlotWindow(int width, int height);

    int get_width();
    int get_height();
    GLFWwindow* get_ptr();

    void set_width(int width);
    void set_height(int height);
    void set_background_color(Color color);

    void show();

    void update();

    void draw();

    void add(Actor* actor);

  private:

    void pre_draw();
    void post_draw();


    int width;
    int height;
    unsigned int VAO;
    GLFWwindow* window;
    Color background_color;
    glm::mat4 projection;
    glm::mat4 view;

    std::vector<Actor*> actors;

};
#endif
