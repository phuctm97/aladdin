#ifndef __FALLING_VASE_PREFAB_H__
#define __FALLING_VASE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(FallingVasePrefab, ala::PrefabV2)
public:
  FallingVasePrefab() : PrefabV2( "Falling Vase" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__FALLING_VASE_PREFAB_H__
