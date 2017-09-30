#include "Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Rect, "ala::Rect" )

Rect::Rect( const Vec2& topLeft, const Size2& size ): _topLeft( topLeft ),
                                                      _size( size ) {}

const Vec2& Rect::getTopLeft() const {
  return _topLeft;
}

void Rect::setTopLeft( const Vec2& topLeft ) {
  _topLeft = topLeft;
}

const Size2& Rect::getSize() const {
  return _size;
}

void Rect::setSize( const Size2& size ) {
  _size = size;
}
}
