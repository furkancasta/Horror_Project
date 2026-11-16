// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"
#include "Flashlight.generated.h"

UCLASS()
class HORROR_PROJECT_API AFlashlight : public AActor
{
	GENERATED_BODY()
	
public:	
	AFlashlight();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SpotLightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* ToggleSound;

	void ToggleFlashlight();
	void PickUp(USceneComponent* AttachTarget);
	void Drop(FVector ThrowDirection);

private:
	bool bIsOn = false;

};
