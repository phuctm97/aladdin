#ifndef __GUARD_THREE_PREFAB_H__
#define __GUARD_THREE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(GuardThreePrefab, ala::PrefabV2)
public:
  GuardThreePrefab()
    : PrefabV2( "Guard 3" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__GUARD_THREE_PREFAB_H__
