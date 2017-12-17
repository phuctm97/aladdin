#ifndef __CAMERA_FOLLOWER_H__
#define __CAMERA_FOLLOWER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(CameraFollower, ala::GameObjectComponent)
public:
  CameraFollower( ala::GameObject* gameObject, const std::string& name = "" );

protected:
  void onRender() override;
};

#endif //!__CAMERA_FOLLOWER_H__
