#include "StringMessageArg.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1 ( ala::StringMessageArg, ala::IMessageArg )

StringMessageArg::StringMessageArg ( const std::string& payload )
{
  _payload = payload;
}

const std::string& StringMessageArg::getPayload ( ) const
{
  return _payload;
}
}
