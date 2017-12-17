#ifndef __ENEMY_EXPLOSION_PREFAB_2_H__
#define __ENEMY_EXPLOSION_PREFAB_2_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(EnemyExplosionTwoPrefab, ala::PrefabV2)
public:
  EnemyExplosionTwoPrefab() : PrefabV2( "Enemy Explosion 2" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};

#endif // !__ENEMY_EXPLOSION_PREFAB_2_H__
