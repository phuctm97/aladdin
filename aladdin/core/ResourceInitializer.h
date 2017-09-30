/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_RESOURCE_INITIALIZER_H__
#define __ALADDIN_CORE_RESOURCE_INITIALIZER_H__

#include "Base.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(ResourceInitializer)
public:
  virtual void init() = 0;
};
}

#endif //!__ALADDIN_CORE_RESOURCE_INITIALIZER_H__
