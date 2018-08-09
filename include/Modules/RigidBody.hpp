#ifndef __RIGIDBODY__
#define __RIGIDBODY__

#include "PROF.hpp"
// include modules
#include "Modules/Component.hpp"

namespace PROF {
class RigidBody: public Component {
private:
  static float dt;

protected:
  vmath::vec3 position;
  vmath::vec3 velocity;
  vmath::vec3 force;

public:
  RigidBody();
  ~RigidBody();
  void setPosition(vmath::vec3 position);
  vmath::vec3 inline getPosition() { return position; }
  void setVelocity(vmath::vec3 velocity);
  vmath::vec3 inline getVelocity() { return velocity; }
  void setForce(vmath::vec3 force);
  vmath::vec3 inline getForce() { return force; }
  void update();
};
} // namespace PROF

#endif //__RIGIDBODY__