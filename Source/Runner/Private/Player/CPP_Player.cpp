
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

	DownCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DownCollider"));
	DownCollider->SetupAttachment(GetRootComponent());
	BodyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyCollider"));
	BodyCollider->SetupAttachment(GetRootComponent());

	data = new CPP_PlayerData();
	data->player = this;
}

void ACPP_Player::BeginPlay()
{
	Super::BeginPlay();
	CreateStateMachine();
	UE_LOG(LogConsoleResponse, Log, TEXT("005"));

}

void ACPP_Player::CreateStateMachine()
{
	UE_LOG(LogConsoleResponse, Log, TEXT("002"));
	std::map<std::string, std::shared_ptr<CPP_PlayerStates>> statesMap;

	statesMap.insert({ typeid(CPP_PlayerIdleStates).name(), std::make_shared<CPP_PlayerIdleStates>(*StateMachine, data) });
	statesMap.insert({ typeid(CPP_PlayerRunStates).name(), std::make_shared<CPP_PlayerRunStates>(*StateMachine, data) });
	statesMap.insert({ typeid(CPP_PlayerDeadStates).name(), std::make_shared<CPP_PlayerDeadStates>(*StateMachine, data) });

	StateMachine->SetStatesList(statesMap);
	StateMachine->ChangeState(typeid(CPP_PlayerRunStates).name());
}

void ACPP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StateMachine->State->Update(DeltaTime);

}

void ACPP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	UE_LOG(LogConsoleResponse, Log, TEXT("003"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPP_Player::JumpAction);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ACPP_Player::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ACPP_Player::MoveRight);
	PlayerInputComponent->BindAction("Slide", IE_Pressed, this, &ACPP_Player::Slide);
}

void ACPP_Player::MoveLeft()
{
	StateMachine->State->MoveLeft();
}

void ACPP_Player::MoveRight()
{
	StateMachine->State->MoveRight();
}

void ACPP_Player::JumpAction()
{
	StateMachine->State->Jump();
}

void ACPP_Player::Slide()
{
	StateMachine->State->Slide();
}

void ACPP_Player::Test()
{
	UE_LOG(LogConsoleResponse, Log, TEXT("Fack"));
	StateMachine->State->MoveLeft();
}

void ACPP_Player::StartRun()
{
	StateMachine->ChangeState(typeid(CPP_PlayerRunStates).name());
}

