#ifndef __THROWABLE_APPLE_CONTROLLER_H__
#define __THROWABLE_APPLE_CONTROLLER_H__

#include <aladdin.h>

class ThrowableAppleController : public ala::GameObjectComponent
{
private:
	bool _collided;

public:
	ThrowableAppleController(ala::GameObject* gameObject, const std::string& name = "");

	bool isCollided() const;

	void onTriggerEnter(const ala::CollisionInfo& collision) override;
};

#endif //!__THROWABLE_APPLE_CONTROLLER_H__
