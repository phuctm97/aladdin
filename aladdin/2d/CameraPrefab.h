#ifndef __CAMERA_PREFAB_H__
#define __CAMERA_PREFAB_H__

#include "2dInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1 ( CameraPrefab, Prefab )
public:
  CameraPrefab()
    : Prefab( "MainCamera" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) override;
};
}

#endif //!__CAMERA_PREFAB_H__
