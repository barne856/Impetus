#ifndef __COLORS__
#define __COLORS__

#include <stdlib.h>
#include <time.h>

namespace PROF {
class Colors {
public:
  static const float red[4];
  static const float green[4];
  static const float blue[4];
  static const float magenta[4];
  static const float purple[4];
  static const float indigo[4];
  static const float orange[4];
  static const float gray[4];
  static const float blueGray[4];
  static const float pink[4];
  static const float teal[4];
  static const float brown[4];
  static const float black[4];
  static const float white[4];
  static const float spaceGray[4];
  static const float cream[4];
  static const float ivory[4];
  static const float silver[4];
  static const float beige[4];
  static const float gold[4];
  static const float yellow[4];
  static const float *randomColor();

private:
  static bool seeded;
};
} // namespace PROF

#endif //__COLORS__