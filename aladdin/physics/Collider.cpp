#include "Collider.h"
#include "PhysicsManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(Collider, GameObjectComponent)

Collider::Collider(GameObject* gameObject, const bool isTrigger, const Vec2& offset, const Size& size,
	const std::string& name)
	: GameObjectComponent(gameObject, name),
	  _offset(offset),
	  _size(size),
	  _isTrigger(isTrigger)
{
}

Rect Collider::getBoundingRect() const
{
	Rect rect;

	rect.setTopLeft(getGameObject()->getTransform()->getWorldPosition() + Vec2(-_size.getWidth()/2, -_size.getHeight()/2));
	OutputDebugString(std::to_string(getGameObject()->getTransform()->getWorldPosition().getX()).c_str());
	OutputDebugString("\n");
	rect.setSize(_size);

	return rect;
}

void Collider::onInitialize()
{
	PhysicsManager::get()->attach(this);
}

void Collider::onRelease()
{
	PhysicsManager::get()->detach(this);
}

Collider::~Collider()
{
}

void Collider::setOffset(const Vec2& offset)
{
	_offset = offset;
}

void Collider::setSize(const Size& size)
{
	_size = size;
}

void Collider::setTrigger(const bool trigger)
{
	_isTrigger = trigger;
}

const Vec2& Collider::getOffset() const
{
	return _offset;
}

const Size& Collider::getSize() const
{
	return _size;
}

bool Collider::getTrigger() const
{
	return _isTrigger;
}
}
