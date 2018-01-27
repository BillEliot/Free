// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/Engine.h"
#include "Components/SceneComponent.h"

inline void PrintMessage(FString Message) {
	GEngine->AddOnScreenDebugMessage(0, 10.f, FColor::Blue, Message);
}