#ifndef __BOX_COLLIDER_H__
#define __BOX_COLLIDER_H__

#include <aladdin.h>

class BoxCollider : public ala::GameObjectComponent
{
private:
  ala::Size _size;
  bool _debugDraw;

public:
  BoxCollider( ala::GameObject* gameObject, const ala::Size& size, const std::string& name = "" );

  const ala::Size& getSize() const;

  void setSize( const ala::Size& size );

  bool getDebugDraw() const;

  void setDebugDraw( const bool debugDraw );
};

#endif //!__BOX_COLLIDER_H__
