#include "Objects/Sphere.hpp"

void normalize(float *vec) {
  float l = sqrt(powf(vec[0], 2.0f) + powf(vec[1], 2.0f) + powf(vec[2], 2.0f));
  vec[0] /= l;
  vec[1] /= l;
  vec[2] /= l;
}

void subdivide(float v1[3], float v2[3], float v3[3], int depth,
               float *vertices, float *normals, unsigned int &iter) {
  float v12[3], v23[3], v31[3];

  if (depth == 0) {
    vertices[iter] = v1[0];
    normals[iter] = vertices[iter++];
    vertices[iter] = v1[1];
    normals[iter] = vertices[iter++];
    vertices[iter] = v1[2];
    normals[iter] = vertices[iter++];
    vertices[iter] = v2[0];
    normals[iter] = vertices[iter++];
    vertices[iter] = v2[1];
    normals[iter] = vertices[iter++];
    vertices[iter] = v2[2];
    normals[iter] = vertices[iter++];
    vertices[iter] = v3[0];
    normals[iter] = vertices[iter++];
    vertices[iter] = v3[1];
    normals[iter] = vertices[iter++];
    vertices[iter] = v3[2];
    normals[iter] = vertices[iter++];
    return;
  }

  // calculate midpoints of each side
  for (int i = 0; i < 3; i++) {
    v12[i] = (v1[i] + v2[i]) / 2.0f;
    v23[i] = (v2[i] + v3[i]) / 2.0f;
    v31[i] = (v3[i] + v1[i]) / 2.0f;
  }
  // extrude midpoints to lie on unit sphere
  normalize(v12);
  normalize(v23);
  normalize(v31);

  // recursively subdivide new triangles
  subdivide(v1, v12, v31, depth - 1, vertices, normals, iter);
  subdivide(v2, v23, v12, depth - 1, vertices, normals, iter);
  subdivide(v3, v31, v23, depth - 1, vertices, normals, iter);
  subdivide(v12, v23, v31, depth - 1, vertices, normals, iter);
}

PROF::Sphere::Sphere() : sphereModel(NULL), blinnPhong(NULL) {}

void PROF::Sphere::genSphere(unsigned int recursionLevel) {
  blinnPhong = new Shader();
  std::string shaderFilepath = "./res/shaders/BlinnPhong.glsl";
  blinnPhong->genShader(shaderFilepath);
  addShader(blinnPhong);
  sphereModel = new Model();

  const float X = 0.525731112119133606f;
  const float Z = 0.850650808352039932f;
  const float N = 0.0f;

  float verts[36] = {-X, N, Z, X,  N, Z,  -X, N,  -Z, X,  N,  -Z,
                     N,  Z, X, N,  Z, -X, N,  -Z, X,  N,  -Z, -X,
                     Z,  X, N, -Z, X, N,  Z,  -X, N,  -Z, -X, N};

  unsigned int indes[60] = {0, 4,  1,  0, 9, 4,  9, 5,  4, 4,  5, 8, 4, 8, 1,
                            8, 10, 1,  8, 3, 10, 5, 3,  8, 5,  2, 3, 2, 7, 3,
                            7, 10, 3,  7, 6, 10, 7, 11, 6, 11, 0, 6, 0, 1, 6,
                            6, 1,  10, 9, 0, 11, 9, 11, 2, 9,  2, 5, 7, 2, 11};

  count = 180 * (int)pow(4, recursionLevel);

  float *vertices = new float[count];
  float *normals = new float[count];

  unsigned int iter = 0;

  for (int i = 0; i < 20; i++) {
    float v1[3] = {verts[3 * indes[3 * i]], verts[3 * indes[3 * i] + 1],
                   verts[3 * indes[3 * i] + 2]};
    float v2[3] = {verts[3 * indes[3 * i + 1]], verts[3 * indes[3 * i + 1] + 1],
                   verts[3 * indes[3 * i + 1] + 2]};
    float v3[3] = {verts[3 * indes[3 * i + 2]], verts[3 * indes[3 * i + 2] + 1],
                   verts[3 * indes[3 * i + 2] + 2]};
    subdivide(v1, v2, v3, recursionLevel, vertices, normals, iter);
  }
  sphereModel->genModel(vertices, normals, count);
  addComponent(sphereModel);
  delete[] vertices;
  delete[] normals;
}

PROF::Sphere::~Sphere() {
  if (sphereModel != NULL) {
    delete sphereModel;
  }
  if (blinnPhong != NULL) {
    delete blinnPhong;
  }
}

void PROF::Sphere::setColor(const float *color) {
  colorUniform[0] = color[0];
  colorUniform[1] = color[1];
  colorUniform[2] = color[2];
  colorUniform[3] = color[3];
}

void PROF::Sphere::setPosition(vmath::vec3 position) {
  sphereModel->setPosition(position);
}

void PROF::Sphere::setVelocity(vmath::vec3 velocity) {
  sphereModel->setVelocity(velocity);
}

void PROF::Sphere::setForce(vmath::vec3 force) {
  sphereModel->setForce(force);
}

void PROF::Sphere::setScale(float scale) { sphereModel->setScale(scale); }

void PROF::Sphere::render() {
  for (unsigned int i = 0; i < componentCount; i++) {
    components[i]->render();
  }
  GLCall(glUniform4fv(11, 1, colorUniform));
  GLCall(glDrawArrays(GL_TRIANGLES, 0, count / 3));
}