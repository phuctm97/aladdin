#ifndef __STAIR_ONE_PREFAB_H__
#define __STAIR_ONE_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(StairOnePrefab, ala::PrefabV2)
public:
  StairOnePrefab() : PrefabV2( "Stair 1" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__STAIR_ONE_PREFAB_H__
