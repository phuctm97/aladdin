#include "PeddlerTextPrefab.h"
#include "../scripts/CameraFollower.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PeddlerTextPrefab, ala::PrefabV2)

void PeddlerTextPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = ala::GameManager::get();

  // components
  const auto container = new GameObject( object );

  const auto cameraFollower = new CameraFollower( object );

  const auto text = new ala::BitmapText( container, "font_one.png", "one.fnt" );
  text->setTextAlignment( ala::BitmapText::CENTER );
  text->setCharacterAlignment( ala::BitmapText::TOP );
  text->setCharacterSpacing( 6 );
  text->setText( "FIND MORE GEMS" );

  const auto actionManager = new ala::ActionManager( container );

  const auto stateManager = new ala::StateManager( container, "blink" );

  // helpers
  const auto timer = new ala::Timer( container );

  const auto transform = container->getTransform();

  // configurations
  transform->setScale( 1.5f );
  transform->setPosition( 0, 50 );
  container->setLayer( "UI" );
  object->setLayer( "UI" );

  // states
  new ala::State( stateManager, "blink", [=] {
    actionManager->play( new ala::Blink( 0.5f, -1 ) );
  }, NULL, NULL );

  new ala::State( stateManager, "gone", [=] {
                    actionManager->stopAll();
                    actionManager->play( new ala::MoveBy( -2000, 5 ) );
                    timer->start( 5 );
                  }, [=]( float dt ) {
                    text->setVisible( true );

                    if ( timer->isDone() ) {
                      object->release();
                    }
                  }, NULL );

  new ala::StateTransition( stateManager, "blink", "gone", [=] {
    return ala::Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW ) || ala::Input::get()->getKeyDown( ALA_KEY_RIGHT_ARROW );
  } );
}
