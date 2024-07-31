
#pragma once

#include "CoreMinimal.h"
#include <queue>
#include "StateMachine/CPP_StateMachine.h"
#include "StateMachine/CPP_State.h"
#include "Player/CPP_PlayerData.h"

class RUNNER_API CPP_PlayerStates : public CPP_State
{
public:
	CPP_PlayerStates(CPP_StateMachine<CPP_PlayerStates> stateMachine, CPP_PlayerData* data);
	virtual void Jump();
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void Slide();

protected:
	CPP_PlayerData* Data;
	class CPP_StateMachine<CPP_PlayerStates>* StateMachine = new CPP_StateMachine<CPP_PlayerStates>();
};


class  RUNNER_API CPP_PlayerIdleStates : public CPP_PlayerStates
{
public:
	CPP_PlayerIdleStates(CPP_StateMachine<CPP_PlayerStates> stateMachine, CPP_PlayerData* data) : CPP_PlayerStates(stateMachine, data) {}
};

class  RUNNER_API CPP_PlayerRunStates : public CPP_PlayerStates
{
private:
	std::queue<int> InputList;
	int lineNum;
	bool isChangeLine;
	float lerpElapsedTime = 0;
	float startPosition;
	float endPosition;

	void UpdateRightDirection();

public:
	CPP_PlayerRunStates(CPP_StateMachine<CPP_PlayerStates> stateMachine, CPP_PlayerData* data) : CPP_PlayerStates(stateMachine, data) 
	{
		lineNum = data->startLine;
	}
	void Update(float tick) override;

	void Jump() override;
	void MoveLeft() override;
	void MoveRight() override;
	void Slide() override;
};

class  RUNNER_API CPP_PlayerDeadStates : public CPP_PlayerStates
{
public:
	CPP_PlayerDeadStates(CPP_StateMachine<CPP_PlayerStates> stateMachine, CPP_PlayerData* data) : CPP_PlayerStates(stateMachine, data) {}
};
