#ifndef __APPLE_CONTROLLER_H__
#define __APPLE_CONTROLLER_H__

#include <aladdin.h>

class AppleController : public ala::GameObjectComponent
{
public:
	AppleController(ala::GameObject* gameObject, const string& name = "");

protected:
	void onTriggerEnter(const ala::CollisionInfo& collision) override;
};


#endif //!__APPLE_CONTROLLER_H__