#ifndef __PROF_FIELD__
#define __PROF_FIELD__

#include "PROF.hpp"
#include <limits>
// include modules
#include "Modules/Model.hpp"
#include "Modules/Object.hpp"

typedef float (*ODEfunc)(float, float, float);

namespace PROF
{
  enum FieldType {none, arrow, line};
class Field : public Object
{
  private:
    float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    Shader *shader;
    Model *model;
    float scale = 0.08f;
    int n = 8*(int)(1.0f/scale);// increase to make arrows tighter
    GLuint angleBuffer = 0;
    GLuint angleTexture = 0;
    float* angle;
    FieldType fieldType = none;

  public:
    Field();
    ~Field();
    void genField();
    void genFieldArrow(float ang, float length, float width,
                           float weight);
    void setColor(const float *color);
    void setPosition(vmath::vec3 position);
    inline vmath::vec3 getPosition() { return model->getPosition(); }
    void setVelocity(vmath::vec3 velocity);
    inline vmath::vec3 getVelocity() { return model->getVelocity(); }
    void setForce(vmath::vec3 force);
    inline vmath::vec3 getForce() { return model->getForce(); }
    void setSlope(ODEfunc x, ODEfunc y, float t);
    virtual void render();
};
} // namespace PROF

#endif //__PROF_FIELD__