#include "MessageArgRect.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::MessageArgRect, ala::MessageArgs)

MessageArgRect::MessageArgRect ( const Rect& rect )
  :_rect(rect)
{
}

const Rect& MessageArgRect::getRect ( ) const
{
  return _rect;
}
}
