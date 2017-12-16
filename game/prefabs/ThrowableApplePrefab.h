#ifndef __THROWABLE_APPLE_PREFAB_H__
#define __THROWABLE_APPLE_PREFAB_H__

#include <aladdin.h>

class ThrowableApplePrefab : ala::PrefabV2
{
public:
  ThrowableApplePrefab()
    : PrefabV2( "Throwable Apple" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};


#endif //!__THROWABLE_APPLE_PREFAB_H__
