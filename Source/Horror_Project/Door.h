// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class HORROR_PROJECT_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Bilesenler
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	USceneComponent* HingeRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	UStaticMeshComponent* DoorMesh;

	// Tasarim Ayarlari
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoorSettings")
	float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoorSettings")
	float OpenSpeed = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoorSettings")
	bool bIsLocked = false;

	void ToggleDoor(const FVector& InteractionLocation);

private:
	bool bIsOpen = false;
	float CurrentYaw = 0.0f;
	float TargetYaw = 0.0f;
};
