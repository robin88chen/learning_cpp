#include "EventSubscriber.h"
#include "EventPublisher.h"
#include <iostream>

void TestEventCommittedHandler::HandleEvent(IEvent* ev)
{
    std::cout << "Test Event Committed!!\n";
}

HandlerCollection::HandlerCollection()
{
    m_handler_ = [this](auto e) { OnEvent(e); };
    EventPublisher::Instance()->Subscribe<TestEventCommitted>(m_handler_);
}
HandlerCollection::~HandlerCollection()
{
    EventPublisher::Instance()->UnSubscribe<TestEventCommitted>(m_handler_);
}

void HandlerCollection::OnEvent(IEvent*)
{
    std::cout << "Test Event in Handler Collection : " << (int)this << "\n";
}
