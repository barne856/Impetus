#ifndef __CAMERA__
#define __CAMERA__

#include "PROF.hpp"
// include modules
#include "Modules/RigidBody.hpp"

namespace PROF {

enum CameraType {Camera2D, Camera3D};

class Camera: public RigidBody {
private:
  vmath::vec3 center;
  vmath::vec3 up;
  vmath::mat4 projection;
  float aspect;
  float fovy;
  CameraType type;

public:
  Camera();
  ~Camera();
  void setView3D();
  void setView2D();
  void setLookat(vmath::vec3 eye, vmath::vec3 center, vmath::vec3 up);
  void setAspect(float aspect);
  void setFOVy(float fovy);
  void render(GLuint programID);
};
} // namespace PROF

#endif //__CAMERA__