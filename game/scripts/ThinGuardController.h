#ifndef __THINGUARD_CONTROLLER_H__
#define __THINGUARD_CONTROLLER_H__

#include <aladdin.h>

class ThinGuardController : public ala::GameObjectComponent
{
private:
	bool _collidedWithGround;
	
protected:
	void onUpdate(const float delta) override;

public:
	ThinGuardController(ala::GameObject* gameObject, const std::string& name = "");
	bool isCollidedWithGround() const;
	void onCollisionEnter(const ala::CollisionInfo& collision) override;
};

#endif //!__THINGUARD_CONTROLLER_H__
