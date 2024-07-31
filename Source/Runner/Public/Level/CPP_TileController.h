
#pragma once

#include "Math/UnrealMathUtility.h"
#include "Level/CPP_Tile.h"
#include "ObjectPool/CPP_ObjectPool.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_TileController.generated.h"

UCLASS()
class RUNNER_API ACPP_TileController : public AActor
{
	GENERATED_BODY()
	
public:
	ACPP_TileController();

protected:
	virtual void BeginPlay() override;

private:
	int f = 0;
	void CreateTile();
	void Test();

public:	
	UPROPERTY(EditAnywhere)
	int TilesCount;
	UPROPERTY(EditAnywhere)
	float TileSize;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ACPP_Tile>> TilesList;

	TMap<int, CPP_ObjectPool<ACPP_Tile>> PoolList;

	FVector lastPosition = FVector(0, 0, 0);
};
