#ifndef __FATGUARD_CONTROLLER_H__
#define __FATGUARD_CONTROLLER_H__

#include <aladdin.h>

class FatGuardController : public ala::GameObjectComponent
{
private:
	bool _collidedWithGround;
	bool _colliedWithAladdin;
	bool _seeAladdin;
	bool _aladdinPosition;

protected:
	void onUpdate(const float delta) override;

public:
	FatGuardController(ala::GameObject* gameObject, const std::string& name = "");
	bool isCollidedWithGround() const;
	bool isCollidedWithAladdin() const;
	bool isSeeingWithAladdin() const;
	bool isInTheLeftAladdin() const;
	void onCollisionEnter(const ala::CollisionInfo& collision) override;
};

#endif //!__FATGUARD_CONTROLLER_H__
