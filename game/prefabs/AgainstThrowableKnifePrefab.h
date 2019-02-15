#ifndef __AGAINST_THROWABLE_KNIFE_PREFAB_H__
#define __AGAINST_THROWABLE_KNIFE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AgainstThrowableKnifePrefab, ala::PrefabV2)
public:
  AgainstThrowableKnifePrefab()
    : PrefabV2( "Against Throwable Knife" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};


#endif //!__AGAINST_THROWABLE_KNIFE_PREFAB_H__
