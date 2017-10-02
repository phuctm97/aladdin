#ifndef __ALADDIN_INPUT_INPUT_H__
#define __ALADDIN_INPUT_INPUT_H__

#include "InputInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Input)
  friend class Application;

private:
  static Input* __instance;
  Logger _logger;

public:
  static Input* get();

  Input();

  virtual ~Input();
};
}

#endif //!__ALADDIN_INPUT_INPUT_H__
