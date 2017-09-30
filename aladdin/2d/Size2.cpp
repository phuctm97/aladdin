/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Size2.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Size2, "ala::Size2" )

Size2::Size2( float x, float y ) : _width( x ),
                                   _height( y ) {}

float Size2::getWidth() const {
  return _width;
}

void Size2::setWidth( float x ) {
  _width = x;
}

float Size2::getHeight() const {
  return _height;
}

void Size2::setHeight( float y ) {
  _height = y;
}
}
