#ifndef __APPLE_PREFAB_H__
#define __APPLE_PREFAB_H__
#include "core/Prefab.h"
#include <aladdin.h>

class Throwable_applePrefab : ala::Prefab
{
public:
	Throwable_applePrefab()
		: Prefab("throwable_apple") {}

protected:
	void doInstantiate(ala::GameObject* object) const override;
};



#endif //!__APPLE_PREFAB_H__
