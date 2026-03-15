// Fill out your copyright notice in the Description page of Project Settings.


#include "ETCamion.h"

AETCamion::AETCamion()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCamion(TEXT("Material'/Game/StarterContent/Materials/M_Rock_Basalt.M_Rock_Basalt'"));

	if(MaterialCamion.Succeeded())
	{
		MallaEnemigo->SetMaterial(0, MaterialCamion.Object);
	}
}

void AETCamion::BeginPlay()
{
	Super::BeginPlay();
}

void AETCamion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
