#ifndef __ABU_BONUS_CONTROLLER_H__
#define __ABU_BONUS_CONTROLLER_H__

#include <aladdin.h>

class AbuBonusController : public ala::GameObjectComponent
{
private:
	bool _aladdinCollision;
protected:
	void onUpdate(const float delta) override;

public:
	AbuBonusController(ala::GameObject* gameObject, const std::string& name = "");
	bool isCollisionAladdin() const;
	void explosionEffect() const;
};

#endif //!__ABU_BONUS_CONTROLLER_H__

