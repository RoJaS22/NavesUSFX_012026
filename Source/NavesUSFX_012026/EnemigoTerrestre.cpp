// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoTerrestre.h"

AEnemigoTerrestre::AEnemigoTerrestre()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaEnemigoTerrestre(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));

	if(MallaEnemigoTerrestre.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaEnemigoTerrestre.Object);
	}
}

void AEnemigoTerrestre::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemigoTerrestre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
