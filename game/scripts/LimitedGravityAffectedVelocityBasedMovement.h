#ifndef __GRAVITY_VECTOR_BASED_MOVEMENT_H__
#define __GRAVITY_VECTOR_BASED_MOVEMENT_H__

#include <aladdin.h>

class LimitedGravityAffectedVelocityBasedMovement : public ala::GameObjectComponent
{
private:
  ala::Vec2 _velocity;
  float _gravity;
  float _limit;

public:
  LimitedGravityAffectedVelocityBasedMovement( ala::GameObject* gameObject, const std::string& name = "" );

  void setVelocity( const ala::Vec2& vector );

  void setVelocityX( const float x );

  void setVelocityY( const float y );

  void addVelocity( const ala::Vec2& vector );

  void addVelocityX( const float x );

  void addVelocityY( const float y );

  const ala::Vec2& getVelocity() const;

  float getGravity() const;

  float getLimit() const;

protected:
  void onUpdate( const float delta ) override;
};

#endif //!__GRAVITY_VECTOR_BASED_MOVEMENT_H__
