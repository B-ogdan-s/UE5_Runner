#pragma once

#include <vector>
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"

template<typename T>
concept IsActor = std::is_base_of<AActor, T>::value;

template<IsActor T>
class CPP_ObjectPool
{
private:
	AActor* UserActor;
	TSubclassOf<T>* PrefabObject;
	std::vector<T*> PoolObjectsList = std::vector<T*>();

private:
	T* SpawnNemObject();

public:
	CPP_ObjectPool(AActor* userActor, TSubclassOf<T>* prefabObject);

	T* GetFreeObject();
	int GetSize();
	void EnableObject(T* Odject);
};

template<IsActor T>
CPP_ObjectPool<T>::CPP_ObjectPool(AActor* userActor, TSubclassOf<T>* prefabObject)
{
	UserActor = userActor;
	PrefabObject = prefabObject;
}

template<IsActor T>
T* CPP_ObjectPool<T>::SpawnNemObject()
{
	FVector Pos = FVector(0, 0, 0);
	FRotator Rot = FRotator(0, 0, 0);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = UserActor;
	SpawnParams.Instigator = UserActor->GetInstigator();


	T* newObject = UserActor->GetWorld()->SpawnActor<T>(*PrefabObject, Pos, Rot, SpawnParams);
	PoolObjectsList.push_back(newObject);
	return newObject;
}

template<IsActor T>
T* CPP_ObjectPool<T>::GetFreeObject()
{
	for (T* obj : PoolObjectsList)
	{
		if (obj->IsHidden())
		{
			EnableObject(obj);
			return obj;
		}
	}
	return SpawnNemObject();
}

template<IsActor T>
int CPP_ObjectPool<T>::GetSize()
{
	return PoolObjectsList.size();
}

template<IsActor T>
void CPP_ObjectPool<T>::EnableObject(T* Object)
{
	Object->SetActorEnableCollision(true);
	Object->SetActorTickEnabled(true);
	Object->SetActorHiddenInGame(false);
}