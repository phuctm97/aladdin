#ifndef __THINGUARD_CONTROLLER_H__
#define __THINGUARD_CONTROLLER_H__

#include <aladdin.h>

class ThinGuardController : public ala::GameObjectComponent
{
private:
  bool _collidedWithGround;
  bool _couldAttackAladdin;
  bool _couldSeeAladdin;
  bool _onRightOfAladdin;

protected:
  void onUpdate( const float delta ) override;

public:
  ThinGuardController( ala::GameObject* gameObject, const std::string& name = "" );
  bool isCollidedWithGround() const;
  bool couldAttackAladdin() const;
  bool coundSeeAladdin() const;
  bool isOnRightOfAladdin() const;
  void onCollisionEnter( const ala::CollisionInfo& collision ) override;
};

#endif //!__THINGUARD_CONTROLLER_H__
