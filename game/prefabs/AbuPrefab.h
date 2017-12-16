#ifndef __ABU_PREFAB_H__
#define __ABU_PREFAB_H__

#include<aladdin.h>

class AbuPrefab : ala::Prefab {
public:
	AbuPrefab() : Prefab("abu"){}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif // !__ABU_PREFAB_H__
