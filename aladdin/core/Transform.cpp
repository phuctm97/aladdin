/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Transform.h"
#include "StdHelper.h"
#include "GameManager.h"

NAMESPACE_ALA
{
// ===================================================
// Basic
// ===================================================

ALA_CLASS_SOURCE_1( ala::Transform, ala::GameObjectComponent )

Transform::Transform( GameObject* gameObject, Transform* parentTransform, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _position( 0, 0 ),
    _scale( 1, 1 ),
    _rotation( 0 ),
    _origin ( 0.5f,0.5f ),
    _parent( parentTransform ) {
  if ( _parent != NULL ) {
    _parent->addChild( this );
  }
}

Transform::~Transform() {}

const Vec2& Transform::getPosition() const {
  return _position;
}

float Transform::getPositionX() const {
  return _position.getX();
}

float Transform::getPositionY() const {
  return _position.getY();
}

void Transform::setPosition( const Vec2& position ) {
  _position = position;
}

void Transform::setPosition ( const float x, const float y )
{
  _position = Vec2(x, y);
}

  void Transform::setPositionX( const float x ) {
  _position.setX( x );
}

void Transform::setPositionY( const float y ) {
  _position.setY( y );
}

const Vec2& Transform::getScale() const {
  return _scale;
}

void Transform::setScale( const Vec2& scale ) {
  _scale = scale;
}

void Transform::setScaleX ( float x )
{
  _scale.setX(x);
}

void Transform::setScaleY ( float y )
{
  _scale.setY(y);
}

void Transform::setScale ( float scale )
{
  _scale.setX(scale);
  _scale.setY(scale);
}

  float Transform::getRotation() const {
  return _rotation;
}

void Transform::setRotation( const float rotation ) {
  _rotation = rotation;
}

  // =======================================================
// Children management
// =======================================================

std::vector<Transform*> Transform::getChildren() const {
  return _children;
}

Transform* Transform::getChild( const int index ) const {
  return _children[index];
}

Transform* Transform::getParent() const {
  return _parent;
}

void Transform::addChild( Transform* child ) {
  if ( isReleasing() || isReleased() ) return;
  if ( child == NULL ) return;
  if ( StdHelper::vectorContain( _children, child ) ) return;
  _children.push_back( child );
}

void Transform::removeChild( Transform* child ) {
  if ( isReleasing() || isReleased() ) return;
  if ( child == NULL ) return;
  StdHelper::vectorErase( _children, child );
}

void Transform::onRelease() {
  // release child transform
  if ( _parent != NULL ) {
    _parent->removeChild( this );
  }
}

void Transform::onUpdate( const float delta ) {
  for ( auto transform : _children ) {
    transform->getGameObject()->update( delta );
  }
}

void Transform::onRender() {
  for ( auto transform : _children ) {
    transform->getGameObject()->render();
  }
}

D3DXMATRIX Transform::getTransformationMatrix ( )
{
  //D3DXMATRIX transformationMatrix;

  //auto position = D3DXVECTOR2(_position.getX(), _position.getY());
  //auto scale = D3DXVECTOR2(_scale.getX(), _scale.getY());
  //D3DXMatrixTransformation2D(
  //  &transformationMatrix,
  //  &position,
  //  0.0f,
  //  &scale,
  //  &position,
  //  D3DXToRadian(_rotation),
  //  0
  //);

  D3DXMATRIX matRotate;
  D3DXMATRIX matScale;
  D3DXMATRIX matTranslate;

  D3DXMatrixRotationZ(&matRotate, D3DXToRadian(_rotation));
  D3DXMatrixScaling(&matScale, _scale.getX (  ), _scale.getY(), 1.f);
  D3DXMatrixTranslation(&matTranslate, _position.getX (  ), _position.getY(), 0.0f);


  return matRotate*matScale*matTranslate;
}
}
