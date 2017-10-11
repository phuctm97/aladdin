#include "Audio.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_2(ala::Audio, ala::Initializable, ala::Releasable)

Audio* Audio::__instance( NULL );

Audio::Audio() :
  _logger( "ala::Audio" ),
  _hWnd( 0 ),
  _directXSound( 0 ) {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));
  _logger.info( "Created" );
}

Audio::~Audio() {
  if ( isInitialized() ) {
    ALA_ASSERT(isReleased());
  }
  _logger.info( "Released" );
}

Audio* Audio::get() {
  if ( __instance == NULL ) {
    __instance = new Audio();
  }
  return __instance;
}

void Audio::load( AudioClip* clip ) {
  ALA_ASSERT(clip != NULL);

  HRESULT result;

  CSound* cSound = 0;

  char srcFile[256];
  std::copy( clip->getSourceFile().cbegin(), clip->getSourceFile().cend(), srcFile );
  srcFile[clip->getSourceFile().length()] = '\0';

  result = _directXSound->Create( &cSound, srcFile );
  ALA_ASSERT(result == DS_OK);

  clip->setCSound( cSound );
}

void Audio::play( AudioClip* clip, bool loop ) {
  if ( clip == NULL ) return;
  if ( !clip->getCSound() ) return;

  if ( loop ) {
    clip->getCSound()->Play( 0, DSBPLAY_LOOPING );
  }
  else {
    clip->getCSound()->Play();
  }
}

void Audio::stop( AudioClip* clip ) {
  if ( clip == NULL ) return;
  if ( !clip->getCSound() ) return;

  if ( clip->getCSound()->IsSoundPlaying() ) {
    clip->getCSound()->Stop();
  }
}

void Audio::initialize() {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  setToInitializing();

  initDirectXSound();

  setToInitialized();
}

void Audio::release() {
  ALA_ASSERT(isInitialized() && (!isReleased()) && (!isReleasing()));

  setToReleasing();

  releaseDirectXSound();

  setToReleased();

  // destroy
  delete this;
}

void Audio::initDirectXSound() {
  HRESULT result;

  _directXSound = new CSoundManager();
  result = _directXSound->Initialize( _hWnd, DSSCL_PRIORITY );
  ALA_ASSERT(result == DS_OK);

  result = _directXSound->SetPrimaryBufferFormat( 2, 22050, 16 );
  ALA_ASSERT(result == DS_OK);

  _logger.info( "Created DirectX Sound" );
}

void Audio::releaseDirectXSound() {
  if ( _directXSound ) {
    delete _directXSound;
    _directXSound = 0;

    _logger.info( "Released DirectX Sound" );
  }
}
}
