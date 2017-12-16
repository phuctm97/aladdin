#ifndef __EXPLOSION_PREFAB_H__
#define __EXPLOSION_PREFAB_H__

#include<aladdin.h>

class ExplosionPrefab : ala::Prefab {
public:
	ExplosionPrefab() : Prefab("explosion") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif // !__EXPLOSION_PREFAB_H__
