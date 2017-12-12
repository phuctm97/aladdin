#ifndef __DIRECTION_CONTROLLER_H__
#define __DIRECTION_CONTROLLER_H__

#include <aladdin.h>

class DirectionController : ala::GameObjectComponent
{
private:
  int _direction;

public:
  DirectionController( ala::GameObject* gameObject, const std::string& name = "" );

  int getDirection() const;

  void setDirection( const int direction );
};

#endif //!__DIRECTION_CONTROLLER_H__
