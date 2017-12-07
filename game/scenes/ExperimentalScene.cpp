/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ExperimentalScene.h"
#include "../scripts/CameraController.h"
#include "../scripts/NodeController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ExperimentalScene::ExperimentalScene() : _logger( "ExperimentalScene" ) {}

void ExperimentalScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();

  // configurations
  enablePhysics( Vec2( 0, -500.0f ) );
  new CameraController( getMainCamera() );

  // initial objects
  const auto background = new GameObject( this, "Background" );
  background->setTag( BACKGROUND_TAG );

  const auto backgroundSpriteRenderer = new SpriteRenderer( background, "background.png" );
  background->setLayer( "Background" );
  background->getTransform()->setPosition(
    Vec2( backgroundSpriteRenderer->getFrameSize().getWidth() / 2,
          backgroundSpriteRenderer->getFrameSize().getHeight() / 2 )
    - Vec2( gameManager->getVisibleWidth() / 2,
            gameManager->getVisibleHeight() / 2 ) );


  const auto foreground = new GameObject( this, "Foreground" );
  foreground->setTag( FOREGROUND_TAG );

  const auto foregroundSpriteRenderer = new SpriteRenderer( foreground, "foreground.png" );
  foreground->setLayer( "Foreground" );
  foreground->getTransform()->setPosition(
    Vec2( foregroundSpriteRenderer->getFrameSize().getWidth() / 2,
          foregroundSpriteRenderer->getFrameSize().getHeight() / 2 )
    - Vec2( gameManager->getVisibleWidth() / 2,
            gameManager->getVisibleHeight() / 2 ) );

  const auto ground = gameManager->getPrefab( "Ground" )->instantiate( "Ground" );

  const auto ropeOne = gameManager->getPrefab( "Rope" )->instantiate( "Rope 1" );
  ropeOne->getTransform()->setPosition( Vec2( 1931, 86 ) );
  ropeOne->getComponentT<Collider>()->setSize( Size( 5, 250 ) );

  const auto ropeTwo = gameManager->getPrefab( "Rope" )->instantiate( "Rope 2" );
  ropeTwo->getTransform()->setPosition( Vec2( 1387, 298 ) );
  ropeTwo->getComponentT<Collider>()->setSize( Size( 5, 193 ) );

  const auto ropeThree = gameManager->getPrefab( "Rope" )->instantiate( "Rope 3" );
  ropeThree->getTransform()->setPosition( Vec2( 2539, 345 ) );
  ropeThree->getComponentT<Collider>()->setSize( Size( 5, 249 ) );

  const auto ropeFour = gameManager->getPrefab( "Rope" )->instantiate( "Rope 4" );
  ropeFour->getTransform()->setPosition( Vec2( 4555, 99 ) );
  ropeFour->getComponentT<Collider>()->setSize( Size( 5, 193 ) );

  const auto charcoalBurnerOne = gameManager->getPrefab( "Charcoal Burner" )->instantiate( "Charcoal Burner 1" );
  charcoalBurnerOne->getTransform()->setPosition( Vec2( 360.5f, -50 ) );

  const auto charcoalBurnerTwo = gameManager->getPrefab( "Charcoal Burner" )->instantiate( "Charcoal Burner 2" );
  charcoalBurnerTwo->getTransform()->setPosition( Vec2( 730.5f, -50 ) );

  const auto charcoalBurnerThree = gameManager->getPrefab( "Charcoal Burner" )->instantiate( "Charcoal Burner 3" );
  charcoalBurnerThree->getTransform()->setPosition( Vec2( 906.5f, -50 ) );

  const auto aladdin = gameManager->getPrefab( "Aladdin" )->instantiate( "Aladdin" );
  aladdin->getTransform()->setPosition( Vec2( -80, -25 ) );
}

void ExperimentalScene::onPreRelease() {}
