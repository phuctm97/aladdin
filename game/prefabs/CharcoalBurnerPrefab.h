#ifndef __CHARCOAL_BURNER_PREFAB_H__
#define __CHARCOAL_BURNER_PREFAB_H__

#include <aladdin.h>

class CharcoalBurnerPrefab : ala::Prefab
{
public:
  CharcoalBurnerPrefab()
    : Prefab( "Charcoal Burner" ) {}


protected:
  void doInstantiate( ala::GameObject* object ) const override;
};

#endif //!__CHARCOAL_BURNER_PREFAB_H__
