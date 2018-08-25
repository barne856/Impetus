#ifndef __MODEL__
#define __MODEL__

#include "PROF.hpp"
// include modules
#include "Modules/RigidBody.hpp"

namespace PROF
{
class Model : public RigidBody
{
    private:
    GLuint vertexArray;
    GLuint vertexBuffer;
    GLuint normalBuffer;

    vmath::mat4 modelMatrix;
    vmath::mat4 rotation;
    vmath::mat4 translation;
    vmath::mat4 scaleMatrix;

    unsigned int count;

    bool mapped = false;

    void updateModelMatrix();

    public:
    Model();
    virtual ~Model();
    void genModel(float* vertices, float* normals, unsigned int count);
    void genMappedModel(float* vertices, unsigned int count);
    void setRotation(float angle, vmath::vec3 axis);
    void setScale(float scale);
    float inline getScale() {return scaleMatrix[0][0];}
    void Bind() const;
    virtual void render();

};
} // namespace PROF

#endif //__MODEL__