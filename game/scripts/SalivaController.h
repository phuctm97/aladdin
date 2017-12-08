#ifndef __SALIVA_CONTROLLER_H__
#define __SALIVA_CONTROLLER_H__

#include <aladdin.h>

class SalivaController : public ala::GameObjectComponent
{
protected:
	void onUpdate(const float delta) override;

public:
	SalivaController(ala::GameObject* gameObject, const std::string& name = "");

};

#endif //!__CAMEL_CONTROLLER_H__

