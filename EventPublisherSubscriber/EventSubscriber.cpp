#include "EventSubscriber.h"
#include <iostream>

void TestEventCommittedHandler::HandleEvent(IEvent* ev)
{
	std::cout << "Test Event Committed!!\n";
}
