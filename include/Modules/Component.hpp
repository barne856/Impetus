#ifndef __COMPONENT__
#define __COMPONENT__

#include "PROF.hpp"

namespace PROF
{
class Component
{
private:
  static int uniqueAssignment;
  int ID;

public:
  Component();
  virtual ~Component();
  inline int getID() { return ID; }
  virtual void render();
};
} // namespace PROF

#endif //__COMPONENT__