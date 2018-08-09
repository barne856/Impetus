#ifndef __SPHERE__
#define __SPHERE__

#include "PROF.hpp"
// include modules
#include "Modules/Object.hpp"
#include "Modules/Model.hpp"

namespace PROF
{
class Sphere : public Object
{
private:
  float colorUniform[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  unsigned int count;
  Shader* blinnPhong;
  Model* sphereModel;

public:
  Sphere();
  void genSphere(unsigned int recursionLevel);
  ~Sphere();
  void setColor(const float *color);
  void setPosition(vmath::vec3 position);
  inline vmath::vec3 getPosition() {return sphereModel->getPosition();}
  void setVelocity(vmath::vec3 velocity);
  inline vmath::vec3 getVelocity() {return sphereModel->getVelocity();}
  void setForce(vmath::vec3 force);
  inline vmath::vec3 getForce() {return sphereModel->getForce();}
  void setScale(float scale);
  inline float getScale() {return sphereModel->getScale();}
  virtual void render();
};
} // namespace PROF

#endif //__SPHERE__