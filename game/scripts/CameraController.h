#ifndef __CAMERA_CONTROLLER_H__
#define __CAMERA_CONTROLLER_H__


#include <aladdin.h>

class CameraController : ala::GameObjectComponent
{
public:
  // ReSharper disable CppNonExplicitConvertingConstructor
  CameraController( ala::GameObject* gameObject, const std::string& name = "" );

protected:
  void onUpdate( const float delta ) override;

  void onRelease() override;
};

#endif // !__CAMERA_CONTROLLER_H__
