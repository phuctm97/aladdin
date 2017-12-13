#ifndef __CAMERA_CONTROLLER_H__
#define __CAMERA_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1( CameraController, ala::GameObjectComponent)
private:
  ala::Vec2 _targetPosition;
  float _movingSpeed;

public:
  CameraController( ala::GameObject* gameObject, const std::string& name = "" );

protected:
  void onUpdate( const float delta ) override;

  void onRelease() override;
};

#endif // !__CAMERA_CONTROLLER_H__
