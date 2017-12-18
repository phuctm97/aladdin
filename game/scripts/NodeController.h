#ifndef __NODE_CONTROLLER_H_
#define __NODE_CONTROLLER_H_

#include <aladdin.h>


class NodeController : public ala::GameObjectComponent
{
private:
	ala::Logger _logger;
	float _speed;
	ala::GameObject* _rectObject;
	int _appleCount;
	float _appleX[100];
	float _appleY[100];

public: 
	NodeController(ala::GameObject*  gameObject, const std::string& name = "");



protected:
	void onUpdate(const float delta) override;

  bool onPreInitialize() override;
};


#endif // !__NODE_CONTROLLER_H_