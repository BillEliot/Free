// Fill out your copyright notice in the Description page of Project Settings.

#include "Monitor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMonitor::AMonitor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	pSM_Monitor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Monitor"));
	pCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Camera"));

	pSM_Monitor->SetupAttachment(RootComponent);
	pCamera->SetupAttachment(RootComponent);

	pSM_Monitor->SetRelativeScale3D(FVector(6.f, 6.f, 6.f));
	pCamera->SetRelativeRotation(FRotator(0, 90.f, 0));
	pCamera->SetRelativeLocation(FVector(0, 10.f, 0));

	ConstructorHelpers::FObjectFinder<UStaticMesh> Asset_Monitor(TEXT("StaticMesh'/Game/Props/Monitor/Monitor.Monitor'"));

	if (Asset_Monitor.Succeeded()) {
		pSM_Monitor->SetStaticMesh(Asset_Monitor.Object);
	}
}

// Called when the game starts or when spawned
void AMonitor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonitor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

