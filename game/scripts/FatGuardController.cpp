#include "FatGuardController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(FatGuardController, GuardController)

FatGuardController::FatGuardController( ala::GameObject* gameObject, const std::string& name )
  : GuardController( gameObject, name ), _willProvokeBeforeChasing( false ) {}

bool FatGuardController::willProvokeBeforeChasing() const {
  return _willProvokeBeforeChasing;
}

void FatGuardController::onUpdate( const float delta ) {
  GuardController::onUpdate( delta );
  _willProvokeBeforeChasing = rand() % 5 < 2;
}
