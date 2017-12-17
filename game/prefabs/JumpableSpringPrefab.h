#ifndef __JUMPABLE_SPRING_PREFAB_H__
#define __JUMPABLE_SPRING_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JumpableSpringPrefab, ala::PrefabV2)
public:
  JumpableSpringPrefab()
    : PrefabV2( "Jumpable Spring" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__JUMPABLE_SPRING_PREFAB_H__
