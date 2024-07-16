
#pragma once

#include "CoreMinimal.h"
#include "StateMachine/CPP_StateMachine.h"
#include "StateMachine/CPP_State.h"
#include "Player/CPP_PlayerData.h"

class RUNNER_API CPP_PlayerStates : public CPP_State
{
public:
	CPP_PlayerStates(CPP_StateMachine<CPP_PlayerStates> stateMachine, CPP_PlayerData* data);

protected:
	CPP_PlayerData* Data;

private:
	class CPP_StateMachine<CPP_PlayerStates>* StateMachine = new CPP_StateMachine<CPP_PlayerStates>();
};


class  RUNNER_API CPP_PlayerIdleStates : public CPP_PlayerStates
{
public:
	CPP_PlayerIdleStates(CPP_StateMachine<CPP_PlayerStates> stateMachine, CPP_PlayerData* data) : CPP_PlayerStates(stateMachine, data) {}
};
class  RUNNER_API CPP_PlayerRunStates : public CPP_PlayerStates
{
public:
	CPP_PlayerRunStates(CPP_StateMachine<CPP_PlayerStates> stateMachine, CPP_PlayerData* data) : CPP_PlayerStates(stateMachine, data) {}
	void Update() override;
};
class  RUNNER_API CPP_PlayerDeadStates : public CPP_PlayerStates
{
public:
	CPP_PlayerDeadStates(CPP_StateMachine<CPP_PlayerStates> stateMachine, CPP_PlayerData* data) : CPP_PlayerStates(stateMachine, data) {}
};
