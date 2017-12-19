#include "JafarPrefab.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarPrefab, ala::PrefabV2)

void JafarPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto minIdle1Delay = 300;
  const auto maxIdle1Delay = 1000;
  const auto minIdle2Delay = 300;
  const auto maxIdle2Delay = 1000;
  const auto minAttackDelay = 1000;
  const auto maxAttackDelay = 2300;
  const auto bodyOffset1 = Vec2( 0, 0 );
  const auto bodySize1 = Size( 35, 70 );
  const auto bodyOffset2 = Vec2( 15, 0 );
  const auto bodySize2 = Size( 60, 70 );
  std::vector<float> firePositions = { -8, -8 + 18 * 1, -8 + 18 * 2 };

  // components

  const auto spriteRenderer = new SpriteRenderer( object, "jafar.png" );
  spriteRenderer->setZOrder( 1 );

  const auto animator = new Animator( object, "jafar_1_attack", "jafar.anm" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 60, 70 ), 1, 0 );

  const auto stateManager = new StateManager( object, "idle_1" );

  std::vector<SpriteRenderer*> fireSprites;
  for ( const auto firePos : firePositions ) {
    const auto fire = new GameObject( object );
    const auto fireSpriteRenderer = new SpriteRenderer( fire, "jafar.png" );
    const auto fireAnimator = new Animator( fire, "fire_loop", "jafar.anm" );
    fire->getTransform()->setPosition( firePos, -14 );
    fire->setLayer( "Supporting Character" );
    fireSpriteRenderer->setZOrder( 2 );

    fireSprites.push_back( fireSpriteRenderer );
  }

  // helpers
  const auto timer = new Timer( object );

  const auto transform = object->getTransform();

  // collider renderers
  const auto colliderRenderer = new ColliderRenderer( collider );
  colliderRenderer->setZOrder( 3 );

  // configurations
  object->setLayer( "Supporting Character" );

  // states
  new State( stateManager, "idle_1",
             [=] {
               // animation effect
               {
                 if ( stateManager->getPreviousStateName() == "attack_1" ) {
                   animator->setAction( "jafar_1_attack_to_idle" );
                 }
                 else {
                   animator->setAction( "jafar_1_idle" );
                 }
               }

               // transition
               {
                 timer->start( (rand() % (maxIdle1Delay - minIdle1Delay) + minIdle1Delay) / 1000.0f );
               }

               // body
               {
                 collider->setOffset( bodyOffset1 );
                 collider->setSize( bodySize1 );
               }

               // fires
               {
                 for ( const auto fireSprite : fireSprites ) fireSprite->setVisible( false );
               }
             }, NULL, NULL );

  new State( stateManager, "attack_1",
             [=] {
               // animation effect
               {
                 animator->setAction( "jafar_1_attack" );
               }

               // transition
               {
                 timer->start( (rand() % (maxAttackDelay - minAttackDelay) + minAttackDelay) / 1000.0f );
               }
             }, NULL, NULL );

  // states
  new State( stateManager, "idle_2",
             [=] {
               // animation effect
               {
                 animator->setAction( "jafar_2_idle" );
               }

               // transition
               {
                 timer->start( (rand() % (maxIdle2Delay - minIdle2Delay) + minIdle2Delay) / 1000.0f );
               }

               // body
               {
                 collider->setOffset( bodyOffset2 );
                 collider->setSize( bodySize2 );
               }

               // fires
               {
                 for ( const auto fireSprite : fireSprites ) fireSprite->setVisible( true );
               }
             }, NULL, NULL );

  new State( stateManager, "attack_2",
             [=] {
               // animation effect
               {
                 animator->setAction( "jafar_2_attack" );
               }
             }, NULL, NULL );

  new StateTransition( stateManager, "idle_1", "attack_1", [=] {
    return timer->isDone() && !animator->isPlaying();
  } );

  new StateTransition( stateManager, "attack_1", "idle_1", [=] {
    return timer->isDone() && !animator->isPlaying();
  } );

  new StateTransition( stateManager, "idle_2", "attack_2", [=] {
    return timer->isDone();
  } );

  new StateTransition( stateManager, "attack_2", "idle_2", [=] {
    return !animator->isPlaying();
  } );

  // TODO: debug
  new StateTransition( stateManager, "idle_1", "idle_2", [=] {
    return Input::get()->getKeyDown( ALA_KEY_SPACE );
  } );

  new StateTransition( stateManager, "idle_2", "idle_1", [=] {
    return Input::get()->getKeyDown( ALA_KEY_SPACE );
  } );
}
