// Fill out your copyright notice in the Description page of Project Settings.
#include "P0_Character.h"
#include"Net/UnrealNetwork.h"
#include "P0_InteractionComponent.h"
#include "P0_PlayerController.h"
#include "P0_Projectile.h"
#include "P0_StaminaComponent.h"
#include "P0_ThrownProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"

float WALK_SPEED = 400;
float WALK_ACCEL = 200;

// Sets default values
AP0_Character::AP0_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicated = true;
	GetCharacterMovement()->SetIsReplicated(true);
	SetReplicateMovement(true);

	// Configure character to turn in the direction it's moving.
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Movement values to change when necessary/to fine tune
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	// bUseControllerRotationPitch = false;
	// bUseControllerRotationYaw = false;
	// bUseControllerRotationRoll = false;

	// Create component and attach
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	// Interaction component
	InteractionComponent = CreateDefaultSubobject<UP0_InteractionComponent>(TEXT("InteractionComponent"));

	// Health and Stamina components
	HealthComp = CreateDefaultSubobject<UP0_HealthComponent>(TEXT("HealthComp"));
	StaminaComp = CreateDefaultSubobject<UP0_StaminaComponent>(TEXT("StaminaComp"));
}

// Called when the game starts or when spawned
void AP0_Character::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);

	AP0_PlayerController* PlayerController = Cast<AP0_PlayerController>(GetWorld()->GetFirstPlayerController());

	if (IsLocallyControlled())
	{
		if (PlayerController)
		{
			StatsWidget = CreateWidget<UP0_PlayerStatsWidget>(PlayerController, StatsWidgetClass);
			if (StatsWidget)
			{
				StatsWidget->AddToViewport();
				StatsWidget->SetOwningPlayer(PlayerController);
			}
		}
	}
}

// Called every frame
void AP0_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AP0_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent =
		CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind the MoveAction to the Move function if the MoveAction is valid.
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,
			                                   this, &AP0_Character::Move);
		}
		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered,
			                                   this, &AP0_Character::Look);
		}
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered,
			                                   this, &AP0_Character::Jump);
		}
		if (InteractAction)
		{
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started,
			                                   this, &AP0_Character::Interact);
		}
		if (RunAction)
		{
			EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AP0_Character::Run);
			EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AP0_Character::StopRun);
		}
		if (ShootAction)
		{
			EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started,
			                                   this, &AP0_Character::ShootProjectile);
		}
	}
}

void AP0_Character::Run()
{
	// GEngine->AddOnScreenDebugMessage(-1, 1.2, FColor::Blue, TEXT("Running"));

	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED + WALK_ACCEL;
	bIsRunning = true;
}

void AP0_Character::StopRun()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.2, FColor::Blue, TEXT("Stopping"));

	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
	bIsRunning = false;
}

void AP0_Character::ShootProjectile(const FInputActionValue& Value)
{
	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ProjectileClass is null"));
		return;
	}
	if (StaminaComp && !StaminaComp->UseStamina(ProjectileCost)) { return; }

	if (!IsLocallyControlled()) { return; }
	FVector SpawnLocation = GetActorLocation() + GetActorRotation().RotateVector(ProjectileSpawnOffset);
	FRotator SpawnRotation = GetControlRotation();

	// FActorSpawnParameters SpawnParams;
	// SpawnParams.Owner = this;
	// SpawnParams.Instigator = GetInstigator();
	//
	// GetWorld()->SpawnActor<AP0_ThrownProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	ServerShootProjectile(SpawnLocation, SpawnRotation);
}


void AP0_Character::Interact()
{
	if (!IsLocallyControlled()) { return; }

	// if (InteractionComponent)
	// {
	// 	InteractionComponent->LineTraceInteract();
	// }
	ServerInteract();
}

void AP0_Character::Move(const FInputActionValue& Value)
{
	// Get the 2D vector value from the input action.
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Get the controller's rotation. We only want to move based on the Yaw.
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get the forward and right direction vectors from the controller's yaw rotation.
		const FVector ForwardDirection =
			FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection =
			FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement input in the forward/backward and right/left directions.
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AP0_Character::Look(const FInputActionValue& Value)
{
	// Get the 2D vector value from the input action.
	const FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(-(LookVector.Y));
	}
}

void AP0_Character::ServerInteract_Implementation()
{
	if (!HasAuthority()) { return; }

	if (InteractionComponent)
	{
		InteractionComponent->LineTraceInteract();
	}
}

void AP0_Character::ServerShootProjectile_Implementation(FVector SpawnLocation, FRotator SpawnRotation)
{
	if (!HasAuthority()) { return; }
	if (!ProjectileClass) { return; }
	if (StaminaComp && !StaminaComp->UseStamina(ProjectileCost)) { return; }

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AP0_ThrownProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
}

void AP0_Character::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
