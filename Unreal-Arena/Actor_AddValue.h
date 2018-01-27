// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_AddValue.generated.h"

UCLASS()
class ARENA_API AActor_AddValue : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_AddValue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float fRunningTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float Amplitude;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float AddHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float AddMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float Rate;

	class USphereComponent* pSphereCollision;
	UFUNCTION()
		void Overlap_Sphere(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
