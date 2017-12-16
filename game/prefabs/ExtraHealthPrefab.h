#ifndef _EXTRA_HEALTH_PREFAB_H__
#define _EXTRA_HEALTH_PREFAB_H__

#include<aladdin.h>

class ExtraHealthPrefab : ala::Prefab {
public:
	ExtraHealthPrefab() : Prefab("extra health") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif // !_EXTRA_HEALTH_PREFAB_H__
