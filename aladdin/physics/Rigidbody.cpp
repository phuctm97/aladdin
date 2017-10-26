#include "Rigidbody.h"

#include "../core/GameObject.h"
#include "PhysicsManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(Rigidbody, GameObjectComponent)

Rigidbody::Rigidbody ( GameObject* gameObject, const std::string& name )
  : GameObjectComponent ( gameObject, name ),
    _mass ( 1 ),
    _position ( gameObject->getTransform (  )->getPosition (  ) ),
    _velocity ( 0 ),
    _gravityScale ( 1 ),
    _bodyType ( ALA_BODY_TYPE_DYNAMIC )
{
}

void Rigidbody::onPhysicsUpdate ( const float delta )
{
  _position = getGameObject()->getTransform()->getPosition();

  if (_bodyType == ALA_BODY_TYPE_STATIC)
  {
    return;
  }

  const Vec2 totalForce = _forces + _impulses;

  const Vec2 gravityAcceleration = GRAVITY_ACCELERATION * _gravityScale;

  _impulses = Vec2(0,0);

  const Vec2 acceleration = totalForce / _mass + gravityAcceleration;
  _velocity += acceleration*delta;

  // x = x0 + v0*t + (1/2)at^2
  _position += _velocity*delta + acceleration*(1 / 2.f)*delta*delta;
}

void Rigidbody::addForce ( const Vec2 &force)
{
  if(_bodyType == ALA_BODY_TYPE_STATIC || _bodyType == ALA_BODY_TYPE_KINEMATIC)
  {
    return;
  }
  _forces += force;
}

void Rigidbody::addImpulse ( const Vec2& impulse )
{
  if (_bodyType == ALA_BODY_TYPE_STATIC || _bodyType == ALA_BODY_TYPE_KINEMATIC)
  {
    return;
  }

  _impulses += impulse;
}

void Rigidbody::setPosition ( const Vec2& position )
{
  _position = position;
}

void Rigidbody::setVelocity ( const Vec2& velocity )
{
  _velocity = velocity;
}

void Rigidbody::setBodyType ( const int bodyType )
{
  _bodyType = bodyType;
}

void Rigidbody::setMass ( const float mass )
{
  _mass = mass;
}

void Rigidbody::setGravityScale ( const float gravityScale )
{
  _gravityScale = gravityScale;
}

const Vec2& Rigidbody::getPosition ( ) const
{
  return _position;
}

const Vec2& Rigidbody::getVelocity ( ) const
{
  return _velocity;
}

const int Rigidbody::getBodyType ( ) const
{
  return _bodyType;
}

const float Rigidbody::getMass ( ) const
{
  return _mass;
}

const float Rigidbody::getGravityScale ( ) const
{
  return _gravityScale;
}

void Rigidbody::onInitialize ( )
{
  PhysicsManager::get()->attach(this);
}

void Rigidbody::onRelease ( )
{
  PhysicsManager::get()->detach(this);
}

Rigidbody::~Rigidbody ( )
{
}
}

