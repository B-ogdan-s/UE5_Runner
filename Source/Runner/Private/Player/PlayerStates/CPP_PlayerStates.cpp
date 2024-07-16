
#include "Player/PlayerStates/CPP_PlayerStates.h"

CPP_PlayerStates::CPP_PlayerStates(CPP_StateMachine<CPP_PlayerStates> stateMachine, CPP_PlayerData* data)
{
	*StateMachine = stateMachine;
	Data = data;
}

void CPP_PlayerRunStates::Update()
{
	Data->player->AddMovementInput(Data->player->GetActorForwardVector(), 1);
}
