#ifndef __FATGUARD_APPLE_PREFAB_H__
#define __FATGUARD_APPLE_PREFAB_H__

#include <aladdin.h>
class FatGuardPrefab : ala::Prefab
{
public:
	FatGuardPrefab()
		: Prefab("Fat Guard") {}


protected:
	void doInstantiate(ala::GameObject* object) const override;
};


#endif //__FATGUARD_APPLE_PREFAB_H__
