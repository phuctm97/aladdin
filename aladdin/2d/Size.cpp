/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Size.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Size, "ala::Size" )

Size::Size( float x, float y ) : _width( x ),
                                 _height( y ) {}

float Size::getWidth() const {
  return _width;
}

void Size::setWidth( float x ) {
  _width = x;
}

float Size::getHeight() const {
  return _height;
}

void Size::setHeight( float y ) {
  _height = y;
}
}
