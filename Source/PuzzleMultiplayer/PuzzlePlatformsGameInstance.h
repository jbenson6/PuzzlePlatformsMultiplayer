// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMULTIPLAYER_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init();

	UFUNCTION(Exec)
	void Host(FString ServerName);

	UFUNCTION(Exec)
	void Join(uint32 Index);

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	void StartSession();


	void RefreshServerList() override;


private:
	
	TSubclassOf<class UUserWidget> MenuClass;
	
	class UMainMenu* MyMenu;
	
	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);

	void OnFindSessionComplete(bool Success);

	void OnJoinComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void CreateSession();

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	FString DesiredServerName;
};
