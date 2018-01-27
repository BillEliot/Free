// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Server.generated.h"

UCLASS()
class ARENA_API AServer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AServer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	class UStaticMeshComponent* pSM_Server;
	class USphereComponent* pSphereCollision;
	class APlayerController* pController;
	TSubclassOf<UUserWidget> Widget_Server;
	UPROPERTY(BlueprintReadOnly)
	class UUserWidget* pWidget;
	UPROPERTY(BlueprintReadOnly)
	bool bIsInTrigger;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex);
};
