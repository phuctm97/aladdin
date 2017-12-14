#include "HubController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

HubController::HubController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _livesLabel( NULL ), _applesLabel( NULL ), _scoresLabel( NULL ),
    _aladdinController( NULL ) {}

void HubController::setLives( const int lives ) const {
  std::stringstream stringBuilder;
  stringBuilder << lives;

  _livesLabel->setText( stringBuilder.str() );
}

void HubController::setApples( const int apples ) const {
  std::stringstream stringBuilder;
  stringBuilder << apples;

  _applesLabel->setText( stringBuilder.str() );
}

void HubController::setScores( const int scores ) const {
  if ( scores > 0 ) {
    std::stringstream stringBuilder;
    stringBuilder << scores;

    _scoresLabel->setVisible( true );
    _scoresLabel->setText( stringBuilder.str() );
  }
  else {
    _scoresLabel->setVisible( false );
  }
}

void HubController::onInitialize() {
  const auto gameManager = GameManager::get();
  const auto livesHub = gameManager->getObjectByName( "Hub Lives" );
  _livesLabel = livesHub->getComponentT<BitmapText>();

  const auto applesHub = gameManager->getObjectByName( "Hub Apples" );
  _applesLabel = applesHub->getComponentT<BitmapText>();

  const auto scoresHub = gameManager->getObjectByName( "Hub Scores" );
  _scoresLabel = applesHub->getComponentT<BitmapText>();

  const auto aladdin = GameManager::get()->getObjectByTag( ALADDIN_TAG );
  if ( aladdin != NULL ) {
    _aladdinController = aladdin->getComponentT<PlayableAladdinController>();
  }
}

void HubController::onUpdate( const float delta ) {
  setLives( _aladdinController->getLives() );
  setApples( _aladdinController->getApples() );
}
