#include "CharcoalBurnerController.h"

USING_NAMESPACE_ALA;

CharcoalBurnerController::CharcoalBurnerController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _firing( false ) {}

void CharcoalBurnerController::onTriggerEnter( const ala::CollisionInfo& collision ) { }

void CharcoalBurnerController::onTriggerStay( const ala::CollisionInfo& collision ) { }

void CharcoalBurnerController::onTriggerExit( const ala::CollisionInfo& collision ) { }
