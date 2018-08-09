#include "Modules/Camera.hpp"

PROF::Camera::Camera()
    : aspect(16.0f / 9.0f), fovy(60.0f),
      type(Camera2D) {
  setPosition(vmath::vec3(0.0f, 0.0f, 1.0f));
  center = vmath::vec3(0.0f);
  up = vmath::vec3(0.0f, 1.0f, 0.0f);
  projection = vmath::ortho(-aspect, aspect, -1.0f, 1.0f, 0.0001f, 10000.0f);
}

PROF::Camera::~Camera() {}

void PROF::Camera::setView3D() {
  projection = vmath::perspective(fovy, aspect, 0.0001f, 10000.0f);
  type = Camera3D;
}

void PROF::Camera::setView2D() {
  projection = vmath::ortho(-aspect, aspect, -1.0f, 1.0f, 0.0001f, 10000.0f);
  type = Camera2D;
}

void PROF::Camera::setLookat(vmath::vec3 eye, vmath::vec3 center,
                            vmath::vec3 up) {
  setPosition(eye);
  this->center = center;
  this->up = up;
}

void PROF::Camera::setAspect(float aspect) {
  this->aspect = aspect;
  if (type == Camera2D) {
    projection = vmath::ortho(-aspect, aspect, -1.0f, 1.0f, 0.0001f, 10000.0f);
  } else if (type = Camera3D) {
    projection = vmath::perspective(fovy, aspect, 0.0001f, 10000.0f);
  }
}

void PROF::Camera::setFOVy(float fovy) {
  this->fovy = fovy;
  if (type == Camera2D) {
    projection = vmath::ortho(-aspect, aspect, -1.0f, 1.0f, 0.0001f, 10000.0f);
  } else if (type = Camera3D) {
    projection = vmath::perspective(fovy, aspect, 0.0001f, 10000.0f);
  }
}

void PROF::Camera::render(GLuint programID) {
  update();
  GLCall(glUseProgram(programID));
  GLCall(glUniformMatrix4fv(
      3, 1, GL_FALSE, vmath::lookat(position, center, up)));
  GLCall(glUniformMatrix4fv(4, 1, GL_FALSE, projection));
}