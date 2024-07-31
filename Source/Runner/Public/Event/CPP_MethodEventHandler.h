
#pragma once

#include <cassert>
#include "CPP_EventHandler.h"
#include "CoreMinimal.h"

template<class TObject, class ...TParams>
class CPP_MethodEventHandler : public CPP_EventHandler<TParams...>
{
	using TMethod = void(TObject::*)(TParams...);

private:
	TObject& Object;
	TMethod Method;
public:
    CPP_MethodEventHandler(TObject& object, TMethod method) :
        CPP_EventHandler<TParams...>(),
        Object(object),
        Method(method)
    {
        assert(Method != nullptr);
    }
    virtual void Call(TParams... params) override final
    {
        (Object.*Method)(params...);
    }
};

template<class TObject, class ...TParams>
CPP_EventHandler<TParams...>& createMethodEventHandler(TObject& object, void(TObject::* method)(TParams...))
{
    return *new CPP_MethodEventHandler<TObject, TParams...>(object, method);
}

#define METHOD_HANDLER( Object, Method ) createMethodEventHandler(Object, &Method )
#define MY_METHOD_HANDLER( Method ) METHOD_HANDLER( *this, Method )