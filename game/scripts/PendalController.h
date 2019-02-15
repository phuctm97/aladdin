#ifndef __PENDAL_CONTROLLER_H__
#define __PENDAL_CONTROLLER_H__

#include <aladdin.h>

class PendalController : public ala::GameObjectComponent
{
private:
  ala::GameObject* _other;
  ala::GameObject* _camera;
  ala::Logger _logger;
  bool _doReset = false;
  bool _doRelease = false;
  float _visibleWidth;
  float _visibleHeight;
  ala::Vec2 _resetPoint;

public:
  PendalController( ala::GameObject* object, const string& name = "" );
  void setResetPoint( ala::Vec2 vec2 );
protected:
  void onUpdate( const float delta ) override;
  void onCollisionEnter( const ala::CollisionInfo& collision ) override;

  void getCollisionObject( const ala::CollisionInfo& collision );
};

#endif //!__PENDAL_CONTROLLER_H__
