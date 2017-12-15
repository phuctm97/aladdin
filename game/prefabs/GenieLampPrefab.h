#ifndef __GENIE_LAMP_PREFAB_H__
#define __GENIE_LAMP_PREFAB_H__

#include<aladdin.h>

class GenieLampPrefab : ala::Prefab {
public:
	GenieLampPrefab() : Prefab("genie lamp") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif // !__GENIE_LAMP_PREFAB_H__
