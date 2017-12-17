#ifndef __CLIMBABLE_ROPE_PREFAB_H__
#define __CLIMBABLE_ROPE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(ClimbableRopePrefab, ala::PrefabV2)
public:
  ClimbableRopePrefab() : PrefabV2( "Climbable Rope" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__CLIMBABLE_ROPE_PREFAB_H__
