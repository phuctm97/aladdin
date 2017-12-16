#ifndef __WALL_PREFAB_H__
#define __WALL_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(WallPrefab, ala::PrefabV2)
public:
  WallPrefab()
    : PrefabV2( "Wall" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif //!__WALL_PREFAB_H__
