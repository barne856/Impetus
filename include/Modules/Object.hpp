#ifndef __OBJECT__
#define __OBJECT__

#include "PROF.hpp"
// include modules
#include "Modules/Shader.hpp"
#include "Modules/Component.hpp"

namespace PROF {

class Object {
private:
  bool renderable;
  bool isActive;
  static int uniqueAssignment;
  int ID;

protected:
  Shader *objectShader;
  Component **components;
  unsigned int componentCount;

public:
  Object();
  Object(const Object &object);
  Object &operator=(const Object &object);
  virtual ~Object();
  inline int getID() { return ID; }
  void addComponent(Component* component);
  void removeComponent(int componentID);
  void addShader(Shader *shader);
  void bindShader();
  void toggleActive();
  bool isRenderable();
  GLuint getShaderID();
  virtual void render();
};
} // namespace PROF

#endif //__OBJECT__