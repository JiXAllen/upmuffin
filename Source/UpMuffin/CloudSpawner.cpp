// Fill out your copyright notice in the Description page of Project Settings.


#include "CloudSpawner.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACloudSpawner::ACloudSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	SpawnerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnerArea"));
	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerArea"));

	RootComponent = DefaultRootComp;
	SpawnerArea->SetupAttachment(RootComponent);
	TriggerArea->SetupAttachment(RootComponent);

	SpawnRisingDistance = 300.0f;
	InitialCloudNum = 6;

}

// Called when the game starts or when spawned
void ACloudSpawner::BeginPlay()
{
	Super::BeginPlay();
	while(InitialCloudNum > 0)
	{
		SpawnCloud();
		InitialCloudNum--;
	}
}

void ACloudSpawner::SpawnCloud()
{
	FVector SpawnOrigin = SpawnerArea->Bounds.Origin;
	FVector SpawnExtent = SpawnerArea->Bounds.BoxExtent;
	float YLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent).Y;
	FVector SpawnLocation = FVector(SpawnerArea->GetComponentLocation().X, YLocation, SpawnerArea->GetComponentLocation().Z);

	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<ACloud>(Cloud, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);

	AddActorWorldOffset(FVector(0,0,SpawnRisingDistance));
}

// Called every frame
void ACloudSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACloudSpawner::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	Muffin = Cast<AMuffin>(OtherActor);
	if (Muffin)
	{
		SpawnCloud();
	}
}

