#include "Flashlight.h"
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFlashlight::AFlashlight()
{
	PrimaryActorTick.bCanEverTick = false;

	SpotLightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpotLightMesh"));
	RootComponent = SpotLightMesh;
	SpotLightMesh->SetSimulatePhysics(true);
	SpotLightMesh->SetCollisionProfileName(TEXT("PhysicsActor"));

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(SpotLightMesh);

	// Isik ayarlari
	SpotLight->SetIntensity(4500.0f);
	SpotLight->SetLightColor(FLinearColor(1.0f, 0.90f, 0.72f));
	SpotLight->SetInnerConeAngle(10.0f);
	SpotLight->SetOuterConeAngle(24.0f);
	SpotLight->SetAttenuationRadius(1400.0f);
	SpotLight->SetVisibility(false);
}

void AFlashlight::ToggleFlashlight()
{
	bIsOn = !bIsOn;
	SpotLight->SetVisibility(bIsOn);
	if (ToggleSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ToggleSound, GetActorLocation());
	}
}

void AFlashlight::PickUp(USceneComponent* AttachTarget)
{
	SpotLightMesh->SetSimulatePhysics(false);
	SpotLightMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttachToComponent(AttachTarget, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SetActorRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
}

void AFlashlight::Drop(FVector ThrowDirection)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SpotLightMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SpotLightMesh->SetSimulatePhysics(true);
	SpotLightMesh->AddImpulse(ThrowDirection * 120.0f, NAME_None, true);
}

