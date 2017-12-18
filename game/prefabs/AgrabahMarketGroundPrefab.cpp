#include "AgrabahMarketGroundPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AgrabahMarketGroundPrefab, ala::PrefabV2)

void AgrabahMarketGroundPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto halfVisibleSize = Size( gameManager->getVisibleWidth() / 2, gameManager->getVisibleHeight() / 2 );

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );
  const auto transform = object->getTransform();

#pragma region ground

  // first ground
  const auto firstGroundSize = Size( 1475 - 5 - 20, 63 );
  const auto firstGroundOffset = Vec2( firstGroundSize.getWidth() / 2 - 5 - 10, firstGroundSize.getHeight() / 2 );
  const auto firstGroundCollider = new Collider( object, false, firstGroundOffset, firstGroundSize );
  firstGroundCollider->setTag( GROUND_TAG );


  // second ground
  const auto secondGroundSize = Size( 768, 33 );
  const auto secondGroundOffset = Vec2( firstGroundSize.getWidth() + secondGroundSize.getWidth() / 2,
                                        secondGroundSize.getHeight() / 2 );
  const auto secondGroundCollider = new Collider( object, false, secondGroundOffset, secondGroundSize );
  secondGroundCollider->setTag( GROUND_TAG );

  // third ground
  const auto thirdGroundSize = Size( 578, 22 );
  const auto thirdGroundOffset = Vec2(
    secondGroundOffset.getX() + secondGroundSize.getWidth() / 2 + thirdGroundSize.getWidth() / 2,
    thirdGroundSize.getHeight() / 2 );
  const auto thirdGroundCollider = new Collider( object, false, thirdGroundOffset, thirdGroundSize );
  thirdGroundCollider->setTag( GROUND_TAG );


  // fourth ground
  const auto fourthGroundSize = Size( 1975, 30 );
  const auto fourthGroundOffset = Vec2(
    thirdGroundOffset.getX() + thirdGroundSize.getWidth() / 2 + fourthGroundSize.getWidth() / 2,
    fourthGroundSize.getHeight() / 2 );
  const auto fourthGroundCollider = new Collider( object, false, fourthGroundOffset, fourthGroundSize );
  fourthGroundCollider->setTag( GROUND_TAG );

#pragma endregion

#pragma region wall

  const auto mapBlockerSize = Size( 20, 688 );

  const auto mapStartBlocker = new Collider( object, false,
                                             Vec2( firstGroundOffset.getX() - firstGroundSize.getWidth() / 2 -
                                                   mapBlockerSize.getWidth() / 2 + 10,
                                                   firstGroundOffset.getY() - firstGroundSize.getHeight() / 2 +
                                                   mapBlockerSize.getHeight() / 2 ),
                                             mapBlockerSize );

  const auto mapEndBlocker = new Collider( object, false,
                                           Vec2( fourthGroundOffset.getX() + fourthGroundSize.getWidth() / 2 +
                                                 mapBlockerSize.getWidth() / 2,
                                                 fourthGroundOffset.getY() - fourthGroundSize.getHeight() / 2 +
                                                 mapBlockerSize.getHeight() / 2 ),
                                           mapBlockerSize );


#pragma endregion

  // configurations
  object->setTag( GROUND_TAG );
  object->setLayer( "Debug" );

  transform->setPosition( Vec2( -halfVisibleSize.getWidth(),
                                -halfVisibleSize.getHeight() ) );

  // collider renderers
  new ColliderRenderer( firstGroundCollider );
  new ColliderRenderer( secondGroundCollider );
  new ColliderRenderer( thirdGroundCollider );
  new ColliderRenderer( fourthGroundCollider );
  new ColliderRenderer( mapStartBlocker );
  new ColliderRenderer( mapEndBlocker );
}
