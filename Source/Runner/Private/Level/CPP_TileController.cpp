
#include "Level/CPP_TileController.h"
#include "Event/CPP_MethodEventHandler.h"

ACPP_TileController::ACPP_TileController()
{
}

void ACPP_TileController::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < TilesCount; i++)
	{
		CreateTile();
	}
}


void ACPP_TileController::CreateTile()
{
	UE_LOG(LogTemp, Warning, TEXT("%d --------------------"), f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	int id = FMath::RandRange(0, TilesList.Num()-1);


	if (PoolList.Find(id) == nullptr)
	{
		PoolList.Add(id, CPP_ObjectPool<ACPP_Tile>(this, &TilesList[id]));
	}

	f++;

	CPP_ObjectPool<ACPP_Tile>* Pool = PoolList.Find(id);
	ACPP_Tile* Tile = Pool->GetFreeObject();

	Tile->OnTileExitF += METHOD_HANDLER(*this, ACPP_TileController::CreateTile);

	Tile->SetActorLocation(lastPosition);
	lastPosition.X += TileSize;
}

void ACPP_TileController::Test()
{
	UE_LOG(LogTemp, Warning, TEXT("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSssss"));
}


