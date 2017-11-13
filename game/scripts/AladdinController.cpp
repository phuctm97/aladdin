#include "AladdinController.h"

USING_NAMESPACE_ALA;

AladdinController::AladdinController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _logger( "AladdinController" ),
    _walkSpeed( 5 ) {}

void AladdinController::onUpdate( const float delta ) {
  const auto transform = getGameObject()->getTransform();
  const auto input = Input::get();

  if ( input->getKey( ALA_KEY_A ) ) transform->setPositionX( transform->getPositionX() - _walkSpeed );
  if ( input->getKey( ALA_KEY_D ) ) transform->setPositionX( transform->getPositionX() + _walkSpeed );
  if ( input->getKey( ALA_KEY_S ) ) transform->setPositionY( transform->getPositionY() - _walkSpeed );
  if ( input->getKey( ALA_KEY_W ) ) transform->setPositionY( transform->getPositionY() + _walkSpeed );
  if ( input->getKey( ALA_KEY_SPACE ) )
    _logger.info( "(%f, %f)", transform->getPositionX(), transform->getPositionY() );
}
