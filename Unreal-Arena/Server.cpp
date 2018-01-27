// Fill out your copyright notice in the Description page of Project Settings.

#include "Server.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "UserWidget.h"


// Sets default values
AServer::AServer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AutoReceiveInput = EAutoReceiveInput::Player0; 

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	pSM_Server = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Server"));
	pSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

	pSM_Server->SetupAttachment(RootComponent);
	pSphereCollision->SetupAttachment(RootComponent);
	pSM_Server->SetRelativeScale3D(FVector(35.f, 35.f, 35.f));
	pSphereCollision->SetSphereRadius(180.f);
	pSphereCollision->SetRelativeLocation(FVector(0, 0, 50.f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> Asset_Server(TEXT("StaticMesh'/Game/Props/Server/Server.Server'"));
	if (Asset_Server.Succeeded()) {
		pSM_Server->SetStaticMesh(Asset_Server.Object);
	}

	pSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AServer::OnBeginOverlap);
	pSphereCollision->OnComponentEndOverlap.AddDynamic(this, &AServer::OnEndOverlap);
}

// Called when the game starts or when spawned
void AServer::BeginPlay()
{
	Super::BeginPlay();

	// Get Player Controller
	pController = UGameplayStatics::GetPlayerController(this, 0);
	// Create Widget
	Widget_Server = LoadClass<UUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/HUD/BPH_Server.BPH_Server_C'"));
	pWidget = CreateWidget<UUserWidget>(GetWorld(), Widget_Server);
}

// Called every frame
void AServer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Enter the Sphere Collision
void AServer::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// Enter the trigger
	bIsInTrigger = true;
}

// Exit the Sphere Collision
void AServer::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex) {
	// Exit the trigger
	bIsInTrigger = false;
}
