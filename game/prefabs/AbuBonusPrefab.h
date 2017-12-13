#ifndef __ABU_BONUS_PREFAB_H__
#define __ABU_BONUS_PREFAB_H__

#include<aladdin.h>

class AbuBonusPrefab : ala::Prefab {
public:
	AbuBonusPrefab() : Prefab("abu bonus") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif // !__ABU_BONUS_PREFAB_H__
