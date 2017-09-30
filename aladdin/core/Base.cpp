//
// Created by phuctm97 on 9/25/2017.
//

#include "Base.h"
#include "Logger.h"

NAMESPACE_ALA
{
// ==============================================
// Basic
// ==============================================

Base::Base() :
  _referenceCount( 0 ),
  _logger( NULL ) {}

Base::~Base() {
  // make sure no reference left
  ALA_ASSERT(_referenceCount == 0);
  SAFE_DELETE(_logger);
}

// ==============================================
// Class Meta
// ==============================================
ALA_DEFINE_CLASS_META_0(ala::Base, "ala::Base")

// ==============================================
// Reference Counter
// ==============================================

int Base::getReferenceCount() const {
  return _referenceCount;
}

void Base::increaseReferenceCount() {
  _referenceCount++;
  TOTAL_REFERENCE_RETAINED++;
}

void Base::decreaseReferenceCount() {
  _referenceCount--;
  TOTAL_REFERENCE_RELEASED++;
  if ( _referenceCount == 0 ) delete this;
}

Logger* Base::getLogger() {
  if ( _logger == NULL ) {
    _logger = new Logger( getClassMeta().getClassName() );
  }
  return _logger;
}

// ======================================================
// Debug memory allocation
// ======================================================
long Base::TOTAL_REFERENCE_RETAINED = 0;

long Base::TOTAL_REFERENCE_RELEASED = 0;
}
