
#pragma once

#include "Event/CPP_Event.h"
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CPP_Tile.generated.h"

UCLASS()
class RUNNER_API ACPP_Tile : public AActor
{
	GENERATED_BODY()

public:
	CPP_Event<> OnTileExitF;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Collider;
	
private:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTileExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	ACPP_Tile();
};
