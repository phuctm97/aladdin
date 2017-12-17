#ifndef __EATABLE_APPLE_PREFAB_H__
#define __EATABLE_APPLE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1( EatableApplePrefab, ala::PrefabV2)
public:
  EatableApplePrefab(): PrefabV2( "Eatable Apple" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};


#endif //!__EATABLE_APPLE_PREFAB_H__
