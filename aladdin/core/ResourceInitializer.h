/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_RESOURCE_INITIALIZER_H__
#define __ALADDIN_CORE_RESOURCE_INITIALIZER_H__

#include "ClassMeta.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(ResourceInitializer)
public:
  ResourceInitializer();

  virtual ~ResourceInitializer();

  virtual void run() = 0;

  // =============================================
  // Debug memory allocation
  // =============================================
public:
  static long TOTAL_RESOURCE_INITIALIZERS_CREATED;
  static long TOTAL_RESOURCE_INITIALIZERS_DELETED;
};
}

#endif //!__ALADDIN_CORE_RESOURCE_INITIALIZER_H__
