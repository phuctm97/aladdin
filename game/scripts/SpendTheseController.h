#ifndef __SPEND_THESE_CONTROLLER_H__
#define __SPEND_THESE_CONTROLLER_H__

#include <aladdin.h>

class SpendTheseController : public ala::GameObjectComponent
{
private:
	bool _aladdinCollision;
protected:
	void onUpdate(const float delta) override;

public:
	SpendTheseController(ala::GameObject* gameObject, const std::string& name = "");
	bool isCollisionAladdin() const;
	void explosionEffect() const;
};

#endif //!__SPEND_THESE_CONTROLLER_H__

