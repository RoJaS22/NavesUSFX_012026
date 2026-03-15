// Copyright Epic Games, Inc. All Rights Reserved.

#include "NavesUSFX_012026GameMode.h"
#include "NavesUSFX_012026Pawn.h"
#include "EnemigoAereo.h"
#include "EnemigoTerrestre.h" 
#include "EnemigoAcuatico.h"
#include "EAAvion.h"
#include "EABarco.h"
#include "EADron.h"
#include "EAHelicoptero.h"
#include "EALancha.h"
#include "EAMotoAcuatica.h"
#include "ETBlindado.h"
#include "ETCamion.h"
#include "ETTanque.h"
#include "ETSoldado.h"
#include "Engine/World.h"
#include "TimerManager.h"

ANavesUSFX_012026GameMode::ANavesUSFX_012026GameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ANavesUSFX_012026Pawn::StaticClass();

}

void ANavesUSFX_012026GameMode::BeginPlay()
{
    Super::BeginPlay();

    SpawnearCuadrilla1();

	// Configuración del temporizador para desaparecer la primera cuadrilla
    GetWorld()->GetTimerManager().SetTimer(
        TimerDesaparicion,
        this,
        &ANavesUSFX_012026GameMode::DesaparecerCuadrilla1,
        10.0f, // Tiempo en segundos antes de desaparecer
        false  // false significa que solo ocurre una vez (no se repite en bucle)
    );

}

void ANavesUSFX_012026GameMode::SpawnearCuadrilla1()
{
    UWorld* Mundo = GetWorld();
    if (!Mundo) return;

    // Formación predefinida
    TArray<UClass*> FormacionCuadrilla;
    FormacionCuadrilla.Add(AETSoldado::StaticClass());
    FormacionCuadrilla.Add(AEAHelicoptero::StaticClass());
    FormacionCuadrilla.Add(AEALancha::StaticClass());
    FormacionCuadrilla.Add(AEAAvion::StaticClass());
    FormacionCuadrilla.Add(AETTanque::StaticClass());

    // Recorremos la formación
    for (int32 i = 0; i < FormacionCuadrilla.Num(); i++)
    {
        UClass* ClaseASpawnear = FormacionCuadrilla[i];

        float Z = 160.0f;

        if (ClaseASpawnear->IsChildOf(AEnemigoAereo::StaticClass()))
        {
            Z = 400.0f;
        }

        if (ClaseASpawnear->IsChildOf(AEnemigoAcuatico::StaticClass()))
        {
            Z = 110.0f;
        }

        FVector PosicionSpawn = FVector(300.0f, i * 100.0f, Z);
        FRotator RotacionSpawn = FRotator::ZeroRotator;

        // Spawn de enemigos
        AActor* ActorSpawneado = Mundo->SpawnActor(ClaseASpawnear, &PosicionSpawn, &RotacionSpawn);
        AEnemigo* NuevoEnemigo = Cast<AEnemigo>(ActorSpawneado);

        if (NuevoEnemigo)
        {
            Cuadrilla1.Add(NuevoEnemigo);
        }
    }
}

void ANavesUSFX_012026GameMode::DesaparecerCuadrilla1()
{
	// Destruccion de enemigos de la primera cuadrilla
    for (AEnemigo* Enemigo : Cuadrilla1)
    {
        if (Enemigo)
        {
            Enemigo->Destroy(); // Esto lo borra físicamente del escenario
        }
    }

    SpawnearCuadrilla2();
}

void ANavesUSFX_012026GameMode::SpawnearCuadrilla2()
{
    UWorld* Mundo = GetWorld();
    if (!Mundo) return;

    // Formación predefinida
    TArray<UClass*> FormacionCuadrilla;
    FormacionCuadrilla.Add(AEAMotoAcuatica::StaticClass());
    FormacionCuadrilla.Add(AETBlindado::StaticClass());
    FormacionCuadrilla.Add(AEADron::StaticClass());
    FormacionCuadrilla.Add(AETCamion::StaticClass());
    FormacionCuadrilla.Add(AEABarco::StaticClass());

    // Recorremos la formación
    for (int32 i = 0; i < FormacionCuadrilla.Num(); i++)
    {
        UClass* ClaseASpawnear = FormacionCuadrilla[i];

        float Z = 160.0f;

        if (ClaseASpawnear->IsChildOf(AEnemigoAereo::StaticClass()))
        {
            Z = 400.0f;
        }

        if (ClaseASpawnear->IsChildOf(AEnemigoAcuatico::StaticClass()))
        {
            Z = 110.0f;
        }

        FVector PosicionSpawn = FVector(300.0f, i * 100.0f, Z);
        FRotator RotacionSpawn = FRotator::ZeroRotator;

        // Spawn de enemigos
        AActor* ActorSpawneado = Mundo->SpawnActor(ClaseASpawnear, &PosicionSpawn, &RotacionSpawn);
        AEnemigo* NuevoEnemigo = Cast<AEnemigo>(ActorSpawneado);

        if (NuevoEnemigo)
        {
            Cuadrilla1.Add(NuevoEnemigo);
        }
    }
}

void ANavesUSFX_012026GameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
	// Aquí podríamos agregar lógica adicional que queramos que se ejecute cada frame
}

