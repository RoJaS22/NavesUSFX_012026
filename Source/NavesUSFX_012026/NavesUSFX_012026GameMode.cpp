// Copyright Epic Games, Inc. All Rights Reserved.

#include "NavesUSFX_012026GameMode.h"
#include "NavesUSFX_012026Pawn.h"
#include "Enemigo.h"

ANavesUSFX_012026GameMode::ANavesUSFX_012026GameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ANavesUSFX_012026Pawn::StaticClass();

}

void ANavesUSFX_012026GameMode::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (!World) return;

    FVector UbicacionSpawn(-600, -100, 160);  
    AEnemigo* Enemigo = World->SpawnActor<AEnemigo>(AEnemigo::StaticClass(), UbicacionSpawn, FRotator::ZeroRotator);

}

void ANavesUSFX_012026GameMode::Tick(float DeltaTime)
{
}

