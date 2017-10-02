/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "Application.h"
#include "GameManager.h"
#include "../2d/Graphics.h"
#include "../input/Input.h"

NAMESPACE_ALA
{
// ==================================================
// Basic
// ==================================================
ALA_CLASS_SOURCE_2(Application, ala::Initializable, ala::Releasable)

Application::Application() :
  _title( "Aladdin Game" ),
  _screenWidth( 800 ),
  _screenHeight( 600 ),
  _animationInterval( 1000.0f / 60 ),
  _sceneToStart( NULL ),
  _frameCount( 0 ),
  _logger( "ala::Application" ),
  _logStream( 0 ),
  _exiting( false ),
  _hInstance( NULL ),
  _hWnd( NULL ),
  _directX( NULL ),
  _directXDevice( NULL ),
  _directXSprite( NULL ),
  _startTimestamp( 0 ),
  _lastTimestamp( 0 ) {
  // check initial state
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));
}

Application::~Application() {
  if ( isInitialized() ) {
    ALA_ASSERT(isReleased());
  }

  // memory debug
  _logger.debug( "Total Resources Created: %ld", GameResource::TOTAL_RESOURCES_CREATED );
  _logger.debug( "Total Resources Deleted: %ld", GameResource::TOTAL_RESOURCES_DELETED );
  _logger.debug( "Total Resource Initializers Created: %ld", ResourceInitializer::TOTAL_RESOURCE_INITIALIZERS_CREATED );
  _logger.debug( "Total Resource Initializers Deleted: %ld", ResourceInitializer::TOTAL_RESOURCE_INITIALIZERS_DELETED );
  _logger.debug( "Total Prefabs Created: %ld", Prefab::TOTAL_PREFABS_CREATED );
  _logger.debug( "Total Prefabs Deleted: %ld", Prefab::TOTAL_PREFABS_DELETED );
  _logger.debug( "Total Scenes Created: %ld", Scene::TOTAL_SCENES_CREATED );
  _logger.debug( "Total Scenes Deleted: %ld", Scene::TOTAL_SCENES_DELETED );
  _logger.debug( "Total Objects Created: %ld", GameObject::TOTAL_OBJECTS_CREATED );
  _logger.debug( "Total Objects Deleted: %ld", GameObject::TOTAL_OBJECTS_DELETED );
  _logger.debug( "Total Components Created: %ld", GameObjectComponent::TOTAL_COMPONENTS_CREATED );
  _logger.debug( "Total Components Deleted: %ld", GameObjectComponent::TOTAL_COMPONENTS_DELETED );
  _logger.debug( "Total Loggers Created: %ld", Logger::TOTAL_LOGGERS_CREATED );
  _logger.debug( "Total Loggers Deleted: %ld", Logger::TOTAL_LOGGERS_DELETED + 1 );

  // average fps
  const auto fps = static_cast<int>(roundf( (1000.0f * _frameCount) / (GetTickCount() - _startTimestamp) ));
  _logger.debug( "Average FPS: %d", fps );
}

void Application::setScreenSize( int width, int height ) {
  // can only be set before init process
  ALA_ASSERT(isInitializing() && (!isInitialized()) && (!isReleased()) && (!isReleasing()));
  _screenWidth = width;
  _screenHeight = height;
}

int Application::getScreenWidth() const {
  return _screenWidth;
}

int Application::getScreenHeight() const {
  return _screenHeight;
}

void Application::setTitle( const std::string& title ) {
  // can only be set before init process
  ALA_ASSERT(isInitializing() && (!isInitialized()) && (!isReleased()) && (!isReleasing()));
  _title = title;
}

const std::string& Application::getTitle() const {
  return _title;
}

void Application::setAnimationInterval( float millis ) {
  // can only be set before init process
  ALA_ASSERT(isInitializing() && (!isInitialized()) && (!isReleased()) && (!isReleasing()));
  _animationInterval = millis;
}

float Application::getLoopInterval() const {
  return _animationInterval;
}

void Application::startWithScene( Scene* scene ) {
  // can only be set before init process
  ALA_ASSERT(isInitializing() && (!isInitialized()) && (!isReleased()) && (!isReleasing()));
  _sceneToStart = scene;
}

void Application::registerResourceInitializer( ResourceInitializer* initializer ) {
  _resourceInitializers.push_back( initializer );
}

void Application::onUpdate( float delta ) {
  Scene* runningScene = GameManager::get()->getRunningScene();
  if ( runningScene ) {
    runningScene->update( delta );
  }
}

void Application::onRender() {
  Scene* runningScene = GameManager::get()->getRunningScene();
  if ( runningScene ) {
    runningScene->render();
  }
}

// ================================================
// Initializing & Releasing
// ================================================

void Application::initialize() {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  setToInitializing();

  // client application init
  onInitialize();

  // init components
  initComponents();

  setToInitialized();
}

void Application::release() {
  ALA_ASSERT((isInitialized()) && (!isReleasing()) && (!isReleased()));

  setToReleasing();

  // client application release
  onRelease();

  // release components
  releaseComponents();

  setToReleased();

  // destroy
  delete this;
}

void Application::initComponents() {
  // validate application properties
  ALA_ASSERT(_screenWidth > 0);
  ALA_ASSERT(_screenHeight > 0);
  ALA_ASSERT(!_title.empty());
  ALA_ASSERT(_animationInterval >= (1000.0f / 61));

  // windows components
  initWindowHandle();
  initDirectX();

  // game singleton components
  Graphics* graphics = Graphics::get();
  graphics->_directXDevice = _directXDevice;
  graphics->_directXSprite = _directXSprite;

  Input* input = Input::get();
  input->_hInstance = _hInstance;
  input->_hWnd = _hWnd;
  input->initialize();

  GameManager* gameManager = GameManager::get();
  gameManager->_screenWidth = static_cast<float>(_screenWidth);
  gameManager->_screenHeight = static_cast<float>(_screenHeight);

  // seed random
  srand( static_cast<unsigned int>(time( 0 )) );

  // init resources
  initResources();

  // init runnings scene
  gameManager->replaceScene( _sceneToStart );
}

void Application::initResources() {
  // init resource initializers
  for ( auto initializer : _resourceInitializers ) {
    if ( initializer ) {
      initializer->init();
    }
    delete initializer;
  }
  _resourceInitializers.clear();

  // load game resources
  for ( const auto it : GameManager::get()->_attachedResources ) {
    auto resource = it.second;
    if ( resource->isLoaded() ) continue;
    if ( resource->isGameScope() ) {
      resource->load();
    }
  }
}

void Application::releaseComponents() {
  // running scene
  Scene* scene = GameManager::get()->getRunningScene();
  scene->release();

  // left objects
  for ( GameObject* object : GameManager::get()->getAllObjects() ) {
    object->release();
  }

  // left resources
  for ( GameResource* resource : GameManager::get()->getAllResources() ) {
    resource->release();
  }

  // left prefabs
  for ( Prefab* prefab : GameManager::get()->getAllPrefabs() ) {
    prefab->release();
  }

  // game singleton components
  GameManager* gameManager = GameManager::get();
  gameManager->release();

  Graphics* graphics = Graphics::get();
  delete graphics;

  Input* input = Input::get();
  input->release();

  // windows components
  releaseDirectX();
}

// ===================================================
// Platform specific
// ===================================================
void Application::run( const HINSTANCE hInstance,
                       const HINSTANCE hPrevInstance,
                       const LPSTR lpCmdLine,
                       const int nCmdShow,
                       const int logStream ) {
  // make sure that application can only init once
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  // get run arguments
  _hInstance = hInstance;
  _logStream = logStream;

  // init app
  initialize();

  // game loop
  gameLoop();
}

void Application::initWindowHandle() {
  // Logging
  switch ( _logStream ) {
  case 1: {
    AllocConsole();
    AttachConsole( GetCurrentProcessId() );
    // ReSharper disable CppDeprecatedEntity
    freopen( "CON", "w", stdout );
    // ReSharper restore CppDeprecatedEntity

    _logger.debug( "Allocated Console Logger" );
  }
    break;
  case 2: {
    // ReSharper disable CppDeprecatedEntity
    freopen( "log.txt", "w", stdout );
    // ReSharper restore CppDeprecatedEntity

    _logger.debug( "Allocated File Logger. All your logging data will be store in file `log.txt`" );
  }
    break;
  default:
    break;
  }

  // Windows
  WNDCLASSEX wndClassEx;
  ZeroMemory(&wndClassEx, sizeof(wndClassEx));
  wndClassEx.cbSize = sizeof(WNDCLASSEX);
  wndClassEx.hInstance = _hInstance; // bind with handle instance
  wndClassEx.lpfnWndProc = reinterpret_cast<WNDPROC>(wndProc); // register windows procedure
  wndClassEx.lpszClassName = _title.c_str(); // define class name
  ALA_ASSERT(RegisterClassEx(&wndClassEx) != 0);

  // create windows
  _hWnd = CreateWindow(
    wndClassEx.lpszClassName, // windows class name
    _title.c_str(), // windows title
    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // windows style
    CW_USEDEFAULT, // windows start position
    CW_USEDEFAULT, // windows start position
    _screenWidth, // windows size
    _screenHeight, // windows size
    0,
    0,
    _hInstance, // handle instance
    0);
  ALA_ASSERT(_hWnd);
  _logger.debug( "Created Windows" );

  // show windows
  ShowWindow( _hWnd, SW_SHOW );
  UpdateWindow( _hWnd );
}

void Application::initDirectX() {
  HRESULT result;

  // init DirectX
  _directX = Direct3DCreate9( D3D_SDK_VERSION );
  ALA_ASSERT(!FAILED(_directX));

  _logger.debug( "Initialized DirectX" );

  // init DirectX device
  D3DPRESENT_PARAMETERS d3dpp;
  ZeroMemory(&d3dpp, sizeof(d3dpp));
  d3dpp.BackBufferCount = 1;
  d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
  d3dpp.BackBufferWidth = static_cast<UINT>(_screenWidth);
  d3dpp.BackBufferHeight = static_cast<UINT>(_screenHeight);
  d3dpp.Windowed = true;
  d3dpp.hDeviceWindow = _hWnd;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  result = _directX->CreateDevice(
    D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    _hWnd,
    D3DCREATE_HARDWARE_VERTEXPROCESSING,
    &d3dpp,
    &_directXDevice );

  ALA_ASSERT(result == D3D_OK);
  ALA_ASSERT(!FAILED(_directXDevice));

  _logger.debug( "Created DirectX Device" );


  // init DirectX Sprite
  result = D3DXCreateSprite( _directXDevice, &_directXSprite );
  ALA_ASSERT(result == D3D_OK);
  ALA_ASSERT(!FAILED(_directXSprite));

  _logger.debug( "Created DirectX Sprite" );
}

void Application::releaseDirectX() const {
  if ( _directXSprite ) {
    _directXSprite->Release();
    _logger.debug( "Released DirectX Sprite" );
  }
  if ( _directXDevice ) {
    _directXDevice->Release();
    _logger.debug( "Released DirectX Device" );
  }
  if ( _directX ) {
    _directX->Release();
    _logger.debug( "Released DirectX" );
  }
}

void Application::gameLoop() {
  // initial timestamp
  _startTimestamp = GetTickCount();
  _lastTimestamp = _startTimestamp;

  while ( !_exiting ) {
    processMessage();
    processGame();
  }
}

void Application::processMessage() {
  // read message from message queue
  if ( PeekMessage( &_msg, 0, 0, 0, PM_REMOVE ) ) {
    if ( _msg.message == WM_QUIT ) {
      // exit event
      _exiting = true;
      return;
    }

    // process message
    TranslateMessage( &_msg );
    DispatchMessage( &_msg );
  }
}

void Application::processGame() {
  // get current timestamp
  DWORD currentTimestamp = GetTickCount();

  // calculate delta
  float delta = static_cast<float>(currentTimestamp - _lastTimestamp);

  // check interval
  if ( delta < _animationInterval ) {
    // too soon, sleep and recalculate
    Sleep( static_cast<DWORD>(roundf( _animationInterval - delta )) );

    currentTimestamp = GetTickCount();
    delta = static_cast<float>(currentTimestamp - _lastTimestamp);
  }

  // update timestamp
  _lastTimestamp = currentTimestamp;

  // debug fps
  _frameCount++;
  if ( _frameCount % 1800 == 0 ) {
    const int fps = static_cast<int>(roundf( (1000.0f * _frameCount) / (currentTimestamp - _startTimestamp) ));
    _logger.debug( "FPS: %d", fps );
  }

  // update
  onUpdate( delta );

  // clear screen
  _directXDevice->Clear( 0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 );

  // start rendering
  if ( _directXDevice->BeginScene() ) {
    _directXSprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_DONOTSAVESTATE );

    onRender();

    // stop rendering
    _directXSprite->End();
    _directXDevice->EndScene();
  }

  // display back buffer to screen
  _directXDevice->Present( 0, 0, 0, 0 );
}

LRESULT Application::wndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {
  // Process message sent to windows

  switch ( message ) {
  case WM_CLOSE: // Windows is about to be closed because user click Close button or press Alt + F4
    break;
  case WM_DESTROY: // Windows is already closed and is about to be destroyed
    PostQuitMessage( 0 ); // put quit message to message queue
    break;
  default:
    break;
  }

  // Default message behaviors
  return DefWindowProc( hWnd, message, wParam, lParam );
}
}
