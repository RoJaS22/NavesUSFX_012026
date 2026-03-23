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

    // Cronómetro 1: A los 5 segundos, se llama a la formación
   GetWorld()->GetTimerManager().SetTimer(TimerFormacion, this, &ANavesUSFX_012026GameMode::OrdenarFormacion, IntervaloFormacion, false);



    // Configuracion del spawn de las cuadrillas del laboratorio 2
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
    APawn* Jugador = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!Jugador) return;

    FVector UbicacionJugador = Jugador->GetActorLocation();

    // APLANAMOS LOS VECTORES DEL JUGADOR PARA QUE EL PENTÁGONO NO SE INCLINE
    FVector FrentePlano = Jugador->GetActorForwardVector();
    FrentePlano.Normalize();

    FVector DerechaPlano = Jugador->GetActorRightVector();
    DerechaPlano.Normalize();

    // GEOMETRÍA DEL PENTÁGONO HORIZONTAL 
    const int32 NumVertices = 5;
    const int32 TotalNaves = ContenedorNaves.Num();
    const int32 NavesPorLado = TotalNaves / NumVertices;
    const float RadioPentagono = 800.0f;

    // CALCULAMOS EL CENTRO A RAS DE PISO
    FVector CentroPentagono = UbicacionJugador + (FrentePlano * 1500.0f);
    CentroPentagono.Z = 200.0f;

    TArray<FVector> Vertices;

    for (int32 i = 0; i < NumVertices; i++)
    {
        // Ángulo de cada punta (72 grados)
        float AnguloBase = FMath::DegreesToRadians(72.0f * i);

        // Usamos Frente y Derecha para dibujar el círculo acostado en el piso (X e Y)
        FVector Vertice = CentroPentagono +
            (FrentePlano * RadioPentagono * FMath::Cos(AnguloBase)) +
            (DerechaPlano * RadioPentagono * FMath::Sin(AnguloBase));

        Vertices.Add(Vertice);
    }

    // --- DISTRIBUCIÓN DE LAS NAVES --- 
    for (int32 i = 0; i < TotalNaves; i++)
    {
        if (AEnemigo* Nave = ContenedorNaves[i])
        {
            Nave->TiempoTransicionAcumulado = 0.0f;
            Nave->bEnFormacion = true;

            int32 IndiceVerticeActual = i / NavesPorLado;
            int32 IndiceSiguienteVertice = (IndiceVerticeActual + 1) % NumVertices;

            FVector Start = Vertices[IndiceVerticeActual];
            FVector End = Vertices[IndiceSiguienteVertice];

            float AlphaSegmento = (i % NavesPorLado) / (float)NavesPorLado;

            // Calculamos su posición exacta en la línea que une los dos vértices
            Nave->PosicionFormacion = FMath::Lerp(Start, End, AlphaSegmento);
            Nave->PosicionFormacionOriginal = Nave->PosicionFormacion;
            Nave->CentroFormacion = CentroPentagono;
        }
    }
    GetWorld()->GetTimerManager().SetTimer(TimerRetorno, this, &ANavesUSFX_012026GameMode::OrdenarMovimientoLibre, 5.0f, false);
}

void ANavesUSFX_012026GameMode::OrdenarMovimientoLibre()
{
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

