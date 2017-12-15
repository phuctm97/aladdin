#ifndef __SPRING_PREFAB_H__
#define __SPRING_PREFAB_H__

#include<aladdin.h>

class SpringPrefab : ala::Prefab
{
public:
	SpringPrefab() : Prefab("spring") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif // !__SPRING_PREFAB_H__

