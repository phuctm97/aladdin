#ifndef __GUARD_CONTROLLER_H__
#define __GUARD_CONTROLLER_H__

#include <aladdin.h>
#include "DirectionController.h"

ALA_CLASS_HEADER_1(GuardController, ala::GameObjectComponent)
private:
  float _minDistanceXCouldAttack;
  float _maxDistanceXCouldAttack;
  float _minDistanceYCouldAttack;
  float _maxDistanceYCouldAttack;
  float _tooFarDistance;

  float _initialX;
  float _leftBoundX;
  float _rightBoundX;

  int _health;
  bool _hitable;

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

  bool isInBestPositionToAttackAladdin() const;

  bool isAbleToGoLeft() const;

  bool isAbleToGoRight() const;

  void keepInBound() const;

  float getInitialX() const;

  void setInitialX( const float initialX );

  float getLeftBoundX() const;

  void setLeftBoundX( const float leftBoundX );

  float getRightBoundX() const;

  void setRightBoundX( const float rightBoundX );

  float getMinDistanceXCouldAttack() const;

  void setMinDistanceXCouldAttack( const float minDistanceCouldAttack );

  float getMaxDistanceXCouldAttack() const;

  void setMaxDistanceXCouldAttack( const float maxDistanceCouldAttack );

  float getMinDistanceYCouldAttack() const;

  void setMinDistanceYCouldAttack( const float minDistanceYCouldAttack );

  float getMaxDistanceYCouldAttack() const;

  void setMaxDistanceYCouldAttack( const float maxDistanceYCouldAttack );

  int getHealth() const;

  void setHealth( const int health );

  bool isHitable() const;

  void setHitable( const bool v );

protected:
  void onInitialize() override;

public:
  void onDie( const int explosionType = 1 ) const;

  void onHit();

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;
};

#endif //!__GUARD_CONTROLLER_H__
