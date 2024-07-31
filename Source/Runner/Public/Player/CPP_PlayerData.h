
#pragma once

#include "GameFramework/Character.h"
#include "CoreMinimal.h"

struct RUNNER_API CPP_PlayerData
{
	class ACharacter* player;

	int startLine = 0;

	int minLine = -1;
	int maxLine = 1;

	float speed = 5;
	float changeLineTime = 0.2f;
	float jumpForce = 300;
	float lineWhide = 150;

};
