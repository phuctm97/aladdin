/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ResourceInitializer.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::ResourceInitializer )

ResourceInitializer::ResourceInitializer() {
  TOTAL_RESOURCE_INITIALIZERS_CREATED++;
}

ResourceInitializer::~ResourceInitializer() {
  TOTAL_RESOURCE_INITIALIZERS_DELETED++;
}

// =============================================
// Debug memory allocation
// =============================================
long ResourceInitializer::TOTAL_RESOURCE_INITIALIZERS_CREATED( 0 );
long ResourceInitializer::TOTAL_RESOURCE_INITIALIZERS_DELETED( 0 );
}
