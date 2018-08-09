#ifndef __PROF__
#define __PROF__

#define GLEW_STATIC

#ifdef _WIN32
#include <Windows.h>
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Colors.hpp"
#include <vmath.h>
#include "GLCall.hpp"

namespace PROF {

struct Info {
  std::string title;
  int windowWidth;
  int windowHeight;
  float aspect;
  int majorVersion;
  int minorVersion;
  int samples;
  bool fullscreen;
  bool cursor;
};

class Context {
public:
  Info info;
  GLFWwindow *window;

protected:
  static Context *context;
  
  // callback functions
  static void glfw_onResize(GLFWwindow *window, int w, int h) {
    context->onResize(w, h);
  }
  static void glfw_onKey(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
    context->onKey(key, action);
  }
  static void glfw_onMouseButton(GLFWwindow *window, int button, int action,
                                 int mods) {
    context->onMouseButton(button, action);
  }
  static void glfw_onMouseMove(GLFWwindow *window, double x, double y) {
    context->onMouseMove(x, y);
  }
  static void glfw_onMouseWheel(GLFWwindow *window, double xoffset,
                                double yoffset) {
    context->onMouseWheel(yoffset);
  }

public:
  Context() {}
  virtual ~Context() {}
  virtual void run(Context *selfPtr) {
    // running context
    bool running = true;
    context = selfPtr;
    // glfw initialization
    if (!glfwInit()) {
      std::cout << "GLFW failed to initialize\n";
      return;
    }
    // context info setup
    init();
    // glfw window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info.majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info.minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, info.samples);
    // create window
    window = glfwCreateWindow(
        info.windowWidth, info.windowHeight, info.title.c_str(),
        info.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (!window) {
      std::cout << "Failed to open window\n";
      return;
    }
    // set current context
    glfwMakeContextCurrent(window);
    // set callback functions
    glfwSetWindowSizeCallback(window, glfw_onResize);
    glfwSetKeyCallback(window, glfw_onKey);
    glfwSetMouseButtonCallback(window, glfw_onMouseButton);
    glfwSetCursorPosCallback(window, glfw_onMouseMove);
    glfwSetScrollCallback(window, glfw_onMouseWheel);
    // show cursor?
    if (!info.cursor) {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    // glew initialization
    if (glewInit() != GLEW_OK) {
      std::cout << "GLEW failed to initialize" << std::endl;
    }
    // startup
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    startup();
    // render
    while (running) {
      render(glfwGetTime());
      glfwSwapBuffers(window);
      glfwPollEvents();
      running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
      running &= (glfwWindowShouldClose(window) != GL_TRUE);
    }
    // shutdown and cleanup
    shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
  }
  virtual void init() {
    info.title = "Untitled";
    info.windowWidth = 1280;
    info.windowHeight = 720;
    info.aspect = (float)info.windowWidth / (float)info.windowHeight;
    info.majorVersion = 4;
    info.minorVersion = 5;
    info.samples = 0;
    info.fullscreen = false;
    info.cursor = true;
  }
  virtual void startup() {}
  virtual void render(double currentTime) {}
  virtual void shutdown() {}
  void setWindowTitle(const char *title) { glfwSetWindowTitle(window, title); }
  virtual void onResize(int w, int h) {
    info.windowWidth = w;
    info.windowHeight = h;
  }
  virtual void onKey(int key, int action) {}
  virtual void onMouseButton(int button, int action) {}
  virtual void onMouseMove(double x, double y) {}
  virtual void onMouseWheel(double pos) {}
};
} // namespace PROF
#endif //__PROF__