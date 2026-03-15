// Fill out your copyright notice in the Description page of Project Settings.


#include "EABarco.h"

AEABarco::AEABarco()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBarco(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak'"));

	if(MaterialBarco.Succeeded())
	{
		MallaEnemigo->SetMaterial(0, MaterialBarco.Object);
	}	
}

void AEABarco::BeginPlay()
{
	Super::BeginPlay();
}

void AEABarco::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
