#ifndef __HAND_ENEMY_PREFAB_H__
#define __HAND_ENEMY_PREFAB_H__

#include<aladdin.h>

class HandEnemyPrefab : ala::Prefab
{
public:
	HandEnemyPrefab() : Prefab("Hand Enemy") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif // !__HAND_ENEMY_PREFAB_H__

