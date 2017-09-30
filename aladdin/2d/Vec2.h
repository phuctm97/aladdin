#ifndef __ALADDIN_2D_VEC2_H__
#define __ALADDIN_2D_VEC2_H__

#include "2dInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Vec2)
private:
  float _x;
  float _y;

public:
  Vec2( float x = 0, float y = 0 );

  float getX() const;

  void setX( float x );

  float getY() const;

  void setY( float y );
};
}

#endif //!__ALADDIN_2D_VEC2_H__
