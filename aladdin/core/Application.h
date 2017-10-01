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
ALA_CLASS_HEADER_2(Application, ala::Initializable, ala::Releasable)
  // ================================================
  // Basic
  // ================================================
private:
  std::string _title;
  int _screenWidth;
  int _screenHeight;
  float _animationInterval;
  std::vector<ResourceInitializer*> _resourceInitializers;
  Scene* _sceneToStart;
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
  void onUpdate(float delta);

  void onRender();

  // ================================================
  // Initializing & Releasing
  // ================================================
public:
  void initialize() override;

  void release() override;

private:
  void initResources();

  void initComponents();

  void releaseComponents();

protected:
  virtual void onInitialize() = 0;

  virtual void onRelease() = 0;

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
  void run( const HINSTANCE hInstance,
            const HINSTANCE hPrevInstance,
            const LPSTR lpCmdLine,
            const int nCmdShow,
            const int logStream = 0 );

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
