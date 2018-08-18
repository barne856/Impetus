#include "Objects/Arrow.hpp"

PROF::Arrow::Arrow() : solidColor(NULL), arrowModel(NULL) {}

PROF::Arrow::~Arrow() {
  if (arrowModel != NULL) {
    delete arrowModel;
  }
  if (solidColor != NULL) {
    delete solidColor;
  }
}

void PROF::Arrow::genArrow(float angle, float length, float width,
                           float weight) {
  if (arrowModel == NULL) {
    arrowModel = new Model();
  } else {
    delete arrowModel;
    arrowModel = new Model();
  }
  if (solidColor == NULL) {
    solidColor = new Shader();
  } else {
    delete solidColor;
    solidColor = new Shader();
  }
  std::string shaderFilepath = "./res/shaders/SolidColor.glsl";
  solidColor->genShader(shaderFilepath);
  addShader(solidColor);

  count = 45;

  float l1 = 1.0f;
  float l2 = length;
  float l3 = width * weight;
  float l4 = width;

  float vertices[45]{
      -0.5f,
      -0.5f * l3,
      0.0f,
      -0.5f,
      0.5f * l3,
      0.0f,
      l2 - 0.5f,
      0.5f * l3,
      0.0f,

      -0.5f,
      -0.5f * l3,
      0.0f,
      l2 - 0.5f,
      0.5f * l3,
      0.0f,
      l2 - 0.5f,
      -0.5f * l3,
      0.0f,

      l2 - 0.5f,
      0.5f * l3,
      0.0f,
      0.5f,
      0.0f,
      0.0,
      l2 - 0.5f,
      -0.5f * l3,
      0.0f,

      0.5f,
      0.0f,
      0.0,
      l2 - 0.5f,
      0.5f * l3,
      0.0f,
      l2 - 0.5f - (0.5f * (l4 - l3)) / tan(angle * (float)M_PI / 180.0f),
      0.5f * l4,
      0.0f,

      0.5f,
      0.0f,
      0.0,
      l2 - 0.5f - (0.5f * (l4 - l3)) / tan(angle * (float)M_PI / 180.0f),
      -0.5f * l4,
      0.0f,
      l2 - 0.5f,
      -0.5f * l3,
      0.0f};

  float normals[45]{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

  arrowModel->genModel(vertices, normals, count);
  addComponent(arrowModel);
}

void PROF::Arrow::setColor(const float *color) {
  colorUniform[0] = color[0];
  colorUniform[1] = color[1];
  colorUniform[2] = color[2];
  colorUniform[3] = color[3];
}

void PROF::Arrow::setPosition(vmath::vec3 position) {
  arrowModel->setPosition(position);
}

void PROF::Arrow::setVelocity(vmath::vec3 velocity) {
  arrowModel->setVelocity(velocity);
}

void PROF::Arrow::setForce(vmath::vec3 force) { arrowModel->setForce(force); }

void PROF::Arrow::setScale(float scale) { arrowModel->setScale(scale); }

void PROF::Arrow::setAngle(float angle) {
  this->angle = angle;
  arrowModel->setRotation(angle, vmath::vec3(0.0f, 0.0f, 1.0f));
}

void PROF::Arrow::render() {
  for (unsigned int i = 0; i < componentCount; i++) {
    components[i]->render();
  }
  GLCall(glUniform4fv(11, 1, colorUniform));
  GLCall(glDrawArrays(GL_TRIANGLES, 0, count / 3));
}