#ifndef _EVENTS_H
#define _EVENTS_H
#include <string>

class IEvent
{
public:
	IEvent() {};
	virtual ~IEvent() {};

	static inline std::string name = "Base.Event.Interface";
};

class TestEventCommitted : public IEvent
{
public:
	TestEventCommitted() : IEvent() {};
	virtual ~TestEventCommitted() {};

	static inline std::string name = "Test.Committed";
};

#endif // _EVENTS_H
