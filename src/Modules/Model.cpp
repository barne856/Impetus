#include "Modules/Model.hpp"

PROF::Model::Model()
    : count(0), modelMatrix(vmath::mat4::identity()),
      rotation(vmath::mat4::identity()), translation(vmath::mat4::identity()),
      scaleMatrix(vmath::mat4::identity()) {}

PROF::Model::~Model() {}

void PROF::Model::genModel(float *vertices, float *normals, unsigned int count) {
  this->count = count;
  GLCall(glGenVertexArrays(1, &vertexArray));
  GLCall(glBindVertexArray(vertexArray));
  GLCall(glGenBuffers(1, &vertexBuffer));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
  GLCall(
      glBufferStorage(GL_ARRAY_BUFFER, sizeof(float) * count, vertices, NULL));
  GLCall(glVertexArrayAttribBinding(vertexArray, 0, 0));
  GLCall(glVertexArrayVertexBuffer(vertexArray, 0, vertexBuffer, 0,
                                   3 * sizeof(float)));
  GLCall(glVertexArrayAttribFormat(vertexArray, 0, 3, GL_FLOAT, GL_FALSE, 0));
  GLCall(glEnableVertexArrayAttrib(vertexArray, 0));

  GLCall(glGenBuffers(1, &normalBuffer));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, normalBuffer));
  GLCall(
      glBufferStorage(GL_ARRAY_BUFFER, sizeof(float) * count, normals, NULL));
  GLCall(glVertexArrayAttribBinding(vertexArray, 1, 1));
  GLCall(glVertexArrayVertexBuffer(vertexArray, 1, normalBuffer, 0,
                                   3 * sizeof(float)));
  GLCall(glVertexArrayAttribFormat(vertexArray, 1, 3, GL_FLOAT, GL_FALSE, 0));
  GLCall(glEnableVertexArrayAttrib(vertexArray, 1));
}

void PROF::Model::updateModelMatrix() {
  update();
  translation = vmath::translate(position);
  modelMatrix = translation * rotation * scaleMatrix;
  GLCall(glUniformMatrix4fv(2, 1, GL_FALSE, modelMatrix));
}

void PROF::Model::setRotation(float angle, vmath::vec3 axis) {
  rotation = vmath::rotate(angle, axis);
}

void PROF::Model::setScale(float scale) {
  scaleMatrix = vmath::scale(vmath::vec3(scale));
}

void PROF::Model::Bind() const {
  GLCall(glBindVertexArray(vertexArray));
}

void PROF::Model::render() {
  Bind();
  updateModelMatrix();
}