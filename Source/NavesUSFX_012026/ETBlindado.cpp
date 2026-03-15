// Fill out your copyright notice in the Description page of Project Settings.


#include "ETBlindado.h"

AETBlindado::AETBlindado()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBlindado(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile.M_Tech_Hex_Tile'"));

	if(MaterialBlindado.Succeeded())
	{
		MallaEnemigo->SetMaterial(0, MaterialBlindado.Object);
	}
}

void AETBlindado::BeginPlay()
{
	Super::BeginPlay();
}

void AETBlindado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
