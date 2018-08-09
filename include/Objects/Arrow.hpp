#ifndef __ARROW__
#define __ARROW__

#include "PROF.hpp"
// include modules
#include "Modules/Model.hpp"
#include "Modules/Object.hpp"

namespace PROF {
class Arrow : public Object {
private:
  float colorUniform[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  unsigned int count;
  Shader* solidColor;
  Model* arrowModel;
  float angle = 0.0f;
public:
  Arrow();
  ~Arrow();
  void genArrow(float angle, float length, float width, float weight);
  void setColor(const float *color);
  void setPosition(vmath::vec3 position);
  inline vmath::vec3 getPosition() { return arrowModel->getPosition(); }
  void setVelocity(vmath::vec3 velocity);
  inline vmath::vec3 getVelocity() { return arrowModel->getVelocity(); }
  void setForce(vmath::vec3 force);
  inline vmath::vec3 getForce() { return arrowModel->getForce(); }
  void setScale(float scale);
  inline float getScale() { return arrowModel->getScale(); }
  void setAngle(float angle);
  inline float getAngle() { return angle; }
  virtual void render();
};
} // namespace PROF

#endif //__ARROW__