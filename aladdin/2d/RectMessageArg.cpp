#include "RectMessageArg.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::RectMessageArg, ala::MessageArgs)

RectMessageArg::RectMessageArg( const Rect& rect )
  :_rect(rect)
{
}

const Rect& RectMessageArg::getRect ( ) const
{
  return _rect;
}
}
