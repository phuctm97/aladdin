#ifndef __PLAYABLE_ALADDIN_CONTROLLER_H__
#define __PLAYABLE_ALADDIN_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1( PlayableAladdinController, ala::GameObjectComponent)
private:
  int _health;
  int _lives;
  int _apples;
  bool _recovering;
  bool _jumpingOnCamel;

  ala::Transform* _selfTransform;
  ala::ActionManager* _selfActionManager;
  ala::StateManager* _selfStateManager;
  ala::Collider* _selfBodyCollider;
  ala::PrefabV2* _throwableApplePrefab;

public:
  PlayableAladdinController( ala::GameObject* gameObject, const std::string& name = "" );

  void setLives( const int lives );

  int getLives() const;

  void setApples( const int apples );

  int getApples() const;

  void setHealth( const int health );

  int getHealth() const;

  bool isRecovering() const;

  void setRecovering();

  void resetJumpingOnCamel();

  bool isJumpingOnCamel() const;

  void throwApple( const char direction,
                   const float offsetX, const float offsetY,
                   const float impulseX, const float impulseY );

  void onCollisionEnter( const ala::CollisionInfo& collision ) override;

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

  void onTriggerStay( const ala::CollisionInfo& collision ) override;

  void onTriggerExit( const ala::CollisionInfo& collision ) override;

protected:
  void onInitialize() override;

private:
  void onHitCharcoalBurner();

  void onHit( const int damage = 1 );

  void onJumpingOnCamel();
};

#endif //!__PLAYABLE_ALADDIN_CONTROLLER_H__
