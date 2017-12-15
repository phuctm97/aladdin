#ifndef __HAND_ENEMY_CONTROLLER_H__
#define __HAND_ENEMY_CONTROLLER_H__

#include <aladdin.h>
#include "DirectionController.h"

class HandEnemyController : public ala::GameObjectComponent
{
private:
  bool _aladdinInZone;

  ala::Transform* _selfTransform;
  DirectionController* _selfDirection;
  ala::Collider* _selfBodyCollider;

  ala::PrefabV2* _enemyExplosionPrefab;
  ala::PrefabV2* _fallingVasePrefab;

public:
  HandEnemyController( ala::GameObject* gameObject, const std::string& name = "" );

  bool isAladdinInZone() const;

  void throwVase( const float directX, const float directY ) const;

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

  void onTriggerExit( const ala::CollisionInfo& collision ) override;

  void onDie() const;

protected:
  void onInitialize() override;
};

#endif //!__HAND_ENEMY_CONTROLLER_H__
