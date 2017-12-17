#ifndef __GUARD_CONTROLLER_H__
#define __GUARD_CONTROLLER_H__

#include <aladdin.h>
#include "DirectionController.h"

ALA_CLASS_HEADER_1(GuardController, ala::GameObjectComponent)
private:
  float _minDistanceCouldAttack;
  float _maxDistanceCouldAttack;
  float _tooFarDistance;

  float _initialX;
  float _leftBoundX;
  float _rightBoundX;

  int _health;

  ala::Transform* _aladdinTransform;
  ala::Transform* _selfTransform;
  ala::StateManager* _selfStateManager;
  DirectionController* _selfDirection;

  ala::PrefabV2* _enemyExplosionOnePrefab;
  ala::PrefabV2* _enemyExplosionTwoPrefab;

public:
  GuardController( ala::GameObject* gameObject, const std::string& name = "" );

  bool isTooFarFromAladdin() const;

  bool isAbleToSeeAladdin() const;

  char getDirectionToGoToAttackAladdin() const;

  char getDirectionToFaceToAladdin() const;

  bool isAbleToAttackAladdin() const;

  bool isAbleToGoLeft() const;

  bool isAbleToGoRight() const;

  void keepInBound() const;

  float getInitialX() const;

  void setInitialX( const float initialX );

  float getLeftBoundX() const;

  void setLeftBoundX( const float leftBoundX );

  float getRightBoundX() const;

  void setRightBoundX( const float rightBoundX );

  float getMinDistanceCouldAttack() const;

  void setMinDistanceCouldAttack( const float minDistanceCouldAttack );

  float getMaxDistanceCouldAttack() const;

  void setMaxDistanceCouldAttack( const float maxDistanceCouldAttack );

  int getHealth() const;

  void setHealth( const int health );

protected:
  void onInitialize() override;

public:
  void onDie( const int explosionType = 1 ) const;

  void onHit();

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;
};

#endif //!__GUARD_CONTROLLER_H__
