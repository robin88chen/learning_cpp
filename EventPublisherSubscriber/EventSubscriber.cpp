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

SubscriberCollection::SubscriberCollection()
{
    // 這樣直接將 lambda function 再做成 subscriber 物件
    m_onEvent = std::make_shared<EventSubscriber>([this](auto e) { OnEvent(e); });
    EventPublisher::Instance()->Subscribe<TestEventCommitted>(m_onEvent);
}

SubscriberCollection::~SubscriberCollection()
{
    EventPublisher::Instance()->UnSubscribe<TestEventCommitted>(m_onEvent);
    m_onEvent = nullptr;
}

void SubscriberCollection::OnEvent(IEvent*)
{
    std::cout << "Test Event in Subscriber Collection : " << (int)this << "\n";
}
