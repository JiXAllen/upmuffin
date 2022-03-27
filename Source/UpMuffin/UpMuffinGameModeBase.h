// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UpMuffinGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UPMUFFIN_API AUpMuffinGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	int Score;
	
public:

	AUpMuffinGameModeBase();

	void CountScore();

	int GetScore() const;
	
};
