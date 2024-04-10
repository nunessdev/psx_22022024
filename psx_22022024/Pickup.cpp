// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/BoxComponent.h"
#include "ComponentVisualizer.h"
#include "PlayableCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	RootComponent = PickupRoot;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Conffigure PickupBox
	PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
	PickupBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	PickupBox->SetGenerateOverlapEvents(true);
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPlayerEnterPickupBox);
	PickupBox->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);

	
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherCommp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Destroy the pickup
	Destroy();
	// Get the player character
	APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PlayableCharacter) {
		PlayableCharacter->PickUpItem();
	}
}

