#ifndef __THROW_VASE_PREFAB_H__
#define __THROW_VASE_PREFAB_H__

#include<aladdin.h>

class ThrowVasePrefab : ala::Prefab
{
public:
	ThrowVasePrefab() : Prefab( "Throw Vase" ) {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif // !__THROW_VASE_PREFAB_H__

