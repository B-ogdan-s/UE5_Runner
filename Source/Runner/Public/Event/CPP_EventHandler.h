
#pragma once

#include "CoreMinimal.h"

template<class ...TParams>
class RUNNER_API CPP_EventHandler
{
public:
	virtual void Call(TParams... params) = 0;
protected:
	CPP_EventHandler() {}
};
