#include "Modules/Object.hpp"

int PROF::Object::uniqueAssignment = 0;

PROF::Object::Object() : componentCount(0), renderable(false), isActive(true) {
  uniqueAssignment++;
  ID = uniqueAssignment;
  components = new Component *[0];
  objectShader = NULL;
}

PROF::Object::Object(const Object &object) {
  componentCount = object.componentCount;
  renderable = object.renderable;
  isActive = object.isActive;
  objectShader = object.objectShader;
  ID = object.ID;
  components = new Component *[componentCount];
  for (unsigned int i = 0; i < componentCount; i++) {
    components[i] = object.components[i];
  }
}

PROF::Object &PROF::Object::operator=(const Object &object) {
  // check for self assignment
  if (this == &object) {
    return *this;
  }

  componentCount = object.componentCount;
  renderable = object.renderable;
  isActive = object.isActive;
  objectShader = object.objectShader;
  ID = object.ID;
  delete[] components;
  components = new Component *[componentCount];
  for (unsigned int i = 0; i < componentCount; i++) {
    components[i] = object.components[i];
  }
  return *this;
}

PROF::Object::~Object() { delete[] components; }

void PROF::Object::addComponent(Component* component) {
  for (unsigned int i = 0; i < componentCount; i++) {
    if (component->getID() == components[i]->getID()) {
      std::cout << "Component is already added to the object!\n";
      return;
    }
  }
  Component **temp = new Component *[componentCount];
  for (unsigned int i = 0; i < componentCount; i++) {
    temp[i] = components[i];
  }
  delete[] components;
  components = new Component *[++componentCount];
  for (unsigned int i = 0; i < componentCount - 1; i++) {
    components[i] = temp[i];
  }
  delete[] temp;
  components[componentCount - 1] = component;
}

void PROF::Object::removeComponent(int componentID) {
  bool componentFound = false;
  for (unsigned int i = 0; i < componentCount; i++) {
    if (componentID == components[i]->getID()) {
      componentFound = true;
    }
  }
  if (!componentFound) {
    std::cout << "The component was not found!\n";
    return;
  }
  Component **temp = new Component *[--componentCount];
  unsigned int j = 0;
  for (unsigned int i = 0; i < componentCount + 1; i++) {
    if (components[i]->getID() != componentID) {
      temp[j] = components[i];
      j++;
    } else {
      j--;
    }
  }
  delete[] components;
  components = new Component *[componentCount];
  for (unsigned int i = 0; i < componentCount; i++) {
    components[i] = temp[i];
  }
  delete[] temp;
}

void PROF::Object::addShader(Shader *shader) {
  this->objectShader = shader;
  renderable = true;
}

bool PROF::Object::isRenderable() { return renderable; }

void PROF::Object::bindShader() {
  if (renderable) {
    objectShader->render();
  }
}

void PROF::Object::toggleActive() { isActive = !isActive; }

GLuint PROF::Object::getShaderID() {
  if (renderable) {
    return objectShader->getProgramID();
  }
  return 0;
}

void PROF::Object::render() {
  if (isActive) {
    for (unsigned int i = 0; i < componentCount; i++) {
      components[i]->render();
    }
  }
}