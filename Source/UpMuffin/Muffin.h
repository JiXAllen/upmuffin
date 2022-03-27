// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Muffin.generated.h"

UCLASS()
class UPMUFFIN_API AMuffin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMuffin();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APlayerController* PC;

	void MoveToMouseCursor();

	void JumpOnKeyPressed();

	void SetSpeed();

	void ContinuedFalling();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetTimer();

	UFUNCTION(BlueprintCallable)
	void AboutToDead();
	
	UPROPERTY(EditAnywhere)
	FVector JumpVelocity;

	UPROPERTY(EditAnywhere)
	float SpeedInAir;

	UPROPERTY(EditAnywhere)
	float SpeedOnGround;

	bool BeginJump;

	UFUNCTION(BlueprintImplementableEvent)
	void RestartUI();

	UPROPERTY(BlueprintReadOnly)
	bool bDead;
	
	void QuitGame();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void JumpLooping();

};


