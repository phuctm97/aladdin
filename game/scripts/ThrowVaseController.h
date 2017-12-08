#ifndef __THROW_VASE_CONTROLLER_H__
#define __THROW_VASE_CONTROLLER_H__

#include <aladdin.h>

class ThrowVaseController : public ala::GameObjectComponent
{
private:
	bool _collidedWithGround;
	bool _nearAladdin;

protected:
	void onUpdate(const float delta) override;

public:
	ThrowVaseController(ala::GameObject* gameObject, const std::string& name = "");

	bool isCollidedWithGround() const;

	bool isAladdinNear() const;

	void resetCollidedWithGround();

	void onCollisionEnter(const ala::CollisionInfo& collision) override;

	void throwVase(char direction, float directX, float directY, float impulseX, float impulseY) const;



};

#endif //!__THROW_VASE_CONTROLLER_H__

