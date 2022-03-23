#ifndef _EVENT_PUBLISHER_H
#define _EVENT_PUBLISHER_H

#include "EventSubscriber.h"
#include <unordered_map>
#include <list>
#include <memory>

class EventPublisher
{
public:
    EventPublisher();
    ~EventPublisher();

    static EventPublisher* Instance();

    template <class EV_T> void Publish(const std::shared_ptr<EV_T>& ev)
    {
        auto it = m_subscribers.find(EV_T::name);
        if (it == m_subscribers.end()) return;
        for (auto sub : it->second)
        {
            sub->HandleEvent(ev.get());
        }
        auto ith = m_handlers.find(EV_T::name);
        if (ith == m_handlers.end()) return;
        for (auto h : ith->second)
        {
            h(ev.get());
        }
    }

    template <class E_T, class SUB_T> void Subscribe(const std::shared_ptr<SUB_T>& sub)
    {
        auto it = m_subscribers.find(E_T::name);
        if (it == m_subscribers.end())
        {
            m_subscribers.insert({ E_T::name, { std::dynamic_pointer_cast<EventSubscriber, SUB_T>(sub) } });
        }
        else
        {
            it->second.emplace_back(std::dynamic_pointer_cast<EventSubscriber, SUB_T>(sub));
        }
    }
    template <class E_T> void Subscribe(const std::shared_ptr<EventSubscriber>& sub)
    {
        if (!sub) return;
        auto it = m_subscribers.find(E_T::name);
        if (it == m_subscribers.end())
        {
            m_subscribers.insert({ E_T::name, { sub } });
        }
        else
        {
            it->second.emplace_back(sub);
        }
    }
    template <class E_T> void Subscribe(const EventHandler& hand)
    {
        auto it = m_handlers.find(E_T::name);
        if (it == m_handlers.end())
        {
            m_handlers.insert({ E_T::name, { hand } });
        }
        else
        {
            it->second.emplace_back(hand);
        }
    }
    template <class E_T> void UnSubscribe(const EventHandler& hand)
    {
        auto it = m_handlers.find(E_T::name);
        if (it != m_handlers.end())
        {
            auto handler_func = hand.target<EventHandlerDelegate>();
            it->second.remove_if([=](const EventHandler& bh)
                {
                    auto booked_func = bh.target<EventHandlerDelegate>();
                    return ((booked_func) && (*booked_func == *handler_func));
                });
        }
    }
    template <class E_T> void UnSubscribe(const std::shared_ptr<EventSubscriber>& sub)
    {
        if (!sub) return;
        auto it = m_subscribers.find(E_T::name);
        if (it != m_subscribers.end())
        {
            it->second.remove(sub);
        }
    }

private:
    static EventPublisher* m_instance;

    std::unordered_map<std::string, std::list<std::shared_ptr<EventSubscriber>>> m_subscribers;
    std::unordered_map<std::string, std::list<EventHandler>> m_handlers;
};


#endif // _EVENT_PUBLISHER_H
