#ifndef __GUARD_FOUR_PREFAB_H__
#define __GUARD_FOUR_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(GuardFourPrefab, ala::PrefabV2)
public:
  GuardFourPrefab()
    : PrefabV2( "Guard 4" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__GUARD_FOUR_PREFAB_H__
