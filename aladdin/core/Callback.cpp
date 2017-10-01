#include "Callback.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::Callback)

Callback::Callback (IMessageArg* args)
  : _args ( args )
{

}

void Callback::operator() ( std::pair<long, std::function<void(IMessageArg*)>> fn ) const
{
  fn.second(_args);
}
}
