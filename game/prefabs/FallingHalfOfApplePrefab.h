#ifndef __FALLING_HALF_OF_APPLE_PREFAB_H__
#define __FALLING_HALF_OF_APPLE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(FallingHalfOfApplePrefab, ala::PrefabV2)
public:
  FallingHalfOfApplePrefab()
    : PrefabV2( "Falling Half Of Apple" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__FALLING_HALF_OF_APPLE_PREFAB_H__
