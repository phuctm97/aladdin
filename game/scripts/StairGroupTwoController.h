#ifndef __STAIR_GROUP_TWO_CONTROLLER_H__
#define __STAIR_GROUP_TWO_CONTROLLER_H__

#include <aladdin.h>

class StairGroupTwoController : ala::GameObjectComponent
{
private:
	ala::GameObject* _other;
	bool _isStairActive = false;
	void getCollisionObject(const ala::CollisionInfo & collision);

public:
	StairGroupTwoController(ala::GameObject* gameObject, const string& name = "") :
		GameObjectComponent(gameObject, name) {};

	void setStairActive(bool active);
protected:
	void onTriggerEnter(const ala::CollisionInfo& collision) override;
};


#endif //!__STAIR_GROUP_TWO_CONTROLLER_H__