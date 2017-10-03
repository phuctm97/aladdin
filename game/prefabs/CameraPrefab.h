#ifndef __CAMERA_PREFAB_H__
#define __CAMERA_PREFAB_H__

#include <aladdin.h>

class CameraPrefab : public ala::Prefab {
public:
  CameraPrefab()
    : Prefab( "Camera" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) override;
};

#endif //!__CAMERA_PREFAB_H__
