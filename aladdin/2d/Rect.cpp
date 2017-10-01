/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Rect )

Rect::Rect( const Vec2& topLeft, const Size& size ): _topLeft( topLeft ),
                                                     _size( size ) {}

Rect::~Rect() {}

const Vec2& Rect::getTopLeft() const {
  return _topLeft;
}

void Rect::setTopLeft( const Vec2& topLeft ) {
  _topLeft = topLeft;
}

const Size& Rect::getSize() const {
  return _size;
}

void Rect::setSize( const Size& size ) {
  _size = size;
}
}
