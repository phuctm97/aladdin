#ifndef __GENIE_BONUS_PREFAB_H__
#define __GENIE_BONUS_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(GenieBonusPrefab, ala::PrefabV2)
public:
  GenieBonusPrefab()
    : PrefabV2( "Genie Bonus" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__GENIE_BONUS_PREFAB_H__
