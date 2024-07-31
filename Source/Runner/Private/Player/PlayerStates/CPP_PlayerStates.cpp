
#include "Player/PlayerStates/CPP_PlayerStates.h"

CPP_PlayerStates::CPP_PlayerStates(CPP_StateMachine<CPP_PlayerStates> stateMachine, CPP_PlayerData* data)
{
	*StateMachine = stateMachine;
	Data = data;
}

void CPP_PlayerStates::Jump(){}
void CPP_PlayerStates::MoveLeft(){}
void CPP_PlayerStates::MoveRight(){}
void CPP_PlayerStates::Slide(){}

void CPP_PlayerRunStates::UpdateRightDirection()
{
	if (InputList.size() == 0)
	{
		return;
	}

	int newLineNum = lineNum + InputList.front();

	if (newLineNum > Data->maxLine || newLineNum < Data->minLine)
	{
		InputList.pop();
		UpdateRightDirection();
		return;
	}

	lerpElapsedTime = 0;

	endPosition = newLineNum * Data->lineWhide;
	startPosition = lineNum * Data->lineWhide;

	lineNum = newLineNum;

	isChangeLine = true;

	InputList.pop();
}

void CPP_PlayerRunStates::Update(float tick)
{
	Data->player->AddMovementInput(Data->player->GetActorForwardVector(), Data->speed);

	if (isChangeLine)
	{
		lerpElapsedTime += tick;
		float alpha = lerpElapsedTime / Data->changeLineTime;

		FVector newPosition = Data->player->GetActorLocation();
		newPosition.Y = FMath::Lerp(startPosition, endPosition, alpha);

		Data->player->SetActorLocation(newPosition);

		if (lerpElapsedTime >= Data->changeLineTime)
		{
			newPosition.Y = endPosition;
			Data->player->SetActorLocation(newPosition);

			isChangeLine = false;
			UpdateRightDirection();
		}
	}
}

void CPP_PlayerRunStates::Jump()
{
	Data->player->Jump();

}

void CPP_PlayerRunStates::MoveLeft()
{
	InputList.push(-1);

	if (!isChangeLine)
		UpdateRightDirection();
}

void CPP_PlayerRunStates::MoveRight()
{
	InputList.push(1);

	if(!isChangeLine)
		UpdateRightDirection();
}

void CPP_PlayerRunStates::Slide()
{
}

