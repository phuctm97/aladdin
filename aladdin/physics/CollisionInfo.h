#ifndef __ALADDIN_PHYSICS_COLLISION_INFO_H__
#define __ALADDIN_PHYSICS_COLLISION_INFO_H__

#include "PhysicsInclude.h"


NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(CollisionInfo)
private:
	GameObject* _objectA;
	GameObject* _objectB;
	float _penetration;
	Vec2 _normal;
public:
	CollisionInfo(GameObject* a = NULL, GameObject* b = NULL, float penetration = 0, Vec2 normal = Vec2(0, 0));
	virtual ~CollisionInfo();

	void setObjectA(GameObject* objectA);
	void setObjectB(GameObject* objectB);
	void setPenetration(const float penetration);
	void setNormal(const Vec2& normal);

	GameObject* getObjectA() const;
	GameObject* getObjectB() const;
	float getPenetration() const;
	const Vec2& getNormal() const;
};

}

#endif //!__ALADDIN_PHYSICS_COLLISION_INFO_H__