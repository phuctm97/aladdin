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
    _isDirty ( false ),
    _isInverseDirty ( false ),
    _parent( parentTransform ) {
  if ( _parent != NULL ) {
    D3DXMatrixIdentity(&_localToWorldMatrix);
    D3DXMatrixIdentity(&_worldToLocalMatrix);
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
  setDirty();
}

void Transform::setPosition ( const float x, const float y )
{
  _position = Vec2(x, y);
  setDirty();
}

  void Transform::setPositionX( const float x ) {
  _position.setX( x );
  setDirty();
}

void Transform::setPositionY( const float y ) {
  _position.setY( y );
  setDirty();
}

const Vec2& Transform::getScale() const {
  return _scale;
}

void Transform::setScale( const Vec2& scale ) {
  _scale = scale;
  setDirty();
}

void Transform::setScaleX ( float x )
{
  _scale.setX(x);
  setDirty();
}

void Transform::setScaleY ( float y )
{
  _scale.setY(y);
  setDirty();
}

void Transform::setScale ( float scale )
{
  _scale.setX(scale);
  _scale.setY(scale);
  setDirty();
}

  float Transform::getRotation() const {
  return _rotation;
}

void Transform::setRotation( const float rotation ) {
  _rotation = rotation;
  setDirty();
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

  child->_parent = this;
  _children.push_back( child );

  setDirty();
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

D3DXMATRIX Transform::calculateLocalToParentMatrix ( )
{
  D3DXMATRIX matRotate;
  D3DXMATRIX matScale;
  D3DXMATRIX matTranslate;

  D3DXMatrixRotationZ(&matRotate, D3DXToRadian(_rotation));
  D3DXMatrixScaling(&matScale, _scale.getX(), _scale.getY(), 1.f);
  D3DXMatrixTranslation(&matTranslate, _position.getX(), _position.getY(), 0.0f);


  return matRotate*matScale*matTranslate;
}

D3DXMATRIX Transform::getLocalToWorldMatrix ( )
{
  if(_isDirty)
  {
    if(_parent == NULL)
    {
      _localToWorldMatrix = calculateLocalToParentMatrix();
    }
    else
    {
      _localToWorldMatrix = _parent->getLocalToWorldMatrix() * calculateLocalToParentMatrix();
    }

    _isDirty = false;
  }

  return _localToWorldMatrix;
}

D3DXMATRIX Transform::getWorldToLocalMatrix()
{
  if(_isInverseDirty)
  {
    auto localToWorldMatrix = getLocalToWorldMatrix();
    D3DXMatrixInverse(&_worldToLocalMatrix, NULL, &localToWorldMatrix);
    _isInverseDirty = false;
  }

  return _worldToLocalMatrix;
}

void Transform::setDirty ( )
{
  if(!_isDirty)
  {
    _isDirty = true;
    _isInverseDirty = true;

    for (auto transform : _children)
    {
      transform->setDirty();
    }
  }
}
}
