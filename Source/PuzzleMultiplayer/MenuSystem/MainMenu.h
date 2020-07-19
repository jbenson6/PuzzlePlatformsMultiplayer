// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
};

/**
 * 
 */
UCLASS()
class PUZZLEMULTIPLAYER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* MenuInterface);
	void Setup();
	void Teardown();
	UMainMenu(const FObjectInitializer& ObjectInitializer);
	void SetServerList(TArray<FServerData> ServerNames);
	void SelectIndex(uint32 Index);

protected:
	virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinServerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostServerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelJoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelHostButton;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerScrollBox;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* ServerNameText;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
		void OpenHostMenu();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void Quit();

	TOptional<uint32> SelectedIndex;

	IMenuInterface* MenuI;

	APlayerController* Controller;

	TSubclassOf<class UUserWidget> ServerRowClass;

	void UpdateChildren();
};
