#include "Objects/SolutionCurve.hpp"

PROF::SolutionCurve::SolutionCurve() : vertices(NULL), model(NULL), shader(NULL) 
{

}

PROF::SolutionCurve::~SolutionCurve()
{
  if (model != NULL) {
    delete model;
  }
  if (shader != NULL) {
    delete shader;
  }
}

void PROF::SolutionCurve::genSolutionCurve(ODEfunc x, ODEfunc y, float initX, float initY, float initT, int iters)
{
    this->x = x;
    this->y = y;
    if (model == NULL) {
    model = new Model();
  } else {
    delete model;
    model = new Model();
  }
  if (shader == NULL) {
    shader = new Shader();
  } else {
    delete shader;
    shader = new Shader();
  }
  std::string shaderFilepath = "./res/shaders/Curve.glsl";
  shader->genShader(shaderFilepath);
  addShader(shader);

  vec[0] = initX;
  vec[1] = initY;
  t = initT;

  count = 3*(iters+1);

  model->genMappedModel(vertices, count);
  GLCall(vertices = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));


  vertices[0] = initX, vertices[1] = initY, vertices[2] = 0.0f;
  float dt = 0.001f;
  for(int i = 1; i < count/3; i++)
  {
    int j = 3*i;
    int k = 3*i+1;
    int l = 3*i+2;
    float dx = dt*x(gridScale*vertices[j-3], gridScale*vertices[k-3], initT);
    float dy = dt*y(gridScale*vertices[j-3], gridScale*vertices[k-3], initT);
    vertices[j] = vertices[j-3] + dx;
    vertices[k] = vertices[k-3] + dy;
    vertices[l] = 0.0f;
  }

  addComponent(model);
  glUnmapBuffer(GL_ARRAY_BUFFER);

}

void PROF::SolutionCurve::setColor(const float *color)
{
  this->color[0] = color[0];
  this->color[1] = color[1];
  this->color[2] = color[2];
  this->color[3] = color[3];
}

void PROF::SolutionCurve::update(vmath::vec2 vec, float t)
{
  this->vec = vec;
  this->t = t;
}

void PROF::SolutionCurve::render()
{
  for (unsigned int i = 0; i < componentCount; i++) {
    components[i]->render();
  }
  GLCall(glUniform4fv(11, 1, color));

  GLCall(vertices = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    vertices[0] = vec[0], vertices[1] = vec[1], vertices[2] = 0.0f;
    float dt = 0.001f;
    for(int i = 1; i < count/3; i++)
    {
      int j = 3*i;
      int k = 3*i+1;
      int l = 3*i+2;
      float dx = dt*x(gridScale*vertices[j-3], gridScale*vertices[k-3], t);
      float dy = dt*y(gridScale*vertices[j-3], gridScale*vertices[k-3], t);
      vertices[j] = vertices[j-3] + dx;
      vertices[k] = vertices[k-3] + dy;
      vertices[l] = 0.0f;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

  GLCall(glDrawArrays(GL_LINE_STRIP, 0, count/3));
}
