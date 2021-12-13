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
private:
	static EventPublisher* m_instance;

	std::unordered_map<std::string, std::list<std::shared_ptr<EventSubscriber>>> m_subscribers;
};


#endif // _EVENT_PUBLISHER_H
