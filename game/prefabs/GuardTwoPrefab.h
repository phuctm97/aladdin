#ifndef __GUARD_TWO_PREFAB_H__
#define __GUARD_TWO_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(GuardTwoPrefab, ala::PrefabV2)
public:
  GuardTwoPrefab()
    : PrefabV2( "Guard 2" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__GUARD_TWO_PREFAB_H__
