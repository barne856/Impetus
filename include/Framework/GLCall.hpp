#ifndef __GL_CALL__
#define __GL_CALL__

#include "PROF.hpp"

#define GLCall(x)                                                              \
  GLClearError();                                                              \
  x;                                                                           \
  GLLogCall(#x, __FILE__, __LINE__)

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

#endif //__GL_CALL__