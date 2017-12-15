#ifndef __GENIE_LAMP_CONTROLLER_H__
#define __GENIE_LAMP_CONTROLLER_H__

#include <aladdin.h>

class GenieLampController : public ala::GameObjectComponent
{
private:
	bool _aladdinCollision;
protected:
	void onUpdate(const float delta) override;

public:
	GenieLampController(ala::GameObject* gameObject, const std::string& name = "");
	bool isCollisionAladdin() const;
	void explosionEffect() const ;
};

#endif //!__GENIE_LAMP_CONTROLLER_H__

