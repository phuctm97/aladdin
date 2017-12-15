#ifndef __ENEMY_EXPLOSION_H__
#define __ENEMY_EXPLOSION_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1( EnemyExplosionPrefab, ala::PrefabV2)
public:
  EnemyExplosionPrefab()
    : PrefabV2( "Enemy Explosion" ) {}

protected:
  void doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const override;
};


#endif //!__ENEMY_EXPLOSION_H__
