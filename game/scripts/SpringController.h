#ifndef __SPRING_CONTROLLER_H__
#define __SPRING_CONTROLLER_H__

#include <aladdin.h>

class SpringController : public ala::GameObjectComponent
{
private:
	bool _aladdinOnBack;
protected:
	void onUpdate(const float delta) override;

public:
	SpringController(ala::GameObject* gameObject, const std::string& name = "");
	bool isAladdinOnBack() const;
};

#endif //!__SPRING_CONTROLLER_H__

