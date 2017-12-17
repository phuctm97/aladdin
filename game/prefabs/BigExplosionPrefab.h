#ifndef __BIG_EXPLOSION_PREFAB_H__
#define __BIG_EXPLOSION_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(BigExplosionPrefab, ala::PrefabV2)
public:
  BigExplosionPrefab() : PrefabV2( "Big Explosion" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__BIG_EXPLOSION_PREFAB_H__
