#ifndef __ALADDIN_PHYSICS_COLLIDER_H__
#define __ALADDIN_PHYSICS_COLLIDER_H__

#include "PhysicsInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Collider, GameObjectComponent)
private:
	Vec2 _offset;
	Size _size;

	bool _isTrigger;

	int _physicsLayer;
public:
	Collider(GameObject* gameObject, const bool isTrigger = false, const Vec2 &offset = Vec2(0,0), const Size &size = Size(0,0), const int physicsLayer = 0, const std::string &name = "");

	Rect getBoundingRect() const;

	void onInitialize() override;;

	void onRelease() override;

	virtual ~Collider();

	void setOffset(const Vec2& offset);
	void setSize(const Size& size);
	void setTrigger(const bool trigger);
	void setPhysicsLayer(const int physicsLayer);

	const Vec2& getOffset() const;
	const Size& getSize() const;
	bool getTrigger() const;
	int getPhysicsLayer() const;
};
}

#endif //!__ALADDIN_PHYSICS_COLLIDER_H__
