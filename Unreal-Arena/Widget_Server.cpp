// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_Server.h"
#include "Arena.h"
#include "Monitor.h"
#include "EngineUtils.h"
#include "Materials/MaterialInterface.h"
#include "Components/Image.h"
#include "SlateBrush.h"
#include "UObject/ConstructorHelpers.h"

UWidget_Server::UWidget_Server(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	MonitorsInfo = "";
	// Load render materials dynamically
	UMaterialInterface* Asset_Monitor_0 = LoadObjFromPath<UMaterialInterface>(TEXT("Material'/Game/RenderTarget/Monitor_0/M_Monitor_0.M_Monitor_0'"));
	UMaterialInterface* Asset_Monitor_1 = LoadObjFromPath<UMaterialInterface>(TEXT("Material'/Game/RenderTarget/Monitor_1/M_Monitor_1.M_Monitor_1'"));

	Array_Material.Add(Asset_Monitor_0);
	Array_Material.Add(Asset_Monitor_1);
}

// Add new output message to the terminal
inline FText UWidget_Server::Output(FString PrimitiveString, const FString Command, const FString Output) const {
	if (Command == "clear") {
		return FText::FromString("OVH-Server : ~ eliot$ ");
	}

	PrimitiveString.Append(Command+"\r\n"+Output+"\r\n"+"OVH-Server : ~ eliot$ ");
	return FText::FromString(PrimitiveString);
}

// Parse the command of server
FText UWidget_Server::ParseCommand(const FText Command, const FText PrimitiveText){
	FString strCommand = Command.ToString();
	if (strCommand == "") {
		return Output(PrimitiveText.ToString(), "", "");
	}
	/*
		1. Signal Command
		2. Command with Option
	*/
	const FString Info_help = "Welcome to OVH Server\r\n\
	Now, We have these softwares:\r\n\
	1. help --- As you know\r\n\
	2. clear --- Clear the text of terminal\r\n\
	3. monitor --- Operate monitoring equipment. Type -h for more details";
	const FString Info_monitor = "Usage: monitor [option]\r\n\
	options:\r\n\
	-l : List all the available monitors\r\n\
	-m [index] : Show the view of appointed monitor";

	int32 nPos = strCommand.Find("-");
	if (nPos == -1) {
		// Signal Command
		if (strCommand == "help") {
			return Output(PrimitiveText.ToString(), "help", Info_help);
		}
		else if (strCommand == "monitor") {
			return Output(PrimitiveText.ToString(), "monitor", Info_monitor);
		}
		else if (strCommand == "clear") {
			return Output("", "clear", "");
		}
	}
	else {
		// Command with Option
		FString option = strCommand.Right(strCommand.Len() - nPos-1).Left(1);
		// BackUp - if the option is '-m', get its index
		FString strIndex = strCommand.Right(1);
		strCommand = strCommand.Left(nPos - 1);

		if (strCommand == "monitor") {
			// Init some values
			bOption_Monitor_M = false;
			nMonitorIndex = 0;
			B_MonitorIndex = FText::FromString(TEXT("N/A"));
			B_MonitorLocation = FText::FromString(TEXT("N/A"));
			B_MonitorModel = FText::FromString(TEXT("N/A"));

			switch (**option) {
			case 'l':
				return Output(PrimitiveText.ToString(), "monitor -l", GetAllMonitors());
			case 'm':
				bOption_Monitor_M = true;
				nMonitorIndex = FCString::Atoi(*strIndex);
				if (Array_Monitor.Num() == 0)
					GetAllMonitors();
				GetMonitorInfo(strIndex);
				return Output(PrimitiveText.ToString(), "monitor -m "+strIndex, TEXT("Get the view of monitor successully : "+strIndex));
			default:
				return Output(PrimitiveText.ToString(), strCommand+" -"+option, TEXT("Unknown option : -"+option));
			}
		}
	}

	return Output(PrimitiveText.ToString(), strCommand, TEXT("OVH-Server: command not found: " + strCommand));
}

// Get all monitors that in the level
FString UWidget_Server::GetAllMonitors() {
	if (Array_Monitor.Num() != 0) {
		return MonitorsInfo;
	}

	for (TActorIterator<AMonitor> MonitorIter(GetWorld()); MonitorIter; ++MonitorIter) {
		Array_Monitor.Add(*MonitorIter);
		MonitorsInfo.Append("Index : "+MonitorIter->Monitor_Index.ToString()+"\r\n"+\
											"Location : "+MonitorIter->Monitor_Location.ToString()+"\r\n"+\
											"Model : "+MonitorIter->Monitor_Model.ToString()+"\r\n");
	}

	return MonitorsInfo;
}

// Set material that contains render target to Image in UMG
inline UMaterialInterface* UWidget_Server::GetRenderMaterial(const int32 nIndex) const {
	return Array_Material[nIndex];
}

// Get specified monitor info
inline void UWidget_Server::GetMonitorInfo(const FString Index) {
	for (auto Monitor  : Array_Monitor) {
		if (Monitor->Monitor_Index.ToString() == Index) {
			B_MonitorIndex = FText::FromName(Monitor->Monitor_Index);
			B_MonitorLocation = FText::FromName(Monitor->Monitor_Location);
			B_MonitorModel = FText::FromName(Monitor->Monitor_Model);
			break;
		}
	}
}