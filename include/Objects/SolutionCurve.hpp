#ifndef __PROF_SOLUTION_CURVE__
#define __PROF_SOLUTION_CURVE__

#include "PROF.hpp"
// include modules
#include "Modules/Model.hpp"
#include "Modules/Object.hpp"

typedef float (*ODEfunc)(float, float, float);

namespace PROF
{
class SolutionCurve : public Object
{
  private:
    float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    Shader *shader;
    Model* model;
    float* vertices;
    unsigned int count;
    ODEfunc x;
    ODEfunc y;
    vmath::vec2 vec;
    float t;
    float gridScale = 4.0f;

  public:
    SolutionCurve();
    ~SolutionCurve();
    void genSolutionCurve(ODEfunc x, ODEfunc y, float initX, float initY, float initT, int iters);
    void setColor(const float *color);
    void update(vmath::vec2 vec, float t);
    virtual void render();
};
} // namespace PROF

#endif //__PROF_SOLUTION_CURVE__