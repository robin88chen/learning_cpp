#ifndef _EVENT_SUBSCRIBER_H
#define _EVENT_SUBSCRIBER_H

#include <functional>
#include "Events.h"

using EventHandler = std::function<void(IEvent*)>;
using EventHandlerDelegate = void(*)(IEvent*);

class EventSubscriber
{
public:
    EventSubscriber() {}
    EventSubscriber(const EventHandler& handler) : m_handler{ handler } {}
    virtual ~EventSubscriber() {}

    virtual void HandleEvent(IEvent* ev) { if (m_handler) m_handler(ev); }

protected:
    EventHandler m_handler;
};

class TestEventCommittedHandler : public EventSubscriber
{
public:
    TestEventCommittedHandler() : EventSubscriber(nullptr) {}
    virtual void HandleEvent(IEvent* ev) override;
};

template <class SUB>
class TemplateSubscriber : public EventSubscriber
{
public:
    TemplateSubscriber<SUB>(EventHandler h) : EventSubscriber(h) {}
    //virtual void HandleEvent(IEvent* ev) override { if (m_handler) m_handler(ev); }
};

/**
 * \brief 需要用繼承的方式，也需要另外再定義一個建構子
 */
class TestTemplatedHandler : public TemplateSubscriber<TestTemplatedHandler>
{
public:
    TestTemplatedHandler(EventHandler h) : TemplateSubscriber<TestTemplatedHandler>(h) {}
};

class HandlerCollection
{
public:
    HandlerCollection();
    ~HandlerCollection();
private:
    void OnEvent(IEvent*);

private:
    EventHandler m_handler_;
};

/**
 * \brief 用Subscriber物件，可以清楚解訂閱。複雜的Subscriber可以繼承再處理
 */
class SubscriberCollection
{
public:
    SubscriberCollection();
    ~SubscriberCollection();
private:
    void OnEvent(IEvent*);
private:
    std::shared_ptr<EventSubscriber> m_onEvent;
};
#endif // _EVENT_SUBSCRIBER_H
