#include "Camera.h"
#include "Graphics.h"

#define ALA_CAMERA_MIN_Z 0.0f
#define ALA_CAMERA_MAX_Z 100000.0f

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1 ( ala::Camera, ala::GameObjectComponent )

Camera::Camera( GameObject* gameObject, const std::string& name ) :
  GameObjectComponent( gameObject, name ),
  _width( 0 ),
  _height( 0 ),
  _angle( 0 ),
  _scaleFactor( Vec2( 1.0f, 1.0f ) ) {
  _orthographicMatrix = Mat4::getOrthoLHMatrix( _width, _height, ALA_CAMERA_MIN_Z, ALA_CAMERA_MAX_Z);
}

Camera::Camera( GameObject* gameObject, const std::string& name,
                const float width,
                const float height,
                const float angle,
                const Vec2& scaleFactor ) :
  GameObjectComponent( gameObject, name ),
  _width( width ),
  _height( height ),
  _angle( angle ),
  _scaleFactor( scaleFactor ) {
  _orthographicMatrix = Mat4::getOrthoLHMatrix( _width, _height, ALA_CAMERA_MIN_Z, ALA_CAMERA_MAX_Z);
}

Camera::~Camera() {}

void Camera::onUpdate( float dt ) {
  _viewMatrix = Mat4::getIdentityMat();
  _viewMatrix.set11( _scaleFactor.getX() * cos( _angle ) );
  _viewMatrix.set12( _scaleFactor.getX() * sin( _angle ) );

  _viewMatrix.set21( -_scaleFactor.getY() * sin( _angle ) );
  _viewMatrix.set22( _scaleFactor.getY() * cos( _angle ) );

  auto cameraPosition = getGameObject()->getTransform()->getPosition();

  _viewMatrix.set41( -cameraPosition.getX() * _scaleFactor.getX() * cos( _angle ) + cameraPosition.getY() * _scaleFactor.getY() * sin( _angle ) );

  _viewMatrix.set42( -cameraPosition.getX() * _scaleFactor.getX() * sin( _angle ) - cameraPosition.getY() * _scaleFactor.getY() * cos( _angle ) );

  auto graphics = Graphics::get();

  graphics->setProjectionMatrix( _orthographicMatrix );
  graphics->setWorldMatrix( Mat4::getIdentityMat() );
  graphics->setViewMatrix( _viewMatrix );
}
}
