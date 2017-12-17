#ifndef __CHARCOAL_BURNER_PREFAB_H__
#define __CHARCOAL_BURNER_PREFAB_H__

#include <aladdin.h>

class CharcoalBurnerPrefab : ala::PrefabV2
{
public:
  CharcoalBurnerPrefab()
    : PrefabV2( "Charcoal Burner" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__CHARCOAL_BURNER_PREFAB_H__
