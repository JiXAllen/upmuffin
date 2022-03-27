// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCarema.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameCarema::AGameCarema()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

	DestroyArea = CreateDefaultSubobject<UBoxComponent>(TEXT("DestoryArea"));
	DestroyArea->SetupAttachment(RootComponent);
	
}

void AGameCarema::MoveCamera()
{
	FVector TargetPos = FVector(GetActorLocation().X, GetActorLocation().Y, Muffin->GetActorLocation().Z);
	SetActorLocation(TargetPos);
}

// Called when the game starts or when spawned
void AGameCarema::BeginPlay()
{
	Super::BeginPlay();

	Muffin = Cast<AMuffin>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->SetViewTargetWithBlend(this, 0); //获取摄像机
}

// Called every frame
void AGameCarema::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCamera();
}

void AGameCarema::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	Cloud = Cast<ACloud>(OtherActor);
	if (Cloud)
	{
		Cloud->Destroy();
	}
}