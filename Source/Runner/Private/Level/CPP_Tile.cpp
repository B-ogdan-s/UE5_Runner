
#include "Level/CPP_Tile.h"
#include "Player/CPP_Player.h"

ACPP_Tile::ACPP_Tile()
{
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);
}

void ACPP_Tile::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentEndOverlap.AddDynamic(this, &ACPP_Tile::OnTileExit);
}

void ACPP_Tile::OnTileExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->IsA(ACPP_Player::StaticClass()))
		{
			SetActorEnableCollision(false);
			SetActorTickEnabled(false);
			SetActorHiddenInGame(true);

			OnTileExitF();
		}
	}
}
