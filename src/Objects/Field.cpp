#include "Objects/Field.hpp"

PROF::Field::Field() : model(NULL), shader(NULL) {
}

PROF::Field::~Field() {
  if (model != NULL) {
    delete model;
  }
  if (shader != NULL) {
    delete shader;
  }
  if(angleTexture != 0)
  {
    glDeleteTextures(1, &angleTexture);
  }
  if(angleBuffer != 0)
  {
    glBindBuffer(GL_ARRAY_BUFFER, angleBuffer);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glDeleteBuffers(1, &angleBuffer);
  }
}

void PROF::Field::genField() {
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
  fieldType = line;
  std::string shaderFilepath = "./res/shaders/Field.glsl";
  shader->genShader(shaderFilepath);

  float verticies[6] = {-0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f};
  float normals[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

  model->genModel(verticies, normals, 6);
  model->setScale(scale);

  addShader(shader);
  addComponent(model);

  GLCall(glGenBuffers(1, &angleBuffer));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, angleBuffer));
  GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)*n*n, NULL, GL_DYNAMIC_DRAW));
  GLCall(angle = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

  GLCall(glGenTextures(1, &angleTexture));
  GLCall(glBindTexture(GL_TEXTURE_BUFFER, angleTexture));
  GLCall(glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, angleBuffer));

}

void PROF::Field::genFieldArrow(float ang, float length, float width,
                           float weight) {
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
  fieldType = arrow;
  std::string shaderFilepath = "./res/shaders/Field.glsl";
  shader->genShader(shaderFilepath);

  float l1 = 1.0f;
  float l2 = length;
  float l3 = width * weight;
  float l4 = width;

  float vertices[45]{
      -0.5f,
      -0.5f * l3,
      0.0f,
      -0.5f,
      0.5f * l3,
      0.0f,
      l2 - 0.5f,
      0.5f * l3,
      0.0f,

      -0.5f,
      -0.5f * l3,
      0.0f,
      l2 - 0.5f,
      0.5f * l3,
      0.0f,
      l2 - 0.5f,
      -0.5f * l3,
      0.0f,

      l2 - 0.5f,
      0.5f * l3,
      0.0f,
      0.5f,
      0.0f,
      0.0,
      l2 - 0.5f,
      -0.5f * l3,
      0.0f,

      0.5f,
      0.0f,
      0.0,
      l2 - 0.5f,
      0.5f * l3,
      0.0f,
      l2 - 0.5f - (0.5f * (l4 - l3)) / tan(ang * (float)M_PI / 180.0f),
      0.5f * l4,
      0.0f,

      0.5f,
      0.0f,
      0.0,
      l2 - 0.5f - (0.5f * (l4 - l3)) / tan(ang * (float)M_PI / 180.0f),
      -0.5f * l4,
      0.0f,
      l2 - 0.5f,
      -0.5f * l3,
      0.0f};

  float normals[45]{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

  model->genModel(vertices, normals, 45);
  model->setScale(scale);

  addShader(shader);
  addComponent(model);

  GLCall(glGenBuffers(1, &angleBuffer));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, angleBuffer));
  GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)*n*n, NULL, GL_DYNAMIC_DRAW));
  GLCall(angle = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

  GLCall(glGenTextures(1, &angleTexture));
  GLCall(glBindTexture(GL_TEXTURE_BUFFER, angleTexture));
  GLCall(glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, angleBuffer));

}

void PROF::Field::setColor(const float *color) {
  this->color[0] = color[0];
  this->color[1] = color[1];
  this->color[2] = color[2];
  this->color[3] = color[3];
}

void PROF::Field::setPosition(vmath::vec3 position) {
  model->setPosition(position);
}

void PROF::Field::setVelocity(vmath::vec3 velocity) {
  model->setVelocity(velocity);
}

void PROF::Field::setForce(vmath::vec3 force) { model->setForce(force); }

void PROF::Field::setSlope(ODEfunc x, ODEfunc y, float t)
{
  
  for(int i = 0; i < n*n; i++)
  {
    float px = 2.0f*(float)(i%n)/(float)(n-1) - 1.0f;
    float py = 2.0f*(float)floor(i/n)/(float)(n-1) - 1.0f;
    float dx = x(px,py,t);
    float dy = y(px,py,t);
    float s = 0.0f;
    if(dx == 0.0f)
    {
      if(dy > 0.0f)
      {
        angle[i] = (float)M_PI/2.0f;
      }
      else if(dy < 0.0f)
      {
        angle[i] = -(float)M_PI/2.0f;
      }
      else if(dy == 0.0f)
      {
        angle[i] = std::numeric_limits<float>::quiet_NaN();
      }
    }
    else if(dx > 0.0f)
    {
      s = dy/dx;
      angle[i] = atan(s);
    }
    else if(dx < 0.0f)
    {
      s = dy/dx;
      angle[i] = atan(s) + (float)M_PI;
    }
    else{
      angle[i] = std::numeric_limits<float>::quiet_NaN();
    }
  }
}

void PROF::Field::render() {
  for (unsigned int i = 0; i < componentCount; i++) {
    components[i]->render();
  }
  GLCall(glUniform1i(5, n));
  GLCall(glUniform4fv(11, 1, color));
  if(fieldType == line)
  {
    GLCall(glDrawArraysInstanced(GL_LINES, 0, 15, n*n));
  }
  else if(fieldType == arrow)
  {
    GLCall(glDrawArraysInstanced(GL_TRIANGLES, 0, 15, n*n));
  }
  
}