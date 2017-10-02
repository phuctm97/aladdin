#include "Messenger.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::Messenger)

Messenger::Messenger ( )
{
  TOTAL_MESSENGERS_CREATED++;
}

Messenger::~Messenger ( )
{
  TOTAL_MESSENGERS_DELETED++;
}

void Messenger::broadcast (std::string messageId, IMessageArg* args )
{
	for(auto callback: _callbacks[messageId])
	{
		callback.second(args);
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

long Messenger::TOTAL_MESSENGERS_CREATED = 0;
long Messenger::TOTAL_MESSENGERS_DELETED = 0;
}
