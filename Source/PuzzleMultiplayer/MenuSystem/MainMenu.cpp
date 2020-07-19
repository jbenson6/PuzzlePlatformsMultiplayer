// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components\Button.h"
#include "UObject/ConstructorHelpers.h"
#include "Components\WidgetSwitcher.h"
#include "Components\EditableTextBox.h"
#include "Components\PanelWidget.h"
#include "ServerRow.h"
#include "Components\TextBlock.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;

	ServerRowClass = ServerRowBPClass.Class;
}



bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::OpenHostMenu);

	if (!ensure(JoinServerButton != nullptr)) return false;
	HostServerButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(JoinServerButton != nullptr)) return false;
	JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(CancelJoinButton != nullptr)) return false;
	CancelJoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(CancelHostButton != nullptr)) return false;
	CancelHostButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::Quit);

	return true;
}

void UMainMenu::HostServer()
{
	if (MenuI != nullptr)
	{
		MenuI->Host(ServerNameText->GetText().ToString());
	}
	
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
	if (MenuI != nullptr)
	{
		MenuI->RefreshServerList();
	}

}

void UMainMenu::OpenHostMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(HostMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(HostMenu);

}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
	if (SelectedIndex.IsSet() && MenuI != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index: %d"), SelectedIndex.GetValue());
		MenuI->Join(SelectedIndex.GetValue());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Selected Index Not Set"));
	}	
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuI = MenuInterface;
}

void UMainMenu::Setup()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	Controller = World->GetFirstPlayerController();
	if (!ensure(Controller != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	this->AddToViewport();

	Controller->SetInputMode(InputModeData);
	Controller->bShowMouseCursor = true;
}

void UMainMenu::Teardown()
{
	FInputModeGameOnly InputModeData;
	Controller->bShowMouseCursor = false;
	Controller->SetInputMode(InputModeData);
	this->RemoveFromViewport();
}

void UMainMenu::Quit()
{
	Controller->ConsoleCommand("quit");
}

void UMainMenu::SetServerList(TArray<FServerData> ServerNames)
{
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;

	ServerScrollBox->ClearChildren();

	uint32 i = 0;
	for (const FServerData& ServerData : ServerNames)
	{
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
		if (!ensure(Row != nullptr)) return;

		Row->ServerName->SetText(FText::FromString(ServerData.Name));
		Row->ServerPlayersText->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), ServerData.CurrentPlayers, ServerData.MaxPlayers)));
		Row->HostUsername->SetText(FText::FromString(ServerData.HostUsername));
		Row->Setup(this, i);
		++i;

		ServerScrollBox->AddChild(Row);
	}
	
	
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

void UMainMenu::UpdateChildren()
{
	
	for (int32 i = 0; i < ServerScrollBox->GetChildrenCount(); i++)
	{
		auto* Row = Cast<UServerRow>(ServerScrollBox->GetChildAt(i));
		if (Row != nullptr)
		{
			Row->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}
