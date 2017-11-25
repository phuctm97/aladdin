#ifndef __THROWABLE_APPLE_CONTROLLER_H__
#define __THROWABLE_APPLE_CONTROLLER_H__

#include <aladdin.h>

class ThrowableAppleController : public ala::GameObjectComponent
{
private:
  bool _collidedWithGround;
  bool _colliedWithEnemy;

public:
  ThrowableAppleController( ala::GameObject* gameObject, const std::string& name = "" );

  bool isCollidedWithGround() const;

  bool isCollidedWithEnemy() const;

  void resetCollidedWithGround();

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;
};

#endif //!__THROWABLE_APPLE_CONTROLLER_H__
