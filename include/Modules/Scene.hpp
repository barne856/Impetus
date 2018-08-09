#ifndef __SCENE__
#define __SCENE__

#include "PROF.hpp"
// include modules
#include "Modules/Camera.hpp"
#include "Modules/Object.hpp"

namespace PROF {

class Scene : public Camera {
private:
  Object **objects;
  unsigned int objectCount;

public:
  Scene();
  Scene(const Scene &scene);
  Scene &operator=(const Scene &scene);
  ~Scene();
  void addObject(Object* object);
  void removeObject(int objectID);
  void render();
};
} // namespace PROF

#endif //__SCENE__