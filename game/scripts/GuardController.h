#ifndef __GUARD_CONTROLLER_H__
#define __GUARD_CONTROLLER_H__

#include <aladdin.h>

class GuardController : public ala::GameObjectComponent
{
private:
  bool _couldAttackAladdin;
  bool _couldSeeAladdin;
  bool _onRightOfAladdin;
  bool _tooFarFromAladdin;
  float _initialX;
  float _minX;
  float _maxX;

public:
  GuardController( ala::GameObject* gameObject, const std::string& name = "" );
  bool couldAttackAladdin() const;
  bool couldSeeAladdin() const;
  bool isOnRightOfAladdin() const;
  bool isTooFarFromAladdin() const;

  float getInitialX() const;
  void setInitialX( const float initialX );
  float getMinX() const;
  void setMinX( const float minX );
  float getMaxX() const;
  void setMaxX( const float maxX );
  void set( const float initialX, const float minX, const float maxX );

protected:
  void onUpdate( const float delta ) override;

public:
  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

private:
  void onHit();
};

#endif //!__GUARD_CONTROLLER_H__
