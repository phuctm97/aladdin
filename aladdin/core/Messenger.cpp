#include "Messenger.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::Messenger)

void Messenger::broadcast (std::string messageId, IMessageArg* args )
{
	for(auto tmp: _callbacks[messageId])
	{
		tmp.second(args);
	}
}

long Messenger::subscribe (std::string messageId,std::function<void(IMessageArg*)> f )
{
  _token++;
  _callbacks[messageId].insert(make_pair(_token, f));
  return _token;
}

void Messenger::unsubscribe (std::string messageId,long token )
{
  _callbacks[messageId].erase(token);
}
}
