
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Tile.generated.h"

UCLASS()
class RUNNER_API ACPP_Tile : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_Tile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
