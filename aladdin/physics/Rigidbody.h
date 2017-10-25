#ifndef __ALADDIN_PHYSICS_RIGIDBODY_H__
#define __ALADDIN_PHYSICS_RIGIDBODY_H__

#include "../core/GameObjectComponent.h"
#include "../core/Vec2.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Rigidbody, ala::GameObjectComponent)
private:
  Vec2 _position;
  Vec2 _velocity;
  Vec2 _accelerator;
public:

};
}
#endif //!__ALADDIN_PHYSICS_RIGIDBODY_H__