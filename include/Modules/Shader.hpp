#ifndef __SHADER__
#define __SHADER__

#include "PROF.hpp"

namespace PROF {
class Shader {
private:
  struct ShaderSource {
    std::string VertexSource;
    std::string TCSource;
    std::string TESource;
    std::string GeometrySource;
    std::string FragmentSource;
    std::string ComputeSource;
  };

  ShaderSource ParseShader(std::string &filepath);
  void CompileShader(ShaderSource shaderSource);
  void Bind();

  GLuint programID;

public:
  Shader();
  void genShader(std::string &filepath);
  ~Shader();
  virtual void render();
  inline GLuint getProgramID() { return programID; }
};
} // namespace PROF
#endif //__SHADER__