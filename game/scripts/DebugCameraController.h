#ifndef __DEBUG_CAMERA_CONTROLLER_H__
#define __DEBUG_CAMERA_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(DebugCameraController, ala::GameObjectComponent)
private:
  float _speed;
  ala::Logger _logger;
  ala::GameObject* _target;
  ala::GameObject* _backupTarget;

public:
  DebugCameraController( ala::GameObject* gameObject, ala::GameObject* target = NULL, const std::string& name = "" );

protected:
  void onUpdate( const float delta ) override;
};


#endif //__DEBUG_CAMERA_CONTROLLER_H__
