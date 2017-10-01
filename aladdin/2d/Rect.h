#ifndef __ALADDIN_2D_RECT_H__
#define __ALADDIN_2D_RECT_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "2dInclude.h"
#include "Size.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Rect)
private:
  Vec2 _topLeft;
  Size _size;

public:
  Rect( const Vec2& topLeft = Vec2(), const Size& size = Size( 0, 0 ) );

  virtual ~Rect();

  const Vec2& getTopLeft() const;

  void setTopLeft( const Vec2& topLeft );

  const Size& getSize() const;

  void setSize( const Size& size );
};
}

#endif //!__ALADDIN_2D_RECT_H__
