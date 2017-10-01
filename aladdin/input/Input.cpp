#include "Input.h"

/*
 * Created by phuctm97 on Oct 1st 2017
 */

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::Input, ala::Releasable)

Input* Input::__instance( NULL );

Input* Input::get() {
  if ( __instance == NULL ) {
    __instance = new Input();
  }
  return __instance;
}

Input::Input()
  : _logger( "ala::Logger" ) {
  ALA_ASSERT((!isReleased()) && (!isReleasing()));
  _logger.debug( "Created" );
}

Input::~Input() {
  ALA_ASSERT(isReleased());
  _logger.debug( "Released" );
}

float Input::getAxis( const std::string& axisName ) const {
  throw "Not implemented";
}

bool Input::getButton( const std::string& buttonName ) const {
  throw "Not implemented";
}

bool Input::getButtonDown( const std::string& buttonName ) const {
  throw "Not implemented";
}

bool Input::getButtonUp( const std::string& buttonName ) const {
  throw "Not implemented";
}

bool Input::getKey( const std::string& name ) const {
  throw "Not implemented";
}

bool Input::getKeyDown( const std::string& name ) const {
  throw "Not implemented";
}

bool Input::getKeyUp( const std::string& name ) const {
  throw "Not implemented";
}

bool Input::getMouseButton( int button ) const {
  throw "Not implemented";
}

bool Input::getMouseButtonDown( int button ) const {
  throw "Not implemented";
}

bool Input::getMouseButtonUp( int button ) const {
  throw "Not implemented";
}

bool Input::anyKey() const {
  throw "Not implemented";
}

bool Input::anyKeyDown() const {
  throw "Not implemented";
}

Vec2 Input::getMousePosition() const {
  throw "Not implemented";
}

bool Input::isMousePresent() const {
  throw "Not implemented";
}

std::string Input::getInputString() const {
  throw "Not implemented";
}

void Input::release() {
  ALA_ASSERT((!isReleased()) && (!isReleasing()));
  setToReleasing();
  setToReleased();
  delete this;
}
}
