// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cloud.h"
#include "Muffin.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameCarema.generated.h"

UCLASS()
class UPMUFFIN_API AGameCarema : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCarema();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	APlayerController* PC;

	AMuffin* Muffin;

	void MoveCamera();

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* DestroyArea;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	ACloud* Cloud;

};

