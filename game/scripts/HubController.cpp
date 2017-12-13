#include "HubController.h"
#include "AladdinController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

HubController::HubController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ) {}

void HubController::setLives( const int lives ) const {
  const auto gameManager = GameManager::get();
  const auto livesHub = gameManager->getObjectByName( "Hub Lives" );

  std::stringstream stringBuilder;
  stringBuilder << lives;

  livesHub->getComponentT<BitmapText>()->setText( stringBuilder.str() );
}

void HubController::setApples( const int apples ) const {
  const auto gameManager = GameManager::get();
  const auto applesHub = gameManager->getObjectByName( "Hub Apples" );

  std::stringstream stringBuilder;
  stringBuilder << apples;

  applesHub->getComponentT<BitmapText>()->setText( stringBuilder.str() );
}

void HubController::setScores( const int scores ) const {
  const auto gameManager = GameManager::get();
  const auto scoresHub = gameManager->getObjectByName( "Hub Scores" );
  const auto text = scoresHub->getComponentT<BitmapText>();

  if ( scores > 0 ) {
    std::stringstream stringBuilder;
    stringBuilder << scores;

    text->setVisible( true );
    text->setText( stringBuilder.str() );
  }
  else {
    text->setVisible( false );
  }
}

void HubController::onUpdate( const float delta ) {
  const auto aladdin = GameManager::get()->getObjectByTag( ALADDIN_TAG );
  if ( aladdin == NULL ) return;

  const auto aladdinController = static_cast<AladdinController*>(aladdin->getComponent( "Controller" ));
  if ( aladdinController == NULL ) return;

  setLives( aladdinController->getLives() );
  setApples( aladdinController->getApples() );
}
