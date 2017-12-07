#include "HubController.h"

USING_NAMESPACE_ALA;

HubController::HubController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ) {}

void HubController::setLives( const int lives ) const {
  const auto gameManager = GameManager::get();
  const auto firstNumber = gameManager->getObjectByName( "Hub Lives 1" );
  const auto firstSpriteRenderer = firstNumber->getComponentT<SpriteRenderer>();
  const auto firstAnimator = firstNumber->getComponentT<Animator>();

  const auto secondNumber = gameManager->getObjectByName( "Hub Lives 2" );
  const auto secondSpriteRenderer = secondNumber->getComponentT<SpriteRenderer>();
  const auto secondAnimator = secondNumber->getComponentT<Animator>();

  const auto filteredLives = MAX(MIN(lives, 99), 0);
  const auto first = filteredLives / 10;
  const auto second = filteredLives % 10;

  std::stringstream stringBuilder;
  if ( first == 0 ) {
    secondSpriteRenderer->setVisible( false );

    stringBuilder << second;
    firstAnimator->setAction( stringBuilder.str() );
  }
  else {
    secondSpriteRenderer->setVisible( true );

    stringBuilder << first;
    firstAnimator->setAction( stringBuilder.str() );
    stringBuilder.str( "" );
    stringBuilder << second;
    secondAnimator->setAction( stringBuilder.str() );
  }
}

void HubController::setApples( const int apples ) const {
  const auto gameManager = GameManager::get();
  const auto firstNumber = gameManager->getObjectByName( "Hub Apples 1" );
  const auto firstSpriteRenderer = firstNumber->getComponentT<SpriteRenderer>();
  const auto firstAnimator = firstNumber->getComponentT<Animator>();

  const auto secondNumber = gameManager->getObjectByName( "Hub Apples 2" );
  const auto secondSpriteRenderer = secondNumber->getComponentT<SpriteRenderer>();
  const auto secondAnimator = secondNumber->getComponentT<Animator>();

  const auto filteredApples = MAX(MIN(apples, 99), 0);
  const auto first = filteredApples / 10;
  const auto second = filteredApples % 10;

  std::stringstream stringBuilder;
  if ( first == 0 ) {
    secondSpriteRenderer->setVisible( false );

    stringBuilder << second;
    firstAnimator->setAction( stringBuilder.str() );
  }
  else {
    secondSpriteRenderer->setVisible( true );

    stringBuilder << first;
    firstAnimator->setAction( stringBuilder.str() );
    stringBuilder.str( "" );
    stringBuilder << second;
    secondAnimator->setAction( stringBuilder.str() );
  }
}

void HubController::onRender() {
  const auto gameManager = GameManager::get();
  const auto visibleWidth = gameManager->getVisibleWidth();
  const auto visibleHeight = gameManager->getVisibleHeight();
  const auto halfVisibleWidth = visibleWidth / 2;
  const auto halfVisibleHeight = visibleHeight / 2;

  const auto camera = gameManager->getMainCamera();
  const auto cameraPosition = camera == NULL ? Vec2() : camera->getTransform()->getPosition();
  getGameObject()->getTransform()->setPosition( cameraPosition );
}
