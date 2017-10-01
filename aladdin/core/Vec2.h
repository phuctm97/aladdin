/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_VEC2_H__
#define __ALADDIN_CORE_VEC2_H__

#include "Base.h"

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

#endif //!__ALADDIN_CORE_VEC2_H__
