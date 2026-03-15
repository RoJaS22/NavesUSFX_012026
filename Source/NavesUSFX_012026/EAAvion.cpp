// Fill out your copyright notice in the Description page of Project Settings.


#include "EAAvion.h"

AEAAvion::AEAAvion()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAvion(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Panel.M_Tech_Panel'"));

	if(MaterialAvion.Succeeded())
	{
		MallaEnemigo->SetMaterial(0, MaterialAvion.Object);
	}
}

void AEAAvion::BeginPlay()
{
	Super::BeginPlay();
}

void AEAAvion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
