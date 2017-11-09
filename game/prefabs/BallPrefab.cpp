/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BallPrefab.h"
#include "../scripts/BallController.h"
#include "physics/Collider.h"
#include "physics/Rigidbody.h"

void BallPrefab::doInstantiate( ala::GameObject* object ) {
	object->getTransform()->setPosition(0, 0);
  new ala::SpriteRenderer( object, "ball.png" );
  new ala::AudioSource( object, "wow.wav" );
  //new BallController( object );
	object->getTransform()->setPosition(1000, 1000);
	auto rb= new ala::Rigidbody(object, ala::PhysicsMaterial(1, 10));
	rb->setGravityScale(0);
	rb->setVelocity(ala::Vec2(-100, -100));
	new ala::Collider(object, false, ala::Vec2(0, 0), ala::Size(30, 30));
}
