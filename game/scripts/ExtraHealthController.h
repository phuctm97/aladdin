#ifndef __EXTRA_HEALTH_CONTROLLER_H__
#define __EXTRA_HEALTH_CONTROLLER_H__

#include <aladdin.h>

class ExtraHealthController : public ala::GameObjectComponent
{
private:
	bool _aladdinCollision;
protected:
	void onUpdate(const float delta) override;

public:
	ExtraHealthController(ala::GameObject* gameObject, const std::string& name = "");
	bool isCollisionAladdin() const;
	void explosionEffect() const;
};

#endif //!__EXTRA_HEALTH_CONTROLLER_H__

