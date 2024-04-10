// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class PSX_22022024_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Invisible ing, root for everything else
	UPROPERTY(EditAnywhere)
	USceneComponent* PickupRoot;

	// Static mesh for the pickup
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MyMesh;

	// When the player enters this box, it picks the pickup up
	UPROPERTY(EditAnywhere)
	UShapeComponent* PickupBox;

	UFUNCTION()
	void OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherCommp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Variable that keeps track of pickups collected
	int n_pickup = 0;
};
