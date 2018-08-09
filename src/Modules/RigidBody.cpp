#include "Modules/RigidBody.hpp"

float PROF::RigidBody::dt = 0.01f;

PROF::RigidBody::RigidBody()
    :   position(vmath::vec3(0.0f)), velocity(vmath::vec3(0.0f)), force(vmath::vec3(0.0f))
{

}

PROF::RigidBody::~RigidBody()
{

}

void PROF::RigidBody::setPosition(vmath::vec3 position)
{
    this->position = position;
}

void PROF::RigidBody::setVelocity(vmath::vec3 velocity)
{
    this->velocity = velocity;
}

void PROF::RigidBody::setForce(vmath::vec3 force)
{
    this->force = force;
}

void PROF::RigidBody::update()
{
    position += velocity*dt;
    velocity += force*dt;
}