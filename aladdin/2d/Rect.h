#ifndef __ALADDIN_2D_RECT_H__
#define __ALADDIN_2D_RECT_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "2dInclude.h"
#include "Vec2.h"
#include "Size2.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Rect)
private:
  Vec2 _topLeft;
  Size2 _size;

public:
  Rect( const Vec2& topLeft = Vec2(), const Size2& size = Size2( 0, 0 ) );

  const Vec2& getTopLeft() const;

  void setTopLeft( const Vec2& topLeft );

  const Size2& getSize() const;

  void setSize( const Size2& size );
};
}

#endif //!__ALADDIN_2D_RECT_H__
