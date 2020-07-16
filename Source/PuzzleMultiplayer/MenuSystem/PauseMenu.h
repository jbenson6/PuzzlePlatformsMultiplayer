// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEMULTIPLAYER_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void MainMenu();

	UFUNCTION()
	void Cancel();

protected:
	virtual bool Initialize();

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* MenuButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UWidget* PauseMenu;

	APlayerController* Controller;

};
