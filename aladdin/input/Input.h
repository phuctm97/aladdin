#ifndef __ALADDIN_INPUT_INPUT_H__
#define __ALADDIN_INPUT_INPUT_H__

#include "InputInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_2(Input, ala::Initializable, ala::Releasable)
  friend class Application;

private:
  static Input* __instance;
  Logger _logger;

public:
  static Input* get();

  Input();

  virtual ~Input();

  float getAxis( const std::string& axisName ) const;

  bool getButton( const std::string& buttonName ) const;

  bool getButtonDown( const std::string& buttonName ) const;

  bool getButtonUp( const std::string& buttonName ) const;

  bool getKey( const std::string& name ) const;

  bool getKeyDown( const std::string& name ) const;

  bool getKeyUp( const std::string& name ) const;

  bool getMouseButton( int button ) const;

  bool getMouseButtonDown( int button ) const;

  bool getMouseButtonUp( int button ) const;

  bool anyKey() const;

  bool anyKeyDown() const;

  Vec2 getMousePosition() const;

  bool isMousePresent() const;

  std::string getInputString() const;

public:
  void initialize() override;

  void release() override;

  void update();

  // =================================================
  // Platform specific
  // =================================================

private:
  HINSTANCE _hInstance;
  HWND _hWnd;
  LPDIRECTINPUT8 _directXInput;
  LPDIRECTINPUTDEVICE8 _directXInputKeyboard;
  char _keys[256];

  void initDirectXInput();

  void releaseDirectXInput();

  int directXKeyDown( const int key );

};
}

#endif //!__ALADDIN_INPUT_INPUT_H__
