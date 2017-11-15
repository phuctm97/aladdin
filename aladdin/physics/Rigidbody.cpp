#include "Rigidbody.h"

#include "../core/GameObject.h"
#include "PhysicsManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(Rigidbody, GameObjectComponent)

Rigidbody::Rigidbody (GameObject* gameObject, const PhysicsMaterial& material, const int bodyType, const float gravityScale, const std::string& name)
  : GameObjectComponent ( gameObject, name ),
    _position ( gameObject->getTransform (  )->getPosition (  ) ),
    _velocity ( 0 ),
		_bodyType(bodyType),
		_material(material),
    _gravityScale ( gravityScale ),
		_forces(0),
		_impulses(0)
{
}

void Rigidbody::addAcceleration(const Vec2& acceleration)
{
	if (_bodyType == ALA_BODY_TYPE_STATIC)
	{
		return;
	}

	_forces += acceleration * getMass();
}

void Rigidbody::addVelocity(const Vec2& velocity)
{
	if (_bodyType == ALA_BODY_TYPE_STATIC)
	{
		return;
	}

	_impulses += velocity * getMass();
}

void Rigidbody::onPhysicsUpdate ( const float delta )
{
  _position = getGameObject()->getTransform()->getPosition();

  if (_bodyType == ALA_BODY_TYPE_STATIC)
  {
    return;
  }

  const Vec2 totalForce = _forces;

  Scene* scene = NULL;
  {
    GameObject *p = getGameObject();
    while (p->getParentScene() == NULL) p = p->getTransform()->getParent()->getGameObject();
    scene = p->getParentScene();
  }
  const Vec2 gravityAcceleration = scene->getGravityAcceleration() * _gravityScale;

  const Vec2 acceleration = totalForce * getInverseMass() + gravityAcceleration;

  _velocity += acceleration*delta + _impulses * getInverseMass();

  _position += _velocity*delta;

	_impulses = Vec2(0, 0);
}

void Rigidbody::resetForce()
{
	_forces = 0;
}

void Rigidbody::addForce ( const Vec2 &force)
{
  if(_bodyType == ALA_BODY_TYPE_STATIC)
  {
    return;
  }
  _forces += force;
}

void Rigidbody::addImpulse ( const Vec2& impulse )
{
  if (_bodyType == ALA_BODY_TYPE_STATIC)
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

void Rigidbody::setGravityScale ( const float gravityScale )
{
  _gravityScale = gravityScale;
}

void Rigidbody::setPhysicsMaterial(const PhysicsMaterial& material)
{
	_material = material;
}

const PhysicsMaterial& Rigidbody::getPhysicsMaterial() const
{
	return _material;
}

const Vec2& Rigidbody::getPosition ( ) const
{
  return _position;
}

const Vec2& Rigidbody::getVelocity ( ) const
{
  return _velocity;
}

int Rigidbody::getBodyType ( ) const
{
  return _bodyType;
}

float Rigidbody::getMass ( ) const
{
	const auto collider = getGameObject()->getComponentT<Collider>();
	if(collider == nullptr)
	{
		return 0;
	}

	return collider->getSize().getArea() * _material.getDensity();
}

float Rigidbody::getInverseMass() const
{
	const auto mass = getMass();

	if(mass == 0)
	{
		return 0;
	}

	return 1 / mass;
}

float Rigidbody::getGravityScale ( ) const
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

