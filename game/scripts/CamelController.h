#ifndef __CAMEL_CONTROLLER_H__
#define __CAMEL_CONTROLLER_H__

#include <aladdin.h>

class CamelController : public ala::GameObjectComponent
{
private:
	bool _aladdinOnBack;
protected:
	void onUpdate(const float delta) override;

public:
	CamelController(ala::GameObject* gameObject, const std::string& name = "");
	bool isAladdinOnBack() const;
	void puffSaliva(float directX, float directY, float impulseX, float impulseY) const;
};

#endif //!__CAMEL_CONTROLLER_H__

