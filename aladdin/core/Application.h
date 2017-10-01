#ifndef __ALADDIN_CORE_APPLICATION_H__
#define __ALADDIN_CORE_APPLICATION_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "Scene.h"
#include "ResourceInitializer.h"
#include "Logger.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Application)
  // ================================================
  // Basic
  // ================================================
private:
  bool _inited;
  bool _released;
  std::string _title;
  int _screenWidth;
  int _screenHeight;
  float _animationInterval;
  Scene* _sceneToStart;
  std::vector<ResourceInitializer*> _resourceInitializers;
  long _frameCount;
  Logger* _logger;

public:
  Application();

  virtual ~Application();

  void setScreenSize( int width, int height );

  int getScreenWidth() const;

  int getScreenHeight() const;

  void setTitle( const std::string& title );

  const std::string& getTitle() const;

  void setAnimationInterval( float millis );

  float getLoopInterval() const;

  void startWithScene( Scene* scene );

  void registerResourceInitializer( ResourceInitializer* initializer );

private:
  void initResources();

  void initComponents();

  void releaseComponents();

  void onUpdate( float delta );

  void onRender();

protected:
  virtual void init() = 0;

  virtual void release() = 0;

  // ================================================
  // Platform specific
  // ================================================

private:
  int _logStream;
  bool _exiting;
  MSG _msg;
  HINSTANCE _hInstance;
  HWND _hWnd;
  IDirect3D9* _directX;
  IDirect3DDevice9* _directXDevice;
  LPD3DXSPRITE _directXSprite;
  DWORD _startTimestamp;
  DWORD _lastTimestamp;

public:
  void run( HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            LPSTR lpCmdLine,
            int nCmdShow,
            int logStream = 0 );

private:
  void initWindowHandle();

  void initDirectX();

  void releaseDirectX() const;

  void gameLoop();

  void processMessage();

  void processGame();

  static LRESULT wndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
};
}

#endif //!__ALADDIN_CORE_APPLICATION_H__
