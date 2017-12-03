#ifndef __THROWABLE_KNIFE_PREFAB_H__
#define __THROWABLE_KNIFE_PREFAB_H__

#include <aladdin.h>

class ThrowableKnifePrefab : ala::Prefab
{
public:
	ThrowableKnifePrefab()
		: Prefab("Throwable Knife") {}

protected:
	void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__THROWABLE_KNIFE_PREFAB_H__

