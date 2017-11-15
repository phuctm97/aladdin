#ifndef __ALADDIN_CONTROLLER_H__
#define __ALADDIN_CONTROLLER_H__

#include <aladdin.h>

class AladdinController : public ala::GameObjectComponent
{
private:
  ala::Logger _logger;
  bool _collidedWithGround;

public:
  AladdinController( ala::GameObject* gameObject, const std::string& name = "" );

  bool isCollidedWithGround() const;

  void resetCollidedWithGround();

protected:
  void onUpdate( const float delta ) override;

public:
  void onCollisionEnter( const ala::CollisionInfo& collision ) override;
};

#endif //!__ALADDIN_CONTROLLER_H__
