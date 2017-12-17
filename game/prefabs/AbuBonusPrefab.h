#ifndef __ABU_BONUS_PREFAB_H__
#define __ABU_BONUS_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AbuBonusPrefab, ala::PrefabV2)
public:
  AbuBonusPrefab() : PrefabV2( "Abu Bonus" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__ABU_BONUS_PREFAB_H__
