// Fill out your copyright notice in the Description page of Project Settings.


#include "ETTanque.h"

AETTanque::AETTanque()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialTanque(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Steel.M_Metal_Steel'"));
	
	if(MaterialTanque.Succeeded())
	{
		MallaEnemigo->SetMaterial(0, MaterialTanque.Object);
	}
}

void AETTanque::BeginPlay()
{
	Super::BeginPlay();
}

void AETTanque::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
