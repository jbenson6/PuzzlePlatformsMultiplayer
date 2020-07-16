// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"
#include "Engine/Engine.h"

bool UPauseMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(MenuButton != nullptr)) return false;
	MenuButton->OnClicked.AddDynamic(this, &UPauseMenu::MainMenu);

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UPauseMenu::Cancel);
	return true;
}


void UPauseMenu::MainMenu()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	Controller = World->GetFirstPlayerController();
	if (!ensure(Controller != nullptr)) return;
	if (Controller->HasAuthority()) 
	{
		World->ServerTravel("/Game/MenuSystem/MainMenu");
		UEngine* Engine = Controller->GetGameInstance()->GetEngine();
		if (!ensure(Engine != nullptr)) return;
		Engine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Host Ended Session"));
	}
	else 
	{
		Controller->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
	}

}

void UPauseMenu::Cancel()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	Controller = World->GetFirstPlayerController();
	if (!ensure(Controller != nullptr)) return;
	FInputModeGameOnly InputModeData;
	Controller->bShowMouseCursor = false;
	Controller->SetInputMode(InputModeData);
	this->RemoveFromViewport();
}
