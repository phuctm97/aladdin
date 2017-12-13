#ifndef __STAIR_PREFAB_H__
#define __STAIR_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(StairPrefab, ala::Prefab)
public:
  StairPrefab() : Prefab( "Stair" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) const override;
};

#endif //!__STAIR_PREFAB_H__
