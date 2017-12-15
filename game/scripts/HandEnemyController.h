#ifndef __HAND_ENEMY_CONTROLLER_H__
#define __HAND_ENEMY_CONTROLLER_H__

#include <aladdin.h>

class HandEnemyController : public ala::GameObjectComponent
{
private:
	bool _nearAladdin;

protected:
	void onUpdate(const float delta) override;

public:
	HandEnemyController(ala::GameObject* gameObject, const std::string& name = "");


	bool isAladdinNear() const;
	void throwVase(char direction, float directX, float directY, float impulseX, float impulseY) const;



};

#endif //!__HAND_ENEMY_CONTROLLER_H__

