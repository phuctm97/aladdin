#ifndef __THINGUARD_APPLE_PREFAB_H__
#define __THINGUARD_APPLE_PREFAB_H__

#include <aladdin.h>
class ThinGuardPrefab : ala::Prefab
{
public:
	ThinGuardPrefab()
		: Prefab("Thin Guard") {}


protected:
	void doInstantiate(ala::GameObject* object) const override;
};


#endif //__THINGUARD_APPLE_PREFAB_H__

