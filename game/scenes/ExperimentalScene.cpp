/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ExperimentalScene.h"
#include "../scripts/CameraController.h"
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
  const auto backgroundSpriteRenderer = new SpriteRenderer( background, "background.png" );
  background->setLayer( "Background" );
  background->getTransform()->setPosition(
    Vec2( backgroundSpriteRenderer->getFrameSize().getWidth() / 2,
          backgroundSpriteRenderer->getFrameSize().getHeight() / 2 )
    - Vec2( gameManager->getVisibleWidth() / 2,
            gameManager->getVisibleHeight() / 2 ) );


  const auto foreground = new GameObject( this, "Foreground" );
  const auto foregroundSpriteRenderer = new SpriteRenderer( foreground, "foreground.png" );
  foreground->setLayer( "Foreground" );
  foreground->getTransform()->setPosition(
    Vec2( foregroundSpriteRenderer->getFrameSize().getWidth() / 2,
          foregroundSpriteRenderer->getFrameSize().getHeight() / 2 )
    - Vec2( gameManager->getVisibleWidth() / 2,
            gameManager->getVisibleHeight() / 2 ) );


  const auto aladdin = gameManager->getPrefab( "Aladdin" )->instantiate( "Aladdin" );
  aladdin->setTag(ALADDIN_TAG);
  aladdin->setLayer( "Character" );
  aladdin->getTransform()->setPosition( Vec2( 500, -40 ) );

 /* const auto thin_enemy = gameManager->getPrefab("Thin Guard")->instantiate("Thin Guard");
  thin_enemy->setLayer("Enemy");
  thin_enemy->getTransform()->setPosition(Vec2(200, -40));
*/
  /*const auto fat_enemy = gameManager->getPrefab("Fat Guard")->instantiate("Fat Guard");
  fat_enemy->setLayer("Enemy");
  fat_enemy->getTransform()->setPosition(Vec2(500, -60));*/

  const auto adorable_enemy = gameManager->getPrefab("Adorable Guard")->instantiate("Adorable Guard");
  adorable_enemy->setLayer("Enemy");
  adorable_enemy->getTransform()->setPosition(Vec2(200, -40));

  const auto ground = gameManager->getPrefab( "Ground" )->instantiate( "Ground" );
  ground->setTag(GROUND_TAG);
}

void ExperimentalScene::onPreRelease() {}
