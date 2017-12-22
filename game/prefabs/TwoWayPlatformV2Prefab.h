#ifndef __TWO_WAY_PLATFORM_V2_PREFAB_H__
#define __TWO_WAY_PLATFORM_V2_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(TwoWayPlatformV2Prefab, ala::PrefabV2)
public:
  TwoWayPlatformV2Prefab()
    : PrefabV2( "Two Way Platform V2" ) {}

private:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__TWO_WAY_PLATFORM_V2_PREFAB_H__
