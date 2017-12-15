#ifndef __FIRE_PREFAB_H__
#define __FIRE_PREFAB_H__

#include <aladdin.h>

class FirePrefab : public ala::Prefab
{
public:
  FirePrefab()
    : Prefab( "Fire" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) const override;
};

#endif //!__FIRE_PREFAB_H__
