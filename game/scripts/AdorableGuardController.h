#ifndef __ADORABLEGUARD_CONTROLLER_H__
#define __ADORABLEGUARD_CONTROLLER_H__

#include <aladdin.h>

class AdorableGuardController : public ala::GameObjectComponent
{
private:
	bool _collidedWithGround;
	bool _colliedWithAladdin;
	bool _seeAladdin;
	bool _aladdinPosition;
	bool _isRunFromEnemy;

protected:
	void onUpdate(const float delta) override;

public:
	AdorableGuardController(ala::GameObject* gameObject, const std::string& name = "");
	bool isCollidedWithGround() const;
	bool isCollidedWithAladdin() const;
	bool isSeeingWithAladdin() const;
	bool isInTheLeftAladdin() const;
	bool isRunFromEnemy() const;
	void onCollisionEnter(const ala::CollisionInfo& collision) override;
	void throwKnife(const char direction, const float directX, const float directY,
					const float impulseX, const float impulseY) const;
};
#endif //!__ADORABLEGUARD_CONTROLLER_H__

