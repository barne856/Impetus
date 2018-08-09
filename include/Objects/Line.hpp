#ifndef __PROF_LINE__
#define __PROF_LINE__

#include "PROF.hpp"
#include <limits>
// include modules
#include "Modules/Model.hpp"
#include "Modules/Object.hpp"

namespace PROF
{
class Line : public Object
{
  private:
    float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    Shader *shader;
    Model *model;
    float slope;

  public:
    Line();
    ~Line();
    void genLine();
    void setColor(const float *color);
    void setPosition(vmath::vec3 position);
    inline vmath::vec3 getPosition() { return model->getPosition(); }
    void setVelocity(vmath::vec3 velocity);
    inline vmath::vec3 getVelocity() { return model->getVelocity(); }
    void setForce(vmath::vec3 force);
    inline vmath::vec3 getForce() { return model->getForce(); }
    void setScale(float scale);
    inline float getScale() { return model->getScale(); }
    void setSlope(float slope);
    inline float getSlope() { return slope; }
    virtual void render();
};
} // namespace PROF

#endif //__PROF_LINE__