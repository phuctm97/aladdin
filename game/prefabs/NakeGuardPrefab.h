#ifndef __NAKEGUARD_APPLE_PREFAB_H__
#define __NAKEGUARD_APPLE_PREFAB_H__

#include <aladdin.h>

class NakeGuardPrefab : ala::Prefab
{
public:
	NakeGuardPrefab()
		: Prefab("Nake Guard") {}


protected:
	void doInstantiate(ala::GameObject* object) const override;
};


#endif //__NAKEGUARD_APPLE_PREFAB_H__


