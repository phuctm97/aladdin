#ifndef __STATIC_PLATFORM_PREFAB_H__
#define __STATIC_PLATFORM_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(StaticPlatformPrefab, ala::PrefabV2)
public:
	StaticPlatformPrefab() : PrefabV2("Static Platform") {}

protected:
	void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif // !__STATIC_PLATFORM_PREFAB_H__
