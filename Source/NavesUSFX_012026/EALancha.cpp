// Fill out your copyright notice in the Description page of Project Settings.


#include "EALancha.h"

AEALancha::AEALancha()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialLancha(TEXT("Material'/Game/StarterContent/Materials/M_Ground_Moss.M_Ground_Moss'"));

	if(MaterialLancha.Succeeded())
	{
		MallaEnemigo->SetMaterial(0, MaterialLancha.Object);
	}
}

void AEALancha::BeginPlay()
{
	Super::BeginPlay();
}

void AEALancha::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
