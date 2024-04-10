// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "Camera//CameraComponent.h"

float InterpolationStartTime;
FTimerHandle CameraMoveTimerHandle;

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// WASD movement
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayableCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayableCharacter::MoveRight);

	// Camera movement
	PlayerInputComponent->BindAxis("TurnCamera", this, &APlayableCharacter::TurnCamera);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayableCharacter::LookUp);

	// Crouching
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayableCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayableCharacter::EndCrouch);

}

void APlayableCharacter::MoveForward(float InputValue)
{
	// Forward facing direction
	FVector ForwardDirection = GetActorForwardVector();
	// Changes position when pressed
	AddMovementInput(ForwardDirection, InputValue);
}

void APlayableCharacter::MoveRight(float InputValue)
{
	// Right facing direction
	FVector RightDirection = GetActorRightVector();
	// Changes position when pressed
	AddMovementInput(RightDirection, InputValue);
}

void APlayableCharacter::TurnCamera(float InputValue)
{
	AddControllerYawInput(InputValue);
}

void APlayableCharacter::LookUp(float InputValue)
{
	AddControllerPitchInput(InputValue);
}

void APlayableCharacter::BeginCrouch()
{
	Crouch();

	// Interpolate camera position when crouching
	FVector TargetCameraLocation = Camera->GetComponentLocation();
	TargetCameraLocation.Z -= 50;
	Camera->SetWorldLocation(TargetCameraLocation);
	
}

void APlayableCharacter::EndCrouch()
{
	UnCrouch();

	// Interpolate camera position when standing up
	FVector TargetCameraLocation = Camera->GetComponentLocation();
	TargetCameraLocation.Z += 50; // Adjust this value based on your needs
	Camera->SetWorldLocation(TargetCameraLocation);
}
