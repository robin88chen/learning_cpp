#ifndef _EVENT_SUBSCRIBER_H
#define _EVENT_SUBSCRIBER_H

#include <functional>
#include "Events.h"

class EventSubscriber
{
public:
    EventSubscriber() {};
    virtual ~EventSubscriber() {};

    virtual void HandleEvent(IEvent* ev) = 0;
};
using EventHandler = std::function<void(IEvent*)>;
using EventHandlerDelegate = void(*)(IEvent*);

class TestEventCommittedHandler : public EventSubscriber
{
public:
    TestEventCommittedHandler() : EventSubscriber() {}
    virtual void HandleEvent(IEvent* ev) override;
};

template <class SUB>
class TemplateSubscriber : public EventSubscriber
{
public:
    TemplateSubscriber<SUB>(EventHandler h) : EventSubscriber(), m_handler(h) {}
    virtual void HandleEvent(IEvent* ev) override { if (m_handler) m_handler(ev); }
protected:
    EventHandler m_handler;
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
#endif // _EVENT_SUBSCRIBER_H
