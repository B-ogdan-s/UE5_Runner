
#pragma once

#include <list>
#include "CoreMinimal.h"
#include "CPP_EventHandler.h"

template<class ...TParams>
class RUNNER_API CPP_Event
{
	using EventHandler = CPP_EventHandler<TParams...>;
private:
	std::list<EventHandler*> EventHandlers;
public:
	CPP_Event() : EventHandlers()
	{

	}
	~CPP_Event()
	{
		for (EventHandler* handler : EventHandlers)
		{
			delete handler;
		}
		EventHandlers.clear();
	}
	void operator()(TParams... params)
	{
		UE_LOG(LogConsoleResponse, Log, TEXT("____________________________"));
		for (EventHandler* handler : EventHandlers)
		{
			handler->Call(params...);
		}
	}
	void operator+=(EventHandler& eventHandler)
	{
		EventHandlers.push_back(&eventHandler);
	}
};
