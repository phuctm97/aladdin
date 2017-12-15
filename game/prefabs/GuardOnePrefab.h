#ifndef __GUARD_ONE_PREFAB_H__
#define __GUARD_ONE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(GuardOnePrefab, ala::PrefabV2)
public:
  GuardOnePrefab()
    : PrefabV2( "Guard 1" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};


#endif //!__GUARD_ONE_PREFAB_H__
