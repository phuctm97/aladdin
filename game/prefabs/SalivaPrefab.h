#ifndef __SALIVA_PREFAB_H__
#define __SALIVA_PREFAB_H__

#include<aladdin.h>

class SalivaPrefab : ala::Prefab
{
public:
	SalivaPrefab() : Prefab("saliva") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif // !__SALIVA_PREFAB_H__

