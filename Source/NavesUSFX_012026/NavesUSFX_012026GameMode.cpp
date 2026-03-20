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
#include "Kismet/GameplayStatics.h"

ANavesUSFX_012026GameMode::ANavesUSFX_012026GameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ANavesUSFX_012026Pawn::StaticClass();

}

void ANavesUSFX_012026GameMode::BeginPlay()
{
    Super::BeginPlay();

    GenerarNaves();

    // 2. Cronómetro 1: A los 5 segundos, se llama a la formación
    GetWorld()->GetTimerManager().SetTimer(TimerFormacion, this, &ANavesUSFX_012026GameMode::OrdenarFormacion, IntervaloFormacion, false);

    /*
    SpawnearCuadrilla1();

	// Configuración del temporizador para desaparecer la primera cuadrilla
    GetWorld()->GetTimerManager().SetTimer(
        TimerDesaparicion,
        this,
        &ANavesUSFX_012026GameMode::DesaparecerCuadrilla1,
        10.0f, // Tiempo en segundos antes de desaparecer
        false  // false significa que solo ocurre una vez (no se repite en bucle)
    );
    */

}

void ANavesUSFX_012026GameMode::GenerarNaves()
{
    UWorld* Mundo = GetWorld();
    if (!Mundo) return;

    for (int32 i = 0; i < 20; i++)
    {
        FVector PosicionSpawn = FVector(600.0f, i*50.0f, 160.0f);
        FRotator RotacionSpawn = FRotator::ZeroRotator;

        // Spawneamos la nave directamente
        AEnemigo* NuevaNave = Mundo->SpawnActor<AEnemigo>(PosicionSpawn, RotacionSpawn);

        // Si la nave se materializó con éxito en el mundo, la metemos al contenedor
        if (NuevaNave)
        {
            ContenedorNaves.Add(NuevaNave);
        }
    }
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

void ANavesUSFX_012026GameMode::OrdenarFormacion()
{
    // Buscamos al Pawn del jugador en el mundo
    APawn* Jugador = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!Jugador) return;

    FVector UbicacionJugador = Jugador->GetActorLocation();

    // Obtenemos los vectores direccionales directamente del jugador
    FVector DireccionFrente = Jugador->GetActorForwardVector();
    FVector DireccionDerecha = Jugador->GetActorRightVector();

    // Posición base
    FVector PosicionBase = UbicacionJugador + (DireccionFrente * 200.0f);

    // Damos la orden a las naves del contenedor
    for (int32 i = 0; i < ContenedorNaves.Num(); i++)
    {
        if (AEnemigo* Nave = ContenedorNaves[i])
        {
            // 1. ACTIVAMOS EL ESTADO (¡y lo dejamos encendido!)
            Nave->bEnFormacion = true;

            // 2. Calculamos la posición en la fila usando el Vector Derecho del jugador
            // Restamos la mitad del total a 'i' para que la formación quede centrada
            float Desplazamiento = (i - (ContenedorNaves.Num() / 2)) * EspaciadoVertical;

            FVector PosicionFinal = PosicionBase + (DireccionDerecha * Desplazamiento);

            // Le pasamos la coordenada final a la nave
            Nave->PosicionFormacion = PosicionFinal;

            // Hacemos que miren en la misma dirección que el jugador
            Nave->SetActorRotation(Jugador->GetActorRotation());

        }
    }

    // Cronómetro 2: llamamos a la función que apaga la bandera
    GetWorld()->GetTimerManager().SetTimer(TimerRetorno, this, &ANavesUSFX_012026GameMode::OrdenarMovimientoLibre, 20.0f, false);
}

void ANavesUSFX_012026GameMode::OrdenarMovimientoLibre()
{
    // Recorremos el contenedor y les apagamos el estado de formación
    for (int32 i = 0; i < ContenedorNaves.Num(); i++)
    {
        if (AEnemigo* Nave = ContenedorNaves[i])
        {
            Nave->bEnFormacion = false;
        }
    }
}

void ANavesUSFX_012026GameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
	// Aquí podríamos agregar lógica adicional que queramos que se ejecute cada frame
}

