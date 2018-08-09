#include "Objects/Line.hpp"

PROF::Line::Line() : model(NULL), shader(NULL) {}

PROF::Line::~Line() {
  if (model != NULL) {
    delete model;
  }
  if (shader != NULL) {
    delete shader;
  }
}

void PROF::Line::genLine() {
  if (model == NULL) {
    model = new Model();
  } else {
    delete model;
    model = new Model();
  }
  if (shader == NULL) {
    shader = new Shader();
  } else {
    delete shader;
    shader = new Shader();
  }
  shader->genShader((std::string) "./res/shaders/SolidColor.glsl");

  float verticies[6] = {-0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f};
  float normals[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

  model->genModel(verticies, normals, 6);

  addShader(shader);
  addComponent(model);
}

void PROF::Line::setColor(const float *color) {
  this->color[0] = color[0];
  this->color[1] = color[1];
  this->color[2] = color[2];
  this->color[3] = color[3];
}

void PROF::Line::setPosition(vmath::vec3 position) {
  model->setPosition(position);
}

void PROF::Line::setVelocity(vmath::vec3 velocity) {
  model->setVelocity(velocity);
}

void PROF::Line::setForce(vmath::vec3 force) { model->setForce(force); }

void PROF::Line::setScale(float scale) { model->setScale(scale); }

void PROF::Line::setSlope(float slope) {
  // use std::numeric_limits<float>::infinity() for 90 degrees
  this->slope = slope;
  model->setRotation(atan(slope) * 180.0f / (float)M_PI,
                     vmath::vec3(0.0f, 0.0f, 1.0f));
}

void PROF::Line::render() {
  for (unsigned int i = 0; i < componentCount; i++) {
    components[i]->render();
  }
  GLCall(glUniform4fv(10, 1, color));
  GLCall(glDrawArrays(GL_LINES, 0, 2));
}