#include "HubPrefab.h"
#include "../scripts/HubController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

HubPrefab::HubPrefab(): Prefab( "Hub" ) {}

void HubPrefab::doInstantiate( ala::GameObject* object ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto visibleWidth = gameManager->getVisibleWidth();
  const auto visibleHeight = gameManager->getVisibleHeight();
  const auto halfVisibleWidth = visibleWidth / 2;
  const auto halfVisibleHeight = visibleHeight / 2;

  // components
  const auto aladdinHead = new GameObject( object );
  const auto aladdinHeadTransform = aladdinHead->getTransform();
  const auto aladdinHeadSpriteRenderer = new SpriteRenderer( aladdinHead, "items.png" );
  const auto aladdinHeadAnimator = new Animator( aladdinHead, "aladdin_head", "items.anm" );
  aladdinHeadTransform->setPosition( Vec2( -halfVisibleWidth + 20, -halfVisibleHeight + 20 ) );

  const auto livesNumberOne = new GameObject( object, "Hub Lives 1" );
  const auto livesNumberOneTransform = livesNumberOne->getTransform();
  const auto livesNumberOneSpriteRenderer = new SpriteRenderer( livesNumberOne, "numbers.png" );
  const auto livesNumberOneAnimator = new Animator( livesNumberOne, "0", "numbers.anm" );
  livesNumberOneTransform->setPosition( Vec2(
    aladdinHeadTransform->getPositionX() + aladdinHeadSpriteRenderer->getFrameSize().getWidth() / 2 + 13,
    -halfVisibleHeight + 20 ) );

  const auto livesNumberTwo = new GameObject( object, "Hub Lives 2" );
  const auto livesNumberTwoTransform = livesNumberTwo->getTransform();
  const auto livesNumberTwoSpriteRenderer = new SpriteRenderer( livesNumberTwo, "numbers.png" );
  const auto livesNumberTwoAnimator = new Animator( livesNumberTwo, "0", "numbers.anm" );
  livesNumberTwoTransform->setPosition( Vec2(
    livesNumberOneTransform->getPositionX() + livesNumberOneSpriteRenderer->getFrameSize().getWidth() / 2 + 10,
    -halfVisibleHeight + 20 ) );

  const auto apples = new GameObject( object );
  const auto applesTransform = apples->getTransform();
  const auto applesSpriteRenderer = new SpriteRenderer( apples, "items.png" );
  const auto applesAnimator = new Animator( apples, "apple", "items.anm" );
  applesTransform->setPosition( Vec2( halfVisibleWidth - 55, -halfVisibleHeight + 20 ) );

  const auto applesNumberOne = new GameObject( object, "Hub Apples 1" );
  const auto applesNumberOneTransform = applesNumberOne->getTransform();
  const auto applesNumberOneSpriteRenderer = new SpriteRenderer( applesNumberOne, "numbers.png" );
  const auto applesNumberOneAnimator = new Animator( applesNumberOne, "0", "numbers.anm" );
  applesNumberOneTransform->setPosition( Vec2(
    applesTransform->getPositionX() + applesSpriteRenderer->getFrameSize().getWidth() / 2 + 13,
    -halfVisibleHeight + 20 ) );

  const auto applesNumberTwo = new GameObject( object, "Hub Apples 2" );
  const auto applesNumberTwoTransform = applesNumberTwo->getTransform();
  const auto applesNumberTwoSpriteRenderer = new SpriteRenderer( applesNumberTwo, "numbers.png" );
  const auto applesNumberTwoAnimator = new Animator( applesNumberTwo, "0", "numbers.anm" );
  applesNumberTwoTransform->setPosition( Vec2(
    applesNumberOneTransform->getPositionX() + applesNumberOneSpriteRenderer->getFrameSize().getWidth() / 2 + 10,
    -halfVisibleHeight + 20 ) );

  const auto controller = new HubController( object, "Controller" );

  // configurations
  object->setTag( HUB_TAG );
  object->setLayer( "UI" );
  controller->setLives( 3 );
  controller->setApples( 5 );
}
