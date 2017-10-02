#ifndef __STRING_MESSAGE_ARG_H__
#define __STRING_MESSAGE_ARG_H__

#include "IMessageArg.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(StringMessageArg, IMessageArg)
public:
  explicit StringMessageArg(const std::string& payload);
  const std::string& getPayload() const;
private:
  std::string _payload;
};
}
#endif //__STRING_MESSAGE_ARG_H__