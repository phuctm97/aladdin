/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_2D_TRANSFORM2_H__
#define __ALADDIN_2D_TRANSFORM2_H__

#include "2dInclude.h"
#include "../core/GameObjectComponent.h"
#include "Vec2.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Transform2, ala::GameObjectComponent)
private:
  Vec2 _position;
  Vec2 _scale;
  float _rotation;

public:
  Transform2( GameObject* gameObject, const std::string& name = "" );

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

#endif //!__ALADDIN_2D_TRANSFORM2_H__
