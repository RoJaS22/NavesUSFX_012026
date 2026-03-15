// Fill out your copyright notice in the Description page of Project Settings.


#include "EADron.h"

AEADron::AEADron()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialDron(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Walnut.M_Wood_Walnut'"));

	if(MaterialDron.Succeeded())
	{
		MallaEnemigo->SetMaterial(0, MaterialDron.Object);
	}
}

void AEADron::BeginPlay()
{
	Super::BeginPlay();
}

void AEADron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
