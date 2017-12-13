#ifndef __APPLE_PREFAB_H__
#define __APPLE_PREFAB_H__

#include <aladdin.h>

class ApplePrefab : public ala::Prefab
{
public:
	ApplePrefab(): Prefab("Apple") {}

protected:
	void doInstantiate(ala::GameObject* object) const override;
};



#endif //!__APPLE_PREFAB_H__