// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_NPCCharacter.h"
#include "P0_Character.h"
#include "P0_PlayerController.h"
#include "P0_DialogueWidget.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"
#include "P0_PlayerController.h"

// Sets default values
AP0_NPCCharacter::AP0_NPCCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionSphere = CreateDefaultSubobject<USphereComponent>("InteractionSphere");
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->SetSphereRadius(150);
	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	bReplicated = true;
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AP0_NPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	isDialogueActive = false;

	// Bind overlap events
	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AP0_NPCCharacter::OnInteractionSphereBeginOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AP0_NPCCharacter::OnInteractionSphereEndOverlap);
}

void AP0_NPCCharacter::OnInteractionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                       bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Overlapping");

	InteractingPlayer = Cast<AP0_Character>(OtherActor);
	if (InteractingPlayer)
	{
		StartDialogue();
	}
}

void AP0_NPCCharacter::OnInteractionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == InteractingPlayer)
	{
		InteractingPlayer = nullptr;
	}
}

void AP0_NPCCharacter::Interact_Implementation(AActor* Caller)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Hit Interact Impl in NPC");
	// Caller is the player who interacted
	InteractingPlayer = Cast<AP0_Character>(Caller);

	if (InteractingPlayer)
	{
		StartDialogue();
	}
}


void AP0_NPCCharacter::StartDialogue()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Calling ");

	if (!InteractingPlayer || !DialogueTable)
	{
		return;
	}

	if (isDialogueActive) { return; }
	isDialogueActive = true;

	AP0_PlayerController* PlayerController = Cast<AP0_PlayerController>(InteractingPlayer->GetController());

	if (!PlayerController) { return; }

	if (!DialogueWidget && DialogueWidgetClass)
	{
		DialogueWidget = CreateWidget<UP0_DialogueWidget>(PlayerController, DialogueWidgetClass);
		if (DialogueWidget)
		{
			DialogueWidget->AddToViewport(9999);
			DialogueWidget->OnDialogueEnded.AddDynamic(this, &AP0_NPCCharacter::OnDialogueEnded);

			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(DialogueWidget->TakeWidget());
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
	}
	if (DialogueWidget)
	{
		DialogueWidget->StartDialogue(DialogueTable, StartDialogueID);
	}
}

void AP0_NPCCharacter::OnDialogueEnded()
{
	isDialogueActive = false;
	if (DialogueWidget)
	{
		DialogueWidget->RemoveFromParent();
		DialogueWidget = nullptr;
	}
}


// Called every frame
void AP0_NPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AP0_NPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AP0_NPCCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AP0_NPCCharacter, InteractingPlayer);
}

void AP0_NPCCharacter::ServerStartDialogue_Implementation(AP0_Character* Caller)
{
	if (!HasAuthority() || !Caller) { return; }
	InteractingPlayer = Caller;
	APlayerController* Controller = Cast<APlayerController>(InteractingPlayer->GetController());
	if (!Controller) { return; }

	StartDialogue();
}
