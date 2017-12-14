#include "HubPrefab.h"
#include "../Define.h"
#include "../scripts/HubController.h"
#include "../scripts/CameraFollower.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(HubPrefab, ala::PrefabV2)

void HubPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
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

  const auto livesLabel = new GameObject( object, "Hub Lives" );
  const auto livesLabelTransform = livesLabel->getTransform();
  const auto livesLableText = new BitmapText( livesLabel, "font_two.png", "two.fnt" );
  livesLabelTransform->setPosition( Vec2( aladdinHeadTransform->getPositionX() + 17, -halfVisibleHeight + 17 ) );
  livesLableText->setTextAlignment( BitmapText::LEFT );
  livesLableText->setText( "99" );

  const auto apples = new GameObject( object );
  const auto applesTransform = apples->getTransform();
  const auto applesSpriteRenderer = new SpriteRenderer( apples, "items.png" );
  const auto applesAnimator = new Animator( apples, "apple", "items.anm" );
  applesTransform->setScale( 1.5f );
  applesTransform->setPosition( Vec2( halfVisibleWidth - 55, -halfVisibleHeight + 20 ) );

  const auto applesLabel = new GameObject( object, "Hub Apples" );
  const auto applesLabelTransform = applesLabel->getTransform();
  const auto applesLableText = new BitmapText( applesLabel, "font_two.png", "two.fnt" );
  applesLabelTransform->setPosition( Vec2( applesTransform->getPositionX() + 13, -halfVisibleHeight + 18 ) );
  applesLableText->setTextAlignment( BitmapText::LEFT );
  applesLableText->setText( "99" );

  const auto scoresLabel = new GameObject( object, "Hub Scores" );
  const auto scoresLabelTransform = scoresLabel->getTransform();
  const auto scoresLableText = new BitmapText( scoresLabel, "font_one.png", "one.fnt" );
  scoresLabelTransform->setPosition( Vec2( halfVisibleWidth - 15, halfVisibleHeight - 20 ) );
  scoresLableText->setTextAlignment( BitmapText::RIGHT );
  scoresLableText->setCharacterSpacing( 2 );
  scoresLableText->setText( "9999" );

  const auto cameraFollower = new CameraFollower( object );

  const auto controller = new HubController( object );

  // configurations
  object->setTag( HUB_TAG );
  object->setLayer( "UI" );
}
