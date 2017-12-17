#ifndef __ENEMY_EXPLOSION_ONE_H__
#define __ENEMY_EXPLOSION_ONE_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1( EnemyExplosionOnePrefab, ala::PrefabV2)
public:
  EnemyExplosionOnePrefab()
    : PrefabV2( "Enemy Explosion 1" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};


#endif //!__ENEMY_EXPLOSION_ONE_H__
