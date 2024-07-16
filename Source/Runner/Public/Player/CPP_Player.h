
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Statemachine/CPP_Statemachine.h"
#include "Player/PlayerStates/CPP_PlayerStates.h"
#include "Player/CPP_PlayerData.h"
#include "CPP_Player.generated.h"

UCLASS()
class RUNNER_API ACPP_Player : public ACharacter
{
	GENERATED_BODY()

public:
	ACPP_Player();

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* Arm;
	class CPP_StateMachine<CPP_PlayerStates>* StateMachine = new CPP_StateMachine<CPP_PlayerStates>();

protected:
	virtual void BeginPlay() override;

private:
	CPP_PlayerData* data;

private: 
	void CreateStateMachine();
};

