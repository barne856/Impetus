#include "Modules/Scene.hpp"

PROF::Scene::Scene() : objectCount(0) {
  objects = new Object *[0];
}

PROF::Scene::Scene(const Scene &scene) {
  objectCount = scene.objectCount;
  objects = new Object *[objectCount];
  for (unsigned int i = 0; i < objectCount; i++) {
    objects[i] = scene.objects[i];
  }
}

PROF::Scene &PROF::Scene::operator=(const Scene &scene) {
  // check for self assignment
  if (this == &scene) {
    return *this;
  }

  objectCount = scene.objectCount;
  delete[] objects;
  objects = new Object *[objectCount];
  for (unsigned int i = 0; i < objectCount; i++) {
    objects[i] = scene.objects[i];
  }
  return *this;
}

PROF::Scene::~Scene() { delete[] objects; }

void PROF::Scene::addObject(Object* object) {
  for (unsigned int i = 0; i < objectCount; i++) {
    if (object->getID() == objects[i]->getID()) {
      std::cout << "Object is already added to the scene!\n";
      return;
    }
  }
  Object **temp = new Object *[objectCount];
  for (unsigned int i = 0; i < objectCount; i++) {
    temp[i] = objects[i];
  }
  delete[] objects;
  objects = new Object *[++objectCount];
  for (unsigned int i = 0; i < objectCount - 1; i++) {
    objects[i] = temp[i];
  }
  delete[] temp;
  objects[objectCount - 1] = object;
}

void PROF::Scene::removeObject(int objectID) {
  bool objectFound = false;
  for (unsigned int i = 0; i < objectCount; i++) {
    if (objectID == objects[i]->getID()) {
      objectFound = true;
    }
  }
  if (!objectFound) {
    std::cout << "The object was not found!\n";
    return;
  }
  Object **temp = new Object *[--objectCount];
  unsigned int j = 0;
  for (unsigned int i = 0; i < objectCount + 1; i++) {
    if (objects[i]->getID() != objectID) {
      temp[j] = objects[i];
      j++;
    } else {
      j--;
    }
  }
  delete[] objects;
  objects = new Object *[objectCount];
  for (unsigned int i = 0; i < objectCount; i++) {
    objects[i] = temp[i];
  }
  delete[] temp;
}

void PROF::Scene::render() {
  for (unsigned int i = 0; i < objectCount; i++) {
    if(objects[i]->isRenderable())
    {
      objects[i]->bindShader();
      Camera::render(objects[i]->getShaderID());
    }
    objects[i]->render();
  }
}