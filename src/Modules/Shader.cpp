#include "Modules/Shader.hpp"

PROF::Shader::Shader() : programID(0) {}

void PROF::Shader::genShader(std::string &filepath) {
  programID = 0;
  Shader::ShaderSource source = ParseShader(filepath);
  CompileShader(source);
}

PROF::Shader::~Shader() {
  if (programID != 0) {
    GLCall(glDeleteProgram(programID));
  }
}

PROF::Shader::ShaderSource PROF::Shader::ParseShader(std::string &filepath) {
  std::ifstream stream(filepath);

  if (!stream.is_open()) {
    std::cout << "Failed to open shader file!" << std::endl;
  }

  enum class ShaderType {
    NONE = -1,
    VERTEX = 0,
    TCS = 1,
    TES = 2,
    GEOMETRY = 3,
    FRAGMENT = 4,
    COMPUTE = 5
  };

  std::string line;
  std::stringstream ss[6];
  ShaderType type = ShaderType::NONE;

  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        type = ShaderType::VERTEX;
      } else if (line.find("tessellation control") != std::string::npos) {
        type = ShaderType::TCS;
      } else if (line.find("tessellation evaluation") != std::string::npos) {
        type = ShaderType::TES;
      } else if (line.find("geometry") != std::string::npos) {
        type = ShaderType::GEOMETRY;
      } else if (line.find("fragment") != std::string::npos) {
        type = ShaderType::FRAGMENT;
      } else if (line.find("compute") != std::string::npos) {
        type = ShaderType::COMPUTE;
      }
    } else {
      ss[(int)type] << line << '\n';
    }
  }
  return {ss[0].str(), ss[1].str(), ss[2].str(),
          ss[3].str(), ss[4].str(), ss[5].str()};
}

void PROF::Shader::CompileShader(PROF::Shader::ShaderSource shaderSource) {
  GLCall(unsigned int program = glCreateProgram());
  int result;

  if (shaderSource.VertexSource.size()) {
    GLCall(unsigned int shader = glCreateShader(GL_VERTEX_SHADER));
    const char *src = shaderSource.VertexSource.c_str();
    GLCall(glShaderSource(shader, 1, &src, nullptr));
    GLCall(glCompileShader(shader));

    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
      int length;
      GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
      char *message = (char *)alloca(length * sizeof(char));
      GLCall(glGetShaderInfoLog(shader, length, &length, message));
      std::cout << "Failed to compile vertex shader!" << std::endl;
      std::cout << message << std::endl;
      GLCall(glDeleteShader(shader));
      return;
    }
    GLCall(glAttachShader(program, shader));
    GLCall(glDeleteShader(shader));
  }

  if (shaderSource.TCSource.size()) {
    GLCall(unsigned int shader = glCreateShader(GL_TESS_CONTROL_SHADER));
    const char *src = shaderSource.TCSource.c_str();
    GLCall(glShaderSource(shader, 1, &src, nullptr));
    GLCall(glCompileShader(shader));

    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
      int length;
      GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
      char *message = (char *)alloca(length * sizeof(char));
      GLCall(glGetShaderInfoLog(shader, length, &length, message));
      std::cout << "Failed to compile tessellation control shader!"
                << std::endl;
      std::cout << message << std::endl;
      GLCall(glDeleteShader(shader));
      return;
    }
    GLCall(glAttachShader(program, shader));
    GLCall(glDeleteShader(shader));
  }

  if (shaderSource.TESource.size()) {
    GLCall(unsigned int shader = glCreateShader(GL_TESS_EVALUATION_SHADER));
    const char *src = shaderSource.TESource.c_str();
    GLCall(glShaderSource(shader, 1, &src, nullptr));
    GLCall(glCompileShader(shader));

    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
      int length;
      GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
      char *message = (char *)alloca(length * sizeof(char));
      GLCall(glGetShaderInfoLog(shader, length, &length, message));
      std::cout << "Failed to compile tessellation evaluation shader!"
                << std::endl;
      std::cout << message << std::endl;
      GLCall(glDeleteShader(shader));
      return;
    }
    GLCall(glAttachShader(program, shader));
    GLCall(glDeleteShader(shader));
  }

  if (shaderSource.GeometrySource.size()) {
    GLCall(unsigned int shader = glCreateShader(GL_GEOMETRY_SHADER));
    const char *src = shaderSource.GeometrySource.c_str();
    GLCall(glShaderSource(shader, 1, &src, nullptr));
    GLCall(glCompileShader(shader));

    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
      int length;
      GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
      char *message = (char *)alloca(length * sizeof(char));
      GLCall(glGetShaderInfoLog(shader, length, &length, message));
      std::cout << "Failed to compile geometry shader!" << std::endl;
      std::cout << message << std::endl;
      GLCall(glDeleteShader(shader));
      return;
    }
    GLCall(glAttachShader(program, shader));
    GLCall(glDeleteShader(shader));
  }

  if (shaderSource.FragmentSource.size()) {
    GLCall(unsigned int shader = glCreateShader(GL_FRAGMENT_SHADER));
    const char *src = shaderSource.FragmentSource.c_str();
    GLCall(glShaderSource(shader, 1, &src, nullptr));
    GLCall(glCompileShader(shader));

    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
      int length;
      GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
      char *message = (char *)alloca(length * sizeof(char));
      GLCall(glGetShaderInfoLog(shader, length, &length, message));
      std::cout << "Failed to compile fragment shader!" << std::endl;
      std::cout << message << std::endl;
      GLCall(glDeleteShader(shader));
      return;
    }
    GLCall(glAttachShader(program, shader));
    GLCall(glDeleteShader(shader));
  }

  if (shaderSource.ComputeSource.size()) {
    GLCall(unsigned int shader = glCreateShader(GL_COMPUTE_SHADER));
    const char *src = shaderSource.ComputeSource.c_str();
    GLCall(glShaderSource(shader, 1, &src, nullptr));
    GLCall(glCompileShader(shader));

    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
      int length;
      GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
      char *message = (char *)alloca(length * sizeof(char));
      GLCall(glGetShaderInfoLog(shader, length, &length, message));
      std::cout << "Failed to compile compute shader!" << std::endl;
      std::cout << message << std::endl;
      GLCall(glDeleteShader(shader));
      return;
    }
    GLCall(glAttachShader(program, shader));
    GLCall(glDeleteShader(shader));
  }

  GLCall(glLinkProgram(program));
  GLCall(glValidateProgram(program));

  GLint validationStatus;
  GLCall(glGetProgramiv(program, GL_VALIDATE_STATUS, &validationStatus));
  if (validationStatus != GL_TRUE) {
    std::cout << "Shader program failed to validate!" << std::endl;
  }

  programID = program;
  GLCall(glUseProgram(programID));
}

void PROF::Shader::Bind() { GLCall(glUseProgram(programID)); }

void PROF::Shader::render() { Bind(); }