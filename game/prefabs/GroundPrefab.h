#ifndef __GROUND_PREFAB_H__
#define __GROUND_PREFAB_H__

#include <aladdin.h>

class GroundPrefab : public ala::Prefab
{
public:
  GroundPrefab()
    : Prefab( "Ground" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) const override;
};

#endif //!__GROUND_PREFAB_H__
