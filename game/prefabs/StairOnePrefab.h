#ifndef __STAIR_ONE_PREFAB_H__
#define __STAIR_ONE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(StairOnePrefab, ala::Prefab)
public:
  StairOnePrefab() : Prefab( "Stair 1" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) const override;
};

#endif //!__STAIR_ONE_PREFAB_H__
