// Fill out your copyright notice in the Description page of Project Settings.

#include "WallLamp.h"

#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"

// Sets default values
AWallLamp::AWallLamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	pScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SM_WallLamp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_WallLamp"));
	PointLIght = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));

	RootComponent = pScene;
	SM_WallLamp->SetupAttachment(pScene);
	PointLIght->SetupAttachment(SM_WallLamp);
}

// Called when the game starts or when spawned
void AWallLamp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallLamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

