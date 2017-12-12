#ifndef __FAT_GUARD_CONTROLLER_H__
#define __FAT_GUARD_CONTROLLER_H__

#include "GuardController.h"

ALA_CLASS_HEADER_1(FatGuardController, GuardController)
private:
  bool _willProvokeBeforeChasing;

public:
  FatGuardController( ala::GameObject* gameObject, const std::string& name = "" );

  bool willProvokeBeforeChasing() const;

protected:
  void onUpdate( const float delta ) override;
};

#endif //!__FAT_GUARD_CONTROLLER_H__
