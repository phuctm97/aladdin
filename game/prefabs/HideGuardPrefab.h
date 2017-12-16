#ifndef __HIDEGUARD_APPLE_PREFAB_H__
#define __HIDEGUARD_APPLE_PREFAB_H__

#include <aladdin.h>

class HideGuardPrefab : ala::Prefab
{
public:
	HideGuardPrefab()
		: Prefab("Hide Guard") {}


protected:
	void doInstantiate(ala::GameObject* object) const override;
};


#endif //__HIDEGUARD_APPLE_PREFAB_H__

