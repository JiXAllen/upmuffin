// Copyright Epic Games, Inc. All Rights Reserved.


#include "UpMuffinGameModeBase.h"

AUpMuffinGameModeBase::AUpMuffinGameModeBase()
{
	Score = 0;
}

void AUpMuffinGameModeBase::CountScore()
{
	Score++;
}

int AUpMuffinGameModeBase::GetScore() const
{
	return Score;
}
