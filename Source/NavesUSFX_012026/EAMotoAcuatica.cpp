// Fill out your copyright notice in the Description page of Project Settings.


#include "EAMotoAcuatica.h"

AEAMotoAcuatica::AEAMotoAcuatica()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialMotoAcuatica(TEXT("Material'/Game/StarterContent/Materials/M_ColorGrid_LowSpec.M_ColorGrid_LowSpec'"));

	if(MaterialMotoAcuatica.Succeeded())
	{
		MallaEnemigo->SetMaterial(0, MaterialMotoAcuatica.Object);
	}
}

void AEAMotoAcuatica::BeginPlay()
{
	Super::BeginPlay();
}

void AEAMotoAcuatica::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
