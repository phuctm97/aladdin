#include "Input.h"

/*
 * Created by phuctm97 on Oct 1st 2017
 */

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_2( ala::Input, ala::Initializable, ala::Releasable)

Input* Input::__instance( NULL );

Input* Input::get() {
  if ( __instance == NULL ) {
    __instance = new Input();
  }
  return __instance;
}

Input::Input()
  : _logger( "ala::Input" ) {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));
  _logger.debug( "Created" );
}

Input::~Input() {
  if ( isInitialized() ) {
    ALA_ASSERT(isReleased());
  }
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

void Input::initialize() {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  setToInitializing();

  initDirectXInput();

  setToInitialized();
}

void Input::release() {
  ALA_ASSERT(isInitialized() && (!isReleased()) && (!isReleasing()));

  setToReleasing();

  releaseDirectXInput();

  setToReleased();

  // destroy
  delete this;
}

void Input::update() {
  _directXInputKeyboard->GetDeviceState( sizeof(_keys), static_cast<LPVOID>(&_keys) );
}

void Input::initDirectXInput() {
  HRESULT result;

  // init DirectX Input
  result = DirectInput8Create(
    _hInstance,
    DIRECTINPUT_VERSION,
    IID_IDirectInput8,
    reinterpret_cast<void**>(&_directXInput),
    NULL );
  ALA_ASSERT(result == DI_OK);
  ALA_ASSERT(!FAILED(_directXInput));

  _logger.debug( "Created DirectX Input" );

  // init DirectX Input Keyboard
  result = _directXInput->CreateDevice( GUID_SysKeyboard, &_directXInputKeyboard, NULL );
  ALA_ASSERT(result == DI_OK);
  ALA_ASSERT(!FAILED(_directXInputKeyboard));

  _logger.debug( "Created DirectX Input Keyboard Device" );

  // acquire Keyboard
  result = _directXInputKeyboard->SetDataFormat( &c_dfDIKeyboard );
  ALA_ASSERT(result == DI_OK);
  result = _directXInputKeyboard->SetCooperativeLevel( _hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
  ALA_ASSERT(result == DI_OK);
  result = _directXInputKeyboard->Acquire();
  ALA_ASSERT(result == DI_OK);

  _logger.debug( "Acquired Keyboard Device" );

}

void Input::releaseDirectXInput() {
  if ( _directXInputKeyboard ) {
    _directXInputKeyboard->Unacquire();
    _logger.debug( "Unacquired Keyboard Device" );

    _directXInputKeyboard->Release();
    _logger.debug( "Released DirectX Input Keyboard Device" );
  }
  if ( _directXInput ) {
    _directXInput->Release();
    _logger.debug( "Released DirectX Input" );
  }
}

int Input::directXKeyDown( const int key ) {
  return (_keys[key] & 0x80);
}
}
