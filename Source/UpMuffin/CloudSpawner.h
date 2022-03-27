// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cloud.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CloudSpawner.generated.h"

UCLASS()
class UPMUFFIN_API ACloudSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACloudSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnCloud();

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SpawnerArea;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerArea;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultRootComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACloud> Cloud;

	AMuffin* Muffin;

	UPROPERTY(EditAnywhere)
	int InitialCloudNum;

	UPROPERTY(EditAnywhere)
	float SpawnRisingDistance;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
