#include "EventPublisher.h"

EventPublisher* EventPublisher::m_instance = nullptr;

EventPublisher::EventPublisher()
{
	m_instance = this;
}

EventPublisher::~EventPublisher()
{
	m_instance = nullptr;
}

EventPublisher* EventPublisher::Instance()
{
	return m_instance;
}


