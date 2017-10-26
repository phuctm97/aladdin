#ifndef __ALADDIN_PHYSICS_RIGIDBODY_H__
#define __ALADDIN_PHYSICS_RIGIDBODY_H__

#include "PhysicsInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Rigidbody, ala::GameObjectComponent)
private:
  Vec2 _position;
  Vec2 _velocity;

  int _bodyType;
  
  float _mass;

  float _gravityScale;

  Vec2 _forces;
  Vec2 _impulses;
public:
  Rigidbody(GameObject* gameObject, const std::string& name = "");

  void onPhysicsUpdate(const float delta) override;

  void addForce(const Vec2 &force);
  void addImpulse(const Vec2 &impulse);

  void setPosition(const Vec2& position);
  void setVelocity(const Vec2& velocity);
  void setBodyType(const int bodyType);
  void setMass(const float mass);
  void setGravityScale(const float gravityScale);

  const Vec2& getPosition() const;
  const Vec2& getVelocity() const;
  const int getBodyType() const;
  const float getMass() const;
  const float getGravityScale() const;

  void onInitialize() override;;

  void onRelease() override;

  virtual ~Rigidbody();
};
}
#endif //!__ALADDIN_PHYSICS_RIGIDBODY_H__