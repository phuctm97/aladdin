#ifndef __PLATFORM_PREFAB_H__
#define __PLATFORM_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(PlatformPrefab, ala::PrefabV2)
public:
  PlatformPrefab() : PrefabV2( "Platform" ) {};

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__PLATFORM_PREFAB_H__
