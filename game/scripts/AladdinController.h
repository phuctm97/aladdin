#ifndef __ALADDIN_CONTROLLER_H__
#define __ALADDIN_CONTROLLER_H__

#include <aladdin.h>

class AladdinController : public ala::GameObjectComponent
{
private:
  ala::Logger _logger;
  bool _collidedWithGround;
  bool _colliedWithKnife;
  int _health;
  int _lives;
  int _apples;
  bool _recovering;

public:
  AladdinController( ala::GameObject* gameObject, const std::string& name = "" );

  bool isCollidedWithGround() const;

  bool isCollidedWithKnife() const;

  void resetCollidedWithGround();

  void throwApple( char direction, float directX, float directY, float impulseX, float impulseY );

  void setLives( const int lives );

  int getLives() const;

  void setApples( const int apples );

  int getApples() const;

  void setHealth( const int health );

  int getHealth() const;

  bool isRecovering() const;

  void setRecovering();

protected:
  void onUpdate( const float delta ) override;

public:
  void onCollisionEnter( const ala::CollisionInfo& collision ) override;

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

  void onTriggerStay( const ala::CollisionInfo& collision ) override;
private:
  void onHitCharcoalBurner( ala::GameObject* burnerObject );
};

#endif //!__ALADDIN_CONTROLLER_H__
