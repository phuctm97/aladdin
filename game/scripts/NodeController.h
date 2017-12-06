#ifndef __NODE_CONTROLLER_H_
#define __NODE_CONTROLLER_H_

#include <aladdin.h>


class NodeController : public ala::GameObjectComponent
{
private:
	ala::Logger _logger;
	int _speed = 1;

public: 
	NodeController(ala::GameObject*  gameObject, const std::string& name = "");



protected:
	void onUpdate(const float delta) override;

};


#endif // !__NODE_CONTROLLER_H_