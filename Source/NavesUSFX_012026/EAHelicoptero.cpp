// Fill out your copyright notice in the Description page of Project Settings.


#include "EAHelicoptero.h"

AEAHelicoptero::AEAHelicoptero()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialHelicoptero(TEXT("Material'/Game/StarterContent/Materials/M_Water_Lake.M_Water_Lake'"));

	if(MaterialHelicoptero.Succeeded())
	{
		MallaEnemigo->SetMaterial(0, MaterialHelicoptero.Object);
	}
}

void AEAHelicoptero::BeginPlay()
{
	Super::BeginPlay();
}

void AEAHelicoptero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
