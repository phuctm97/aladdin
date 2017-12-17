#ifndef __PLATFORM_PREFAB_H__
#define __PLATFORM_PREFAB_H__

#include <aladdin.h>

class PlatformPrefab : public ala::Prefab {
public:
	PlatformPrefab() : Prefab("Platform") {};

protected:
	void doInstantiate(ala::GameObject* object) const override;
};

#endif //!__PLATFORM_PREFAB_H__