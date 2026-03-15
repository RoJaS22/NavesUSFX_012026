// Fill out your copyright notice in the Description page of Project Settings.


#include "ETSoldado.h"

AETSoldado::AETSoldado()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialSoldado(TEXT("Material'/Game/StarterContent/Materials/M_Concrete_Grime.M_Concrete_Grime'"));

	if(MaterialSoldado.Succeeded())
	{
		MallaEnemigo->SetMaterial(0, MaterialSoldado.Object);
	}
}

void AETSoldado::BeginPlay()
{
	Super::BeginPlay();
}

void AETSoldado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
