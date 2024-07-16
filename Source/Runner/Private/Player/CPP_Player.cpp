
#include "Player/CPP_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACPP_Player::ACPP_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Arm->SetupAttachment(GetRootComponent());
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->AttachToComponent(Arm, FAttachmentTransformRules::KeepRelativeTransform);

	data = new CPP_PlayerData();
	data->player = this;
}

void ACPP_Player::BeginPlay()
{
	Super::BeginPlay();
	CreateStateMachine();
}

void ACPP_Player::CreateStateMachine()
{
	std::map<std::string, std::shared_ptr<CPP_PlayerStates>> statesMap;

	statesMap.insert({ typeid(CPP_PlayerIdleStates).name(), std::make_shared<CPP_PlayerIdleStates>(*StateMachine, data) });
	statesMap.insert({ typeid(CPP_PlayerRunStates).name(), std::make_shared<CPP_PlayerRunStates>(*StateMachine, data) });
	statesMap.insert({ typeid(CPP_PlayerDeadStates).name(), std::make_shared<CPP_PlayerDeadStates>(*StateMachine, data) });

	StateMachine->SetStatesList(statesMap);
	StateMachine->ChangeState(typeid(CPP_PlayerIdleStates).name());
}

void ACPP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StateMachine->State->Update();

}

void ACPP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

