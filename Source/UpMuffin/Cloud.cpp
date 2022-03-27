// Fill out your copyright notice in the Description page of Project Settings.


#include "Cloud.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACloud::ACloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	Cloud = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cloud"));
	Cloud->SetupAttachment(RootComponent);

	ScoreTextComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreTextComp"));
	ScoreTextComp->SetupAttachment(RootComponent);

	RainComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RainComp"));
	RainComp->SetupAttachment(Cloud);

	RainSound = CreateDefaultSubobject<UAudioComponent>(TEXT("RainSound"));
	RainSound->SetupAttachment(Cloud);
}

// Called when the game starts or when spawned
void ACloud::BeginPlay()
{
	Super::BeginPlay();
	SetRandomMaterial();

	GameModeRef = Cast<AUpMuffinGameModeBase>(UGameplayStatics::GetGameMode(this));
}

void ACloud::SetRandomMaterial()
{
	MaterialInterface = Cloud->GetMaterial(0);
	MaterialInstance = Cloud->CreateDynamicMaterialInstance(0, MaterialInterface);
	int Index = FMath::RandRange(0,3);
	if (Textures[Index])
	{
		MaterialInstance->SetTextureParameterValue(FName(TEXT("Texture")), Textures[Index]);
		Cloud->SetMaterial(0, MaterialInstance);
	}
	if (Index == 0)
	{
		RainComp->SetVisibility(true);
		RainSound->Activate(true);
	}
}

void ACloud::DisplayScore()
{
	ScoreTextComp->SetText(FText::FromString(FString::FromInt(GameModeRef->GetScore())));
}

// Called every frame
void ACloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACloud::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	Muffin = Cast<AMuffin>(OtherActor);
	if (Muffin)
	{
		GameModeRef->CountScore();
		DisplayScore();
		UGameplayStatics::PlaySoundAtLocation(this, CollisionSoundCue, GetActorLocation());
		FadeOut();
		Muffin->JumpLooping();
	}
}

