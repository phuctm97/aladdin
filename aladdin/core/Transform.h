/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_TRANSFORM2_H__
#define __ALADDIN_CORE_TRANSFORM2_H__

#include "../core/GameObjectComponent.h"
#include "Vec2.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Transform, ala::GameObjectComponent)
private:
  Vec2 _position;
  Vec2 _scale;
  float _rotation;

public:
  Transform( GameObject* gameObject, const std::string& name = "" );

  const Vec2& getPosition() const;

  float getPositionX() const;

  float getPositionY() const;

  void setPosition( const Vec2& position );

  void setPositionX( float x );

  void setPositionY( float y );

  const Vec2& getScale() const;

  void setScale( const Vec2& scale );

  float getRotation() const;

  void setRotation( float rotation );
};
}

#endif //!__ALADDIN_CORE_TRANSFORM2_H__
