// Fill out your copyright notice in the Description page of Project Settings.


#include "P0_Torch.h"

#include "P0_Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Evaluation/IMovieSceneEvaluationHook.h"

// Sets default values
AP0_Torch::AP0_Torch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	(SetRootComponent(Root));

	TorchMesh = CreateDefaultSubobject<UStaticMeshComponent>("TorchMesh");
	TorchMesh->SetupAttachment(Root);

	TorchLight = CreateDefaultSubobject<UPointLightComponent>("TorchLight");
	TorchLight->SetupAttachment(TorchMesh);
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->SetupAttachment(TorchMesh);
	TriggerBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AP0_Torch::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AP0_Torch::OnComponentBeginOverlap);
}

// Called every frame
void AP0_Torch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AP0_Torch::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedObject, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                        const FHitResult& SweepResult)
{
	// Light if
	if (OtherActor && OtherActor->IsA(AP0_Projectile::StaticClass()) && !bIsLit)
	{
		LightTorch();
	}
}

void AP0_Torch::LightTorch()
{
	TorchLight->SetVisibility(true);
	bIsLit = true;
}
