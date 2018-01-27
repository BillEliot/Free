// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Server.generated.h"

/**
 * 
 */
UCLASS()
class ARENA_API UWidget_Server : public UUserWidget
{
	GENERATED_BODY()

public:
	UWidget_Server(const FObjectInitializer& ObjectInitializer);

protected:
	TArray<class AMonitor*> Array_Monitor;
	TArray<class UMaterialInterface*> Array_Material;

	UPROPERTY(BlueprintReadOnly)
	bool bOption_Monitor_M;
	UPROPERTY(BlueprintReadOnly)
	int32 nMonitorIndex;
	UPROPERTY(BlueprintReadOnly)
	FText B_MonitorIndex;
	UPROPERTY(BlueprintReadOnly)
	FText B_MonitorLocation;
	UPROPERTY(BlueprintReadOnly)
	FText B_MonitorModel;

	FString MonitorsInfo;

	UFUNCTION(BlueprintCallable)
	FText ParseCommand(const FText Command, const FText PrimitiveText);
	UFUNCTION(BlueprintCallable)
	inline class UMaterialInterface* GetRenderMaterial(const int32 nIndex) const;
	inline FText Output(FString PrimitiveString, const FString Command, const FString Output) const;
	FString GetAllMonitors();
	inline void GetMonitorInfo(const FString Index);

	//TEMPLATE - Load Object From Path
	template <typename ObjClass>
	static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;
		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString())); 
	}
};
  