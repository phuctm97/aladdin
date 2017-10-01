#ifndef __ALADDIN_CORE_CALLBACK_H__
#define __ALADDIN_CORE_CALLBACK_H__

#include "IMessageArg.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Callback)
public:
  Callback(IMessageArg* args);
  void operator()(std::pair<long, std::function<void(IMessageArg*)>> p) const;
private:
  IMessageArg* _args;
};
}

#endif //__ALADDIN_CORE_CALLBACK_H__
