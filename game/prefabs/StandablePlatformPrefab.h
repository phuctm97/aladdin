#ifndef __STANDABLE_PLATFORM_PREFAB_H__
#define __STANDABLE_PLATFORM_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(StandablePlatformPrefab, ala::PrefabV2)
public:
	StandablePlatformPrefab() : PrefabV2("Standable Platform") {}

protected:
	void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif // !__STANDABLE_PLATFORM_PREFAB_H__
