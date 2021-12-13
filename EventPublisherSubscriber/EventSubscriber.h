#ifndef _EVENT_SUBSCRIBER_H
#define _EVENT_SUBSCRIBER_H

#include "Events.h"

class EventSubscriber
{
public:
	EventSubscriber() {};
	virtual ~EventSubscriber() {};

	virtual void HandleEvent(IEvent* ev) = 0;
};

class TestEventCommittedHandler : public EventSubscriber
{
public:
	TestEventCommittedHandler() : EventSubscriber() {}
	virtual void HandleEvent(IEvent* ev) override;
};

#endif // _EVENT_SUBSCRIBER_H
