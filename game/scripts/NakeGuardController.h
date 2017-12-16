#ifndef __NAKEGUARD_CONTROLLER_H__
#define __NAKEGUARD_CONTROLLER_H__

#include <aladdin.h>

class NakeGuardController : public ala::GameObjectComponent
{
private:
	bool _collidedWithGround;
	bool _couldAttackAladdin;
	bool _couldSeeAladdin;
	bool _onRightOfAladdin;
	bool _couldThrowToSky;

protected:
	void onUpdate(const float delta) override;

public:
	NakeGuardController(ala::GameObject* gameObject, const std::string& name = "");
	bool isCollidedWithGround() const;
	bool couldAttackAladdin() const;
	bool coundSeeAladdin() const;
	bool couldThrowToSky() const;
	bool isOnRightOfAladdin() const;
	void onCollisionEnter(const ala::CollisionInfo& collision) override;
	void throwKnife(const char direction, const float directX, const float directY,
		const float impulseX, const float impulseY) const;
};

#endif //!__NAKEGUARD_CONTROLLER_H__

