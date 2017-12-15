#ifndef __GENIE_BONUS_CONTROLLER_H__
#define __GENIE_BONUS_CONTROLLER_H__

#include <aladdin.h>

class GenieBonusController : public ala::GameObjectComponent
{
private:
	bool _aladdinCollision;
	bool _orient;
protected:
	void onUpdate(const float delta) override;

public:
	GenieBonusController(ala::GameObject* gameObject, const std::string& name = "");
	bool isCollisionAladdin() const;
	bool getOrient() const;
	void setOrient(bool orient);
	void explosionEffect() const ;
};

#endif //!__GENIE_BONUS_CONTROLLER_H__

