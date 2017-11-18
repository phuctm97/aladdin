#ifndef __APPLE_CONTROLLER_H__
#define __APPLE_CONTROLLER_H__
#include <aladdin.h>

class Throwable_appleController : public ala::GameObjectComponent
{
	ala::Logger _logger;
	bool _collidedWithGround;

public:
	Throwable_appleController(ala::GameObject* gameObject, const std::string& name = "");

	bool isCollidedWithGround() const;
	void resetCollidedWithGround();

	void onTriggerEnter(const ala::CollisionInfo& collision) override;
	
};

#endif //!__APPLE_CONTROLLER_H__
