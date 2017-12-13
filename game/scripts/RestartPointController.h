#ifndef __RESTART_POINT_CONTROLLER_H__
#define __RESTART_POINT_CONTROLLER_H__

#include <aladdin.h>

class RestartPointController : public ala::GameObjectComponent
{
private:
	bool _aladdinNear;
protected:
	void onUpdate(const float delta) override;

public:
	RestartPointController(ala::GameObject* gameObject, const std::string& name = "");
	bool isNearAladdin() const;
};

#endif //!__RESTART_POINT_CONTROLLER_H__

