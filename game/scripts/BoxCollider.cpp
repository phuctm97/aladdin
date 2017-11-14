#include "BoxCollider.h"

USING_NAMESPACE_ALA;

BoxCollider::BoxCollider( ala::GameObject* gameObject, const ala::Size& size, const std::string& name )
  : GameObjectComponent( gameObject, name ), _size( size ), _debugDraw( false ) {}

const ala::Size& BoxCollider::getSize() const { return _size; }

void BoxCollider::setSize( const ala::Size& size ) { _size = size; }

bool BoxCollider::getDebugDraw() const { return _debugDraw; }

void BoxCollider::setDebugDraw( const bool debugDraw ) { _debugDraw = debugDraw; }
