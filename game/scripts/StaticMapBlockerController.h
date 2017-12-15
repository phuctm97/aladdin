#ifndef __STATIC_MAP_BLOCKER_CONTROLLER_H__
#define __STATIC_MAP_BLOCKER_CONTROLLER_H__

#include <aladdin.h>

class StaticMapBlockerController : ala::GameObjectComponent
{
private:

	ala::GameObject* _other; 
	ala::Logger _logger;
	void getCollisionObject(const ala::CollisionInfo& collision);

public:
	StaticMapBlockerController(ala::GameObject* gameObject, const string& name = "");

protected:

	void onCollisionEnter(const ala::CollisionInfo& collision) override;
	void onCollisionStay(const ala::CollisionInfo& collision) override;
	void onCollisionExit(const ala::CollisionInfo& collision) override;

};


#endif //!__STATIC_MAP_BLOCKER_CONTROLLER_H__