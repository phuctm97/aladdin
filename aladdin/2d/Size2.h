#ifndef __ALADDIN_2D_SIZE2_H__
#define __ALADDIN_2D_SIZE2_H__

#include "2dInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Size2)
private:
  float _width;
  float _height;

public:
  Size2( float x, float y );

  float getWidth() const;

  void setWidth( float x );

  float getHeight() const;

  void setHeight( float y );
};
}

#endif //!__ALADDIN_2D_SIZE2_H__
