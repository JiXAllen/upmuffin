// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Muffin.h"
#include "UpMuffinGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Cloud.generated.h"

UCLASS()
class UPMUFFIN_API ACloud : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACloud();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Cloud;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* RainComp;
	
	UPROPERTY(EditAnywhere)
	TArray<UTexture*> Textures;

	UPROPERTY(BlueprintReadOnly)
	UMaterialInstanceDynamic* MaterialInstance;

	UMaterialInterface* MaterialInterface;

	void SetRandomMaterial();

	AMuffin* Muffin;

	AUpMuffinGameModeBase* GameModeRef;

	void DisplayScore();

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* ScoreTextComp;

	UFUNCTION(BlueprintImplementableEvent)
	void FadeOut();

	UPROPERTY(EditAnywhere)
	USoundCue* CollisionSoundCue;

	UPROPERTY(EditAnywhere)
	UAudioComponent* RainSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
