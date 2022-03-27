// Fill out your copyright notice in the Description page of Project Settings.


#include "Muffin.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMuffin::AMuffin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	JumpVelocity = FVector(0, 0 , 1500);
	SpeedInAir = 3500.0f;
	SpeedOnGround = 300.0f;
	
}

// Called when the game starts or when spawned
void AMuffin::BeginPlay()
{
	Super::BeginPlay();

	BeginJump = true;
	bDead = false;
	PC = Cast<APlayerController>(GetController());
	PC->bShowMouseCursor = true;
	
}

void AMuffin::MoveToMouseCursor()
{
	FVector MouseLocation, MouseDirection;
	PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	float YDirection = FMath::Clamp(MouseLocation.Y - GetActorLocation().Y, -1.0f, 1.0f);
	float ScaleValue = FMath::Clamp(FMath::Abs(MouseLocation.Y - GetActorLocation().Y)/100, 0.0f, 1.0f);
	FVector Direction = FVector(0, YDirection, 0);
	AddMovementInput(Direction, ScaleValue);
}

void AMuffin::JumpOnKeyPressed()
{
	if (BeginJump)
	{
		JumpLooping();
		BeginJump = false;
	}
}

void AMuffin::SetSpeed()
{
	if (GetCharacterMovement()->IsFalling()) GetCharacterMovement()->MaxWalkSpeed = SpeedInAir;
	else GetCharacterMovement()->MaxWalkSpeed = SpeedOnGround;
}

void AMuffin::ContinuedFalling()
{
	if (GetCharacterMovement()->Velocity.Z < 0)
	{
		UpdateTimer();
	}
	else if (GetCharacterMovement()->Velocity.Z > 0)
	{
		ResetTimer();
	}
	else
	{
		bDead = true;
	}
}

void AMuffin::AboutToDead()
{
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 80.150002f));
	bDead = true;
	RestartUI();
}

void AMuffin::JumpLooping()
{
	LaunchCharacter(JumpVelocity, false, true);
}

void AMuffin::QuitGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("Exit"));
}

// Called every frame
void AMuffin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bDead)
	{
		SetSpeed();
		MoveToMouseCursor();
		if (!BeginJump) 
		ContinuedFalling();
	}
}

// Called to bind functionality to input
void AMuffin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMuffin::JumpOnKeyPressed);
	PlayerInputComponent->BindAction("Quit", IE_Pressed, this, &AMuffin::QuitGame);
}

