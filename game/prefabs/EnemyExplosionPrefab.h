#ifndef __ENEMY_EXPLOSION_H__
#define __ENEMY_EXPLOSION_H__

#include <aladdin.h>

class EnemyExplosionPrefab : public ala::Prefab
{
public:
  EnemyExplosionPrefab()
    : Prefab( "Enemy Explosion" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) const override;
};


#endif //!__ENEMY_EXPLOSION_H__
