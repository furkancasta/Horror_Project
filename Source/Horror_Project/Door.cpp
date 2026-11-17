// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	RootComponent = DoorFrame;

	HingeRoot = CreateDefaultSubobject<USceneComponent>(TEXT("HingeRoot"));
	HingeRoot->SetupAttachment(DoorFrame);
	HingeRoot->SetRelativeLocation(FVector(-60.0f, 0.0f, 0.0f));

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(HingeRoot);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoor::ToggleDoor(const FVector& InteractionLocation)
{
	if (bIsLocked)
	{
		// Kapı kilitliyse, açma işlemi yapılmaz
		return;
	}
	
	bIsOpen = !bIsOpen;

	if (bIsOpen)
	{
		FVector DirectionToPlayer = (InteractionLocation - GetActorLocation()).GetSafeNormal();
		float Dot = FVector::DotProduct(GetActorRightVector(), DirectionToPlayer);

		TargetYaw = (Dot > 0) ? -OpenAngle : OpenAngle;
	}
	else
	{
		TargetYaw = 0.0f;
	}
	SetActorTickEnabled(true);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, OpenSpeed);
	HingeRoot->SetRelativeRotation(FRotator(0.0f, CurrentYaw, 0.0f));

	if (FMath::IsNearlyEqual(CurrentYaw, TargetYaw, 0.1f))
	{
		HingeRoot->SetRelativeRotation(FRotator(0.0f, TargetYaw, 0.0f));
		SetActorTickEnabled(false);
	}
}

