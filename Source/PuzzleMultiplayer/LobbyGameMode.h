// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleMultiplayerGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMULTIPLAYER_API ALobbyGameMode : public APuzzleMultiplayerGameMode
{
	GENERATED_BODY()

public:

	void PostLogin(APlayerController* NewPlayer) override;

	void Logout(AController* Exiting) override;

private:

	void StartGame();
	
	FTimerHandle GameStartTimer;

	uint32 PlayerCount = 0;
	
};
