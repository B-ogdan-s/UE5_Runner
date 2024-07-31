
#pragma once

#include <iostream>
#include <map>
#include <typeindex>
#include "StateMachine/CPP_State.h"

template<typename T>
class CPP_StateMachine
{
private:
	std::map<std::string, std::shared_ptr<T>> StatesMap;

public:
	T* State;

	void SetStatesList(std::map <std::string, std::shared_ptr<T>> statesMap)
	{
		StatesMap = statesMap;
	}

	void ChangeState(std::string NewState)
	{
		if (State != nullptr)
		{
			State->Stop();
			delete State;
		}

		State = StatesMap.at(NewState).get();
		State->Start();
	}
};
