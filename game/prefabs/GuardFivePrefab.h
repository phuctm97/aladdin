#ifndef __GUARD_FIVE_H__
#define __GUARD_FIVE_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(GuardFivePrefab, ala::PrefabV2)
public:
  GuardFivePrefab()
    : PrefabV2( "Guard 5" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__GUARD_FIVE_H__
