#ifndef __EATABLE_HEART_PREFAB_H__
#define __EATABLE_HEART_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(EatableHeartPrefab, ala::PrefabV2)
public:
  EatableHeartPrefab() : PrefabV2( "Eatable Heart" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__EATABLE_HEART_PREFAB_H__
