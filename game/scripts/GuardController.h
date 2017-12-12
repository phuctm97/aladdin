#ifndef __GUARD_CONTROLLER_H__
#define __GUARD_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1( GuardController, ala::GameObjectComponent)
private:
  float _initialX;
  float _minX;
  float _maxX;

protected:
  int _state;

public:
  GuardController( ala::GameObject* gameObject, const std::string& name = "" );

  float getInitialX() const;
  float getMinX() const;
  float getMaxX() const;
  void set( const float initialX, const float minX, const float maxX );

  bool isIdling() const;
  bool isChasingAladdin() const;
  bool isAttacking() const;

protected:
  void onInitialize() override;

  void onUpdate( const float delta ) override;

public:
  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

private:
  void onHit();
};

#endif //!__GUARD_CONTROLLER_H__
