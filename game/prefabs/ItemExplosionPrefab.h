#ifndef __ITEM_EXPLOSION_PREFAB_H__
#define __ITEM_EXPLOSION_PREFAB_H__

#include<aladdin.h>

class ItemExplosionPrefab : ala::Prefab {
public:
	ItemExplosionPrefab() : Prefab("item explosion") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif // !__ITEM_EXPLOSION_PREFAB_H__
