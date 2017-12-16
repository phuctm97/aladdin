#ifndef __PENDAL_CONTROLLER_H__
#define __PENDAL_CONTROLLER_H__

#include <aladdin.h>

class PendalController : public ala::GameObjectComponent
{
private:
	ala::GameObject* _other;
	ala::GameObject* _camera;
	ala::Logger _logger;
	bool checkReset = false;
	float _visibleWidth;
	float _visibleHeight;

public:
	PendalController(ala::GameObject* object, const string& name = "");
protected:
	void onUpdate(const float delta) override;
	void onCollisionEnter(const ala::CollisionInfo& collision) override;

	void getCollisionObject(const ala::CollisionInfo& collision);
};

#endif //!__PENDAL_CONTROLLER_H__