#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <PlotWindow.hpp>
#include <ShaderManager.hpp>
#include <draw.hpp>
#include <stdio.h>

ShaderManager* SHADER_MANAGER;

static void window_on_resize(GLFWwindow* window, int width, int height)
{
  PlotWindow* _window = reinterpret_cast<PlotWindow*>(glfwGetWindowUserPointer(window));
  _window->set_width(width);
  _window->set_height(height);
  glViewport(0, 0, width, height);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  PlotWindow* _window = reinterpret_cast<PlotWindow*>(glfwGetWindowUserPointer(window));

  Event event = {};
  event.type = EventType::MOUSE_WHEEL;
  event.dx = xoffset;
  event.dy = yoffset;
  event.x = xoffset;
  event.y = yoffset;

  _window->emit_event(event);
}

PlotWindow::PlotWindow(int width, int height)
  : width(width)
  , height(height)
  , VAO(0)
{
  projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -100.0f, 100.0f);
  view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
  if (!SHADER_MANAGER)
    SHADER_MANAGER = new ShaderManager();
}

void PlotWindow::set_width(int width)
{
  this->width = width;
}
void PlotWindow::set_height(int height)
{
  this->height = height;
}
void PlotWindow::set_background_color(Color color)
{
  this->background_color = color;
}
int PlotWindow::get_width()
{
  return width;
}

int PlotWindow::get_height()
{
  return height;
}

void PlotWindow::show()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_FLOATING, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(this->width, this->height, "Plot", NULL, NULL);

  if (window == NULL) {
    printf("Failed to show window.\n");
    glfwTerminate();
    return;
  }

  glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));

  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    return;
  }
  glfwSetFramebufferSizeCallback(window, window_on_resize);
  glfwSetScrollCallback(window, scroll_callback);

  if (!VAO) {
    glGenVertexArrays(1, &VAO);
  }

  // register shaders
  std::vector<Shader*> shaders;
  shaders.push_back(Shader::from_file(GL_VERTEX_SHADER, "assets/shaders/vertex.glsl"));
  shaders.push_back(Shader::from_file(GL_FRAGMENT_SHADER, "assets/shaders/frag.glsl"));
  SHADER_MANAGER->add_program(shaders, "color");
  shaders.clear();

  shaders.push_back(Shader::from_file(GL_VERTEX_SHADER, "assets/shaders/vertex.glsl"));
  shaders.push_back(Shader::from_file(GL_FRAGMENT_SHADER, "assets/shaders/frag_texture.glsl"));
  SHADER_MANAGER->add_program(shaders, "texture");

  SHADER_MANAGER->set("color");

  while (!glfwWindowShouldClose(window)) {
    this->update();
    this->draw();
  }

  glfwTerminate();
}

void PlotWindow::update()
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  for (std::vector<Actor*>::iterator it = actors.begin(); it != actors.end(); it++) {
    Actor* actor = *it;

    actor->update();
  }
}

void PlotWindow::draw()
{
  pre_draw();

  for (std::vector<Actor*>::iterator it = actors.begin(); it != actors.end(); it++) {
    glBindVertexArray(VAO);

    Actor* actor = *it;
    actor->draw();
  }

  post_draw();
}

void PlotWindow::pre_draw()
{
  glClearColor(background_color.r, background_color.g, background_color.b, background_color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, get_width(), get_height());
  glEnable(GL_DEPTH_TEST);

  glBindVertexArray(VAO);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  ShaderProgram* program = SHADER_MANAGER->current();

  if (!program)
    SHADER_MANAGER->set("color");

  assert(program != 0);

  program->bind();

  program->set_valuemat4("view", view);
  program->set_valuemat4("projection", projection);
}
void PlotWindow::post_draw()
{
  glfwSwapBuffers(window);
  glfwPollEvents();
}

GLFWwindow* PlotWindow::get_ptr()
{
  return window;
}

void PlotWindow::add(Actor* actor)
{
  actors.push_back(actor);
}
