#ifndef __ALADDIN_CONTROLLER_H__
#define __ALADDIN_CONTROLLER_H__

#include <aladdin.h>

class AladdinController : public ala::GameObjectComponent
{
private:
  ala::Logger _logger;
  bool _collidedWithGround;
  bool _colliedWithKnife;
  bool _aladdinPosition;

public:
  AladdinController( ala::GameObject* gameObject, const std::string& name = "" );

  bool isCollidedWithGround() const;

  bool isCollidedWithKnife() const;

  bool isAladdinRightPosition() const;

  void resetCollidedWithGround();

  void throwApple( char direction, float directX, float directY, float impulseX, float impulseY ) const;
protected:
  void onUpdate( const float delta ) override;

public:
  void onCollisionEnter( const ala::CollisionInfo& collision ) override;

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;
};

#endif //!__ALADDIN_CONTROLLER_H__
