/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Vec2.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Vec2 )

Vec2::Vec2( float x, float y ): _x( x ),
                                _y( y ) {}

Vec2::~Vec2() {}

float Vec2::getX() const {
  return _x;
}

void Vec2::setX( float x ) {
  _x = x;
}

float Vec2::getY() const {
  return _y;
}

void Vec2::setY( float y ) {
  _y = y;
}
}
