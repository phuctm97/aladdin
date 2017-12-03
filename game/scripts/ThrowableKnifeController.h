#ifndef __THROWABLE_KNIFE_CONTROLLER_H__
#define __THROWABLE_KNIFE_CONTROLLER_H__

#include <aladdin.h>

class ThrowableKnifeController : public ala::GameObjectComponent
{
private:
	bool _collidedWithGround;
	bool _colliedWithEnemy;

public:
	ThrowableKnifeController(ala::GameObject* gameObject, const std::string& name = "");

	bool isCollidedWithGround() const;

	bool isCollidedWithEnemy() const;

	void onTriggerEnter(const ala::CollisionInfo& collision) override;
};

#endif //!__THROWABLE_KNIFE_CONTROLLER_H__
