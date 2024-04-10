// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class PSX_22022024_API APlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Variable to keep track of number of picked up objects
	int32 numItemsPickedUp = 0;

	// Function to increment the value of numItemsPickedUp
	UFUNCTION(BlueprintCallable)
	void PickUpItem();

	// Getter function to get current numItemsPickedUp value
	UFUNCTION(Blueprintcallable, Category = "Pickup")
	int32 GetNumItemsPickedUp() const { return numItemsPickedUp; }


protected:

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	void MoveForward(float InptVector);
	void MoveRight(float InptVector);

	void TurnCamera(float InputValue);
	void LookUp(float InputValue);

	void BeginCrouch();
	void EndCrouch();

};
