#ifndef __ONE_WAY_PLATFORM_V2_PREFAB_H__
#define __ONE_WAY_PLATFORM_V2_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(OneWayPlatformV2Prefab, ala::PrefabV2)
public:
  OneWayPlatformV2Prefab()
    : PrefabV2( "One Way Platform V2" ) {}

private:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__ONE_WAY_PLATFORM_V2_PREFAB_H__
