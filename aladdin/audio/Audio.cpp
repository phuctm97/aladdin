#include "Audio.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_2(ala::Audio, ala::Initializable, ala::Releasable)

Audio* Audio::__instance( NULL );

Audio::Audio() : _logger( "ala::Audio" ) {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));
  _logger.debug( "Created" );
}

Audio::~Audio() {
  if ( isInitialized() ) {
    ALA_ASSERT(isReleased());
  }
  _logger.debug( "Released" );
}

Audio* Audio::get() {
  if ( __instance == NULL ) {
    __instance = new Audio();
  }
  return __instance;
}

void Audio::initialize() {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  setToInitializing();


  setToInitialized();
}

void Audio::release() {
  ALA_ASSERT(isInitialized() && (!isReleased()) && (!isReleasing()));

  setToReleasing();


  setToReleased();

  // destroy
  delete this;
}
}
