#ifndef __THROWABLE_KNIFE_PREFAB_H__
#define __THROWABLE_KNIFE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(ThrowableKnifePrefab, ala::PrefabV2)
public:
  ThrowableKnifePrefab()
    : PrefabV2( "Throwable Knife" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};


#endif //!__THROWABLE_KNIFE_PREFAB_H__
