// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoAcuatico.h"

AEnemigoAcuatico::AEnemigoAcuatico()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaEnemigoAcuatico(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	if(MallaEnemigoAcuatico.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaEnemigoAcuatico.Object);
	}
}

void AEnemigoAcuatico::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemigoAcuatico::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
