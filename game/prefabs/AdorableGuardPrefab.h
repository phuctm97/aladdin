#ifndef __ADORABLEGUARD_APPLE_PREFAB_H__
#define __ADORABLEGUARD_APPLE_PREFAB_H__
#include <aladdin.h>

class AdorableGuardPrefab : ala::Prefab
{
public:
	AdorableGuardPrefab()
		: Prefab("Adorable Guard") {}


protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif //__ADORABLEGUARD_APPLE_PREFAB_H__

