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
  : _logger( "ala::Input" ),
    _directXInput( 0 ),
    _directXInputKeyboard( 0 ) {
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

bool Input::getKey( const int code ) const {
  throw "Not implemented";
}

bool Input::getKeyDown( const int code ) const {
  throw "Not implemented";
}

bool Input::getKeyUp( const int code ) const {
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
  _directXInputKeyboard->GetDeviceState( sizeof(_directXKeys), static_cast<LPVOID>(&_directXKeys) );
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

void Input::initDirectXKeysMap() {
  _directXKeysMap.emplace( ALA_KEY_NONE, 0 );
  _directXKeysMap.emplace( ALA_KEY_BACKSPACE, DIK_BACKSPACE );
  _directXKeysMap.emplace( ALA_KEY_DELETE, DIK_DELETE );
  _directXKeysMap.emplace( ALA_KEY_TAB, DIK_TAB );
  _directXKeysMap.emplace( ALA_KEY_RETURN, DIK_RETURN );
  _directXKeysMap.emplace( ALA_KEY_ESCAPE, DIK_ESCAPE );
  _directXKeysMap.emplace( ALA_KEY_SPACE, DIK_SPACE );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_0, DIK_NUMPAD0 );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_1, DIK_NUMPAD1 );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_2, DIK_NUMPAD2 );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_3, DIK_NUMPAD3 );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_4, DIK_NUMPAD4 );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_5, DIK_NUMPAD5 );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_6, DIK_NUMPAD6 );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_7, DIK_NUMPAD7 );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_8, DIK_NUMPAD8 );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_9, DIK_NUMPAD9 );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_PERIOD, DIK_NUMPADPERIOD );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_DIVIDE, DIK_NUMPADSLASH );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_MULTIPLY, DIK_NUMPADSTAR );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_MINUS, DIK_NUMPADMINUS );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_PLUS, DIK_NUMPADPLUS );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_ENTER, DIK_NUMPADENTER );
  _directXKeysMap.emplace( ALA_KEY_KEYPAD_EQUALS, DIK_NUMPADEQUALS );
  _directXKeysMap.emplace( ALA_KEY_UP_ARROW, DIK_UPARROW );
  _directXKeysMap.emplace( ALA_KEY_DOWN_ARROW, DIK_DOWNARROW );
  _directXKeysMap.emplace( ALA_KEY_LEFT_ARROW, DIK_LEFTARROW );
  _directXKeysMap.emplace( ALA_KEY_RIGHT_ARROW, DIK_RIGHTARROW );
  _directXKeysMap.emplace( ALA_KEY_INSERT, DIK_INSERT );
  _directXKeysMap.emplace( ALA_KEY_HOME, DIK_HOME );
  _directXKeysMap.emplace( ALA_KEY_END, DIK_END );
  _directXKeysMap.emplace( ALA_KEY_PAGE_UP, DIK_PGUP );
  _directXKeysMap.emplace( ALA_KEY_PAGE_DOWN, DIK_PGDN );
  _directXKeysMap.emplace( ALA_KEY_F1, DIK_F1 );
  _directXKeysMap.emplace( ALA_KEY_F2, DIK_F2 );
  _directXKeysMap.emplace( ALA_KEY_F3, DIK_F3 );
  _directXKeysMap.emplace( ALA_KEY_F4, DIK_F4 );
  _directXKeysMap.emplace( ALA_KEY_F5, DIK_F5 );
  _directXKeysMap.emplace( ALA_KEY_F6, DIK_F6 );
  _directXKeysMap.emplace( ALA_KEY_F7, DIK_F7 );
  _directXKeysMap.emplace( ALA_KEY_F8, DIK_F8 );
  _directXKeysMap.emplace( ALA_KEY_F9, DIK_F9 );
  _directXKeysMap.emplace( ALA_KEY_F10, DIK_F10 );
  _directXKeysMap.emplace( ALA_KEY_F11, DIK_F11 );
  _directXKeysMap.emplace( ALA_KEY_F12, DIK_F12 );
  _directXKeysMap.emplace( ALA_KEY_F13, DIK_F13 );
  _directXKeysMap.emplace( ALA_KEY_F14, DIK_F14 );
  _directXKeysMap.emplace( ALA_KEY_F15, DIK_F15 );
  _directXKeysMap.emplace( ALA_KEY_ALPHA_0, DIK_0 );
  _directXKeysMap.emplace( ALA_KEY_ALPHA_1, DIK_1 );
  _directXKeysMap.emplace( ALA_KEY_ALPHA_2, DIK_2 );
  _directXKeysMap.emplace( ALA_KEY_ALPHA_3, DIK_3 );
  _directXKeysMap.emplace( ALA_KEY_ALPHA_4, DIK_4 );
  _directXKeysMap.emplace( ALA_KEY_ALPHA_5, DIK_5 );
  _directXKeysMap.emplace( ALA_KEY_ALPHA_6, DIK_6 );
  _directXKeysMap.emplace( ALA_KEY_ALPHA_7, DIK_7 );
  _directXKeysMap.emplace( ALA_KEY_ALPHA_8, DIK_8 );
  _directXKeysMap.emplace( ALA_KEY_ALPHA_9, DIK_9 );
  _directXKeysMap.emplace( ALA_KEY_COMMA, DIK_COMMA );
  _directXKeysMap.emplace( ALA_KEY_MINUS, DIK_MINUS );
  _directXKeysMap.emplace( ALA_KEY_PERIOD, DIK_PERIOD );
  _directXKeysMap.emplace( ALA_KEY_SLASH, DIK_SLASH );
  _directXKeysMap.emplace( ALA_KEY_COLON, DIK_COLON );
  _directXKeysMap.emplace( ALA_KEY_SEMICOLON, DIK_SEMICOLON );
  _directXKeysMap.emplace( ALA_KEY_EQUALS, DIK_EQUALS );
  _directXKeysMap.emplace( ALA_KEY_LEFTBRACKET, DIK_LBRACKET );
  _directXKeysMap.emplace( ALA_KEY_BACKSLASH, DIK_BACKSLASH );
  _directXKeysMap.emplace( ALA_KEY_RIGHTBRACKET, DIK_RBRACKET );
  _directXKeysMap.emplace( ALA_KEY_A, DIK_A );
  _directXKeysMap.emplace( ALA_KEY_B, DIK_B );
  _directXKeysMap.emplace( ALA_KEY_C, DIK_C );
  _directXKeysMap.emplace( ALA_KEY_D, DIK_D );
  _directXKeysMap.emplace( ALA_KEY_E, DIK_E );
  _directXKeysMap.emplace( ALA_KEY_F, DIK_F );
  _directXKeysMap.emplace( ALA_KEY_G, DIK_G );
  _directXKeysMap.emplace( ALA_KEY_H, DIK_H );
  _directXKeysMap.emplace( ALA_KEY_I, DIK_I );
  _directXKeysMap.emplace( ALA_KEY_J, DIK_J );
  _directXKeysMap.emplace( ALA_KEY_K, DIK_K );
  _directXKeysMap.emplace( ALA_KEY_L, DIK_L );
  _directXKeysMap.emplace( ALA_KEY_M, DIK_M );
  _directXKeysMap.emplace( ALA_KEY_N, DIK_N );
  _directXKeysMap.emplace( ALA_KEY_O, DIK_O );
  _directXKeysMap.emplace( ALA_KEY_P, DIK_P );
  _directXKeysMap.emplace( ALA_KEY_Q, DIK_Q );
  _directXKeysMap.emplace( ALA_KEY_R, DIK_R );
  _directXKeysMap.emplace( ALA_KEY_S, DIK_S );
  _directXKeysMap.emplace( ALA_KEY_T, DIK_T );
  _directXKeysMap.emplace( ALA_KEY_U, DIK_U );
  _directXKeysMap.emplace( ALA_KEY_V, DIK_V );
  _directXKeysMap.emplace( ALA_KEY_W, DIK_W );
  _directXKeysMap.emplace( ALA_KEY_X, DIK_X );
  _directXKeysMap.emplace( ALA_KEY_Y, DIK_Y );
  _directXKeysMap.emplace( ALA_KEY_Z, DIK_Z );
  _directXKeysMap.emplace( ALA_KEY_NUM_LOCK, DIK_NUMLOCK );
  _directXKeysMap.emplace( ALA_KEY_CAPS_LOCK, DIK_CAPSLOCK );
  _directXKeysMap.emplace( ALA_KEY_RIGHT_SHIFT, DIK_RSHIFT );
  _directXKeysMap.emplace( ALA_KEY_LEFT_SHIFT, DIK_LSHIFT );
  _directXKeysMap.emplace( ALA_KEY_RIGHT_CONTROL, DIK_RCONTROL );
  _directXKeysMap.emplace( ALA_KEY_LEFT_CONTROL, DIK_LCONTROL );
  _directXKeysMap.emplace( ALA_KEY_RIGHT_ALT, DIK_RALT );
  _directXKeysMap.emplace( ALA_KEY_LEFT_ALT, DIK_LALT );
  _directXKeysMap.emplace( ALA_KEY_RIGHT_WINDOWS, DIK_RWIN );
  _directXKeysMap.emplace( ALA_KEY_LEFT_WINDOWS, DIK_LWIN );
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
  return (_directXKeys[key] & 0x80);
}
}
