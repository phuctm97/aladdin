#ifndef __ALADDIN_CORE_MESSENGER__
#define __ALADDIN_CORE_MESSENGER__

#include "IMessageArg.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Messenger)
public:
  Messenger();
  ~Messenger();
  void broadcast(std::string messageId, IMessageArg* args);
  long subscribe(std::string messageId, std::function<void(IMessageArg*)> f);
  void unsubscribe(std::string messageId, long token);
private:
  std::map<std::string, std::map<long, std::function<void(IMessageArg*)>>> _callbacks;
  long _token = 0;
public:
  static long TOTAL_MESSENGERS_CREATED;
  static long TOTAL_MESSENGERS_DELETED;
};
}
#endif //__ALADDIN_CORE_MESSENGER__
