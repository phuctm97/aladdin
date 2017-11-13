#include "AladdinController.h"

USING_NAMESPACE_ALA;

AladdinController::AladdinController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _logger( "AladdinController" ),
    _walkSpeed( 5 ) {}

void AladdinController::onUpdate( const float delta ) {
}
