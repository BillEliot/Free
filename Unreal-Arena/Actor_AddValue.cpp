// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor_AddValue.h"

#include "Components/SphereComponent.h"
#include "Engine/Engine.h"


// Sets default values
AActor_AddValue::AActor_AddValue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialise value
	Amplitude = 200.0f;
	AddHP = 0;
	AddMP = 0;

	// Create Subobject Component
	pSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	pSphereCollision->SetupAttachment(RootComponent);
	pSphereCollision->SetSphereRadius(32.f);
	pSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AActor_AddValue::Overlap_Sphere);
}

// Called when the game starts or when spawned
void AActor_AddValue::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActor_AddValue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Make the object float up and down
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = FMath::Sin(fRunningTime+DeltaTime) - FMath::Sin(fRunningTime);
	NewLocation.Z += DeltaHeight * Amplitude;
	SetActorLocation(NewLocation);
	fRunningTime += DeltaTime - Rate;
}

// Overlap Sphere Collision
void AActor_AddValue::Overlap_Sphere(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// Check whether the overlapped actor is player
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::White, TEXT("AddHP"));
}