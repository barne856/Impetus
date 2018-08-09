#include "Modules/Component.hpp"

int PROF::Component::uniqueAssignment = 0;

PROF::Component::Component() {
  uniqueAssignment++;
  ID = uniqueAssignment;
}

PROF::Component::~Component() {}

void PROF::Component::render() {}
