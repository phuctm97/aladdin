#include "Input.h"

/*
 * Created by phuctm97 on Oct 1st 2017
 */

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Input )

Input* Input::__instance( NULL );

Input* Input::get() {
  if ( __instance == NULL ) {
    __instance = new Input();
  }
  return __instance;
}

Input::Input()
  : _logger( "ala::Logger" ) {
  _logger.debug( "Created" );
}

Input::~Input() {
  _logger.debug( "Released" );
}
}
