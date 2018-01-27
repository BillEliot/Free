// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallLamp.generated.h"

UCLASS()
class ARENA_API AWallLamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallLamp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	class USceneComponent *pScene;
	UPROPERTY(EditAnywhere, Category = "Component")
		class UStaticMeshComponent *SM_WallLamp;
	UPROPERTY(EditAnywhere, Category = "Component")
		class UPointLightComponent *PointLIght;
};
