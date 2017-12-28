#include "PlayableAladdinController.h"
#include "DirectionController.h"
#include "../Define.h"
#include "../scenes/AutoLoadScene.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PlayableAladdinController, ala::GameObjectComponent)

PlayableAladdinController::
PlayableAladdinController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _maxHealth( 99 ), _maxLives( 99 ), _maxApples( 99 ), _maxGems( 99 ),
    _health( 0 ), _lives( 0 ), _apples( 0 ), _gems( 0 ),
    _recovering( false ),
    _hit( false ),
    _jumpOnCamel( false ), _jumpOnSpring( false ),
    _pushingWall( false ),
    _reachedTopOfRope( false ),
    _holdingRope( NULL ), _holdingBar( NULL ), _collidedWithStandable( false ), _maxMovingVelocityX( 200.0f ),
    _movingVelocityX( 0 ), _dampVelocitiesSize( 0 ),
    _selfTransform( NULL ),
    _selfActionManager( NULL ), _selfStateManager( NULL ), _selfAnimator( NULL ), _selfBodyCollider( NULL ),
    _selfBody( NULL ), _selfDirection( NULL ),
    _throwableApplePrefab( NULL ), _throwableKnifePrefab( NULL ), _myAppData( NULL ),
    _sceneFadeOutTransitionPrefab( NULL ) {}

float PlayableAladdinController::getMovingVelocityX() const {
  return _movingVelocityX;
}

void PlayableAladdinController::setMovingVelocityX( const float v ) {
  _movingVelocityX = v;
}

void PlayableAladdinController::setLives( const int lives ) {
  _lives = MIN(lives, _maxLives);
}

int PlayableAladdinController::getLives() const {
  return _lives;
}

void PlayableAladdinController::setApples( const int apples ) {
  _apples = MIN(apples, _maxApples);
}

int PlayableAladdinController::getApples() const {
  return _apples;
}

int PlayableAladdinController::getGems() const {
  return _gems;
}

void PlayableAladdinController::setGems( const int gems ) {
  _gems = MIN( gems, _maxGems);
}

void PlayableAladdinController::setHealth( const int health ) {
  _health = MIN( health, _maxHealth);
}

int PlayableAladdinController::getHealth() const {
  return _health;
}

bool PlayableAladdinController::isRecovering() const {
  return _recovering;
}

void PlayableAladdinController::setRecovering() {
  if ( _recovering ) return;

  _recovering = true;

  _selfActionManager->play( new Sequence( {
    new Blink( 0.05f, 10 ),
    new CallFunc( [this] {
      _recovering = false;
      _hit = false;
    } )
  } ) );
}

void PlayableAladdinController::resetJumpOnCamel() {
  _jumpOnCamel = false;
}

bool PlayableAladdinController::isJumpOnCamel() const {
  return _jumpOnCamel;
}

void PlayableAladdinController::resetJumpOnSpring() {
  _jumpOnSpring = false;
}

bool PlayableAladdinController::isJumpOnSpring() const {
  return _jumpOnSpring;
}

void PlayableAladdinController::resetHit() {
  _hit = false;
}

bool PlayableAladdinController::isHit() const {
  return _hit;
}

bool PlayableAladdinController::isPushingWall() const {
  return _pushingWall;
}

void PlayableAladdinController::resetHoldingRope() {
  _holdingRope = NULL;
  _reachedTopOfRope = false;
}

bool PlayableAladdinController::isHoldingRope() const {
  return _holdingRope != NULL;
}

bool PlayableAladdinController::hasReachedTopOfRope() const {
  return _reachedTopOfRope;
}

void PlayableAladdinController::resetHoldingBar() {
  _holdingBar = NULL;
}

bool PlayableAladdinController::isHoldingBar() const {
  return _holdingBar != NULL;
}

ala::GameObject* PlayableAladdinController::getHoldingBar() const {
  return _holdingBar;
}

void PlayableAladdinController::resetCollidedWithStandable() {
  _collidedWithStandable = false;
}

bool PlayableAladdinController::isCollidedWithStandable() const {
  return _collidedWithStandable;
}

ala::GameObject* PlayableAladdinController::getHodingRope() const {
  return _holdingRope;
}

void PlayableAladdinController::throwApple( const char direction,
                                            const float offsetX, const float offsetY,
                                            const float impulseX, const float impulseY ) {
  if ( _apples <= 0 ) return;
  _apples -= 1;

  std::stringstream argsStream;
  argsStream << direction << ' ' << impulseX << ' ' << impulseY;

  _throwableApplePrefab->instantiateWithArgs( argsStream.str() )
                       ->getTransform()
                       ->setPosition( _selfTransform->getPosition() +
                         Vec2( _selfBodyCollider->getSize().getWidth() / 2 + offsetX,
                               _selfBodyCollider->getSize().getHeight() / 2 + offsetY ) );
}

void PlayableAladdinController::addDampVelocity( const float v, const float duration ) {
  if ( _dampVelocitiesSize < 100 ) {
    _dampVelocities[_dampVelocitiesSize++] = std::make_pair( duration, v );
  }
}

void PlayableAladdinController::onCollisionEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == WALL_TAG && otherCollider->getTag() == WALL_TAG
    && collision.getNormal().getY() == 0 ) {
    _pushingWall = true;
  }
  else if ( otherCollider->hasFlag( STANDABLE_FLAG ) ) {
    const auto colliderPosY = otherObject->getTransform()->getPositionY() + otherCollider->getOffset().getY();

    if ( colliderPosY < _selfTransform->getPositionY() ) {
      _collidedWithStandable = true;
    }
  }
}

void PlayableAladdinController::onCollisionExit( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == WALL_TAG && otherCollider->getTag() == WALL_TAG ) {
    _pushingWall = false;
  }
}

void PlayableAladdinController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();
  const auto selfCollider = collision.getColliderA() == otherCollider
                              ? collision.getColliderB()
                              : collision.getColliderA();

  if ( selfCollider->getTag() == ALADDIN_TAG ) {
    if ( otherObject->getTag() == ENEMY_TAG &&
      (otherCollider->getTag() == SWORD_TAG || otherCollider->getTag() == KNIFE_TAG) ) {
      onHit();
    }
    else if ( otherObject->getTag() == VASE_TAG ) {
      onHit();
    }
    else if ( otherObject->getTag() == CAMEL_TAG && otherCollider->getTag() == CAMEL_TAG ) {
      if ( collision.getNormal() == Vec2( 0, 1 ) ) {
        onJumpOnCamel();
      }
    }
    else if ( otherObject == _holdingRope && otherCollider->getName() == "T" ) {
      _reachedTopOfRope = true;
    }
  }
  else if ( selfCollider->getTag() == SWORD_TAG ) {
    if ( otherCollider->getTag() == KNIFE_TAG && otherObject->getTag() == ENEMY_TAG ) {
      if ( _selfDirection->isRight() ) {
        _throwableKnifePrefab->instantiateWithArgs( "R 6000 14000" )
                             ->getTransform()->setPosition( otherObject->getTransform()->getPosition() );
      }
      else {
        _throwableKnifePrefab->instantiateWithArgs( "L 6000 14000" )
                             ->getTransform()->setPosition( otherObject->getTransform()->getPosition() );
      }
    }
  }

  if ( otherObject->getTag() == APPLE_TAG ) {
    setApples( getApples() + 1 );
  }
  else if ( otherObject->getTag() == HEART_TAG ) {
    setHealth( getHealth() + 1 );
  }
  else if ( otherObject->getTag() == SPEND_TAG ) {
    setGems( getGems() + 1 );
  }

}

void PlayableAladdinController::onTriggerStay( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  const auto selfCollider = collision.getColliderA() == otherCollider
                              ? collision.getColliderB()
                              : collision.getColliderA();

  if ( selfCollider->getTag() == ALADDIN_TAG ) {
    if ( otherObject->getTag() == CHARCOAL_BURNER_TAG ) {
      onHitCharcoalBurner();
    }
    else if ( otherObject->getTag() == ROPE_TAG ) {
      if ( !isHoldingRope() ) {
        if ( otherCollider->getName() == "M"
          && ABS(_selfTransform->getPositionX() - otherObject->getTransform()->getPositionX()) <= 5 ) {
          onCatchRope( otherObject );
        }
      }
      else if ( otherObject == _holdingRope && otherCollider->getName() == "T" ) {
        _reachedTopOfRope = true;
      }
    }
    else if ( otherObject->getTag() == BAR_TAG ) {
      if ( !isHoldingBar() ) {
        if ( ABS(_selfTransform->getPositionY() - otherObject->getTransform()->getPositionY()) <= 5 ) {
          onCatchBar( otherObject );
        }
      }
    }
    else if ( otherObject->getTag() == SPRING_TAG ) {
      if ( _selfTransform->getPositionY() - otherObject->getTransform()->getPositionY() >= 10 ) {
        onJumpOnSpring( otherObject );
      }
    }
    else if ( otherObject->getTag() == BOSS_TAG ) {
      onHit();
    }
    else if ( otherObject->getTag() == FIRE_TAG ) {
      onHit();
    }
    else if ( otherObject->getTag() == FINISH_ENTRANCE_TAG ) {
      onEnterFinishEntrance();
    }
  }
}

void PlayableAladdinController::onTriggerExit( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();
  const auto selfCollider = collision.getColliderA() == otherCollider
                              ? collision.getColliderB()
                              : collision.getColliderA();

  if ( selfCollider->getTag() == ALADDIN_TAG ) {
    if ( otherObject == _holdingRope ) {
      if ( otherCollider->getName() == "M" ) {
        resetHoldingRope();
      }
      else if ( otherCollider->getName() == "T" ) {
        _reachedTopOfRope = false;
      }
    }
    else if ( otherObject == _holdingBar ) {
      resetHoldingBar();
    }
  }
}

void PlayableAladdinController::onInitialize() {
  const auto gameManager = GameManager::get();

  _selfTransform = getGameObject()->getTransform();
  _selfActionManager = getGameObject()->getComponentT<ActionManager>();
  _selfStateManager = getGameObject()->getComponentT<StateManager>();
  _selfAnimator = getGameObject()->getComponentT<Animator>();
  _selfBodyCollider = static_cast<Collider*>(getGameObject()->getComponent( "Body" ));
  _selfBody = getGameObject()->getComponentT<Rigidbody>();
  _selfDirection = getGameObject()->getComponentT<DirectionController>();
  _throwableApplePrefab = gameManager->getPrefabV2( "Throwable Apple" );
  _throwableKnifePrefab = gameManager->getPrefabV2( "Against Throwable Knife" );
  _myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));
  _sceneFadeOutTransitionPrefab = gameManager->getPrefabV2( "Scene Fade Out Transition" );

  setLives( _myAppData->getAladdinLives() );
  setApples( _myAppData->getAladdinApples() );
  setGems( 0 );
  setHealth( 9 );

  // debug
  //  setApples( 90 );
  //  setHealth( 90 );
}

void PlayableAladdinController::onUpdate( const float dt ) {
  // recalculate moving x
  float dampVelocity = 0.0f;

  for ( auto i = 0; i < _dampVelocitiesSize; ++i ) {
    _dampVelocities[i].first -= dt;
    dampVelocity += _dampVelocities[i].second;

    if ( _dampVelocities[i].first <= 0 ) {
      for ( auto j = i; j < _dampVelocitiesSize - 1; ++j ) {
        _dampVelocities[j] = _dampVelocities[j + 1];
      }
      --_dampVelocitiesSize;
      --i;
    }
  }

  // update body velocity
  float v = 0.0f;

  if ( _selfDirection->isLeft() ) {
    v = -_movingVelocityX + dampVelocity;
  }
  else {
    v = _movingVelocityX + dampVelocity;
  }

  if ( v < -_maxMovingVelocityX ) v = -_maxMovingVelocityX;
  else if ( v > _maxMovingVelocityX ) v = _maxMovingVelocityX;

  _selfBody->setVelocity( Vec2( v, _selfBody->getVelocity().getY() ) );
}

void PlayableAladdinController::onHitCharcoalBurner() {
  if ( _selfStateManager->getCurrentStateName() == "idle" ) {
    onHit();
  }
}

void PlayableAladdinController::onHit( const int damage ) {
  if ( _recovering ) return;

  setHealth( getHealth() - damage );

  if ( _health <= 0 ) {
    _sceneFadeOutTransitionPrefab->instantiateWithArgs( "0.5 death.scene\n0" );

    return;
  }

  _hit = true;

  setRecovering();
}

void PlayableAladdinController::onJumpOnCamel() {
  _jumpOnCamel = true;

  // TODO: refactor to state transition
  _selfStateManager->changeState( "jump" );
}

void PlayableAladdinController::onJumpOnSpring( ala::GameObject* spring ) {
  _jumpOnSpring = true;

  // TODO: move to spring controller
  spring->getComponentT<StateManager>()->changeState( "dynamic" );

  // TODO: refactor to state transition
  _selfStateManager->changeState( "jump" );
}

void PlayableAladdinController::onCatchRope( ala::GameObject* rope ) {
  if ( isHoldingRope() ||
    _selfStateManager->getCurrentStateName() == "climb" ||
    _selfAnimator->getActionName() == "climb_to_jump" )
    return;

  _holdingRope = rope;

  // TODO: refactor to state transition
  _selfStateManager->changeState( "climb" );
}

void PlayableAladdinController::onCatchBar( ala::GameObject* bar ) {
  if ( isHoldingRope() || isHoldingBar() || _selfStateManager->getPreviousStateName() == "hold_bar_idle" ) return;

  _holdingBar = bar;

  // TODO: refactor to state transition
  _selfStateManager->changeState( "hold_bar_idle" );
}

void PlayableAladdinController::onEnterFinishEntrance() const {
  _myAppData->setAladdinApples( getApples() );
  _sceneFadeOutTransitionPrefab->instantiateWithArgs( "1 level_complete.scene\n0" );
}
