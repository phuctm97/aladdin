#ifndef _SPEND_THESE_PREFAB_H__
#define _SPEND_THESE_PREFAB_H__

#include<aladdin.h>

class SpendThesePrefab : ala::Prefab {
public:
	SpendThesePrefab() : Prefab("spend these") {}
protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif // !_SPEND_THESE_PREFAB_H__
