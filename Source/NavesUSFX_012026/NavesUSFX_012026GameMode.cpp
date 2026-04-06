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
#include "Bloque.h"
#include "MuroFalso.h"
#include "MuroMovedizo.h"
#include "MuroMagico.h"
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
    
    GenerarMapaMuros();


	// Generar el camino para el laboratorio 4
    //GenerarCamino();


	// Spawneo de las naves enemigas Laboratorio 3
    /*
    GenerarNaves();

    // Cronómetro 1: A los 5 segundos, se llama a la formación
    GetWorld()->GetTimerManager().SetTimer(TimerFormacion, this, &ANavesUSFX_012026GameMode::OrdenarFormacion, IntervaloFormacion, false);
    */


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

void ANavesUSFX_012026GameMode::GenerarCamino()
{
	UWorld* World = GetWorld();
	if (!World) return;

	const int32 Filas = 7;
	const int32 Columnas = 6;
	const float Espaciado = 600.0f;

    float OffsetX = (Filas * Espaciado) / 2.0f;
    float OffsetY = (Columnas * Espaciado) / 2.0f;

    for (int32 i = 0; i < Filas; i++) {
        for(int32 j = 0; j < Columnas; j++) {
            FVector PosicionSpawn = FVector(i * Espaciado - OffsetX + 350, j * Espaciado - OffsetY + 300, 160.0f);
            FRotator RotacionSpawn = FRotator::ZeroRotator;
            ABloque* NuevoBloque = World->SpawnActor<ABloque>(PosicionSpawn, RotacionSpawn);
            if (NuevoBloque) {
                ListaBloques.Agregar(NuevoBloque);
            }
		}
    }
}

void ANavesUSFX_012026GameMode::GenerarMapaMuros()
{
    UWorld* World = GetWorld();
    if (!World) return;

    //MAPA 
    TArray<int32> PlanoNivel = {
		2, 2, 1, 0, 1, 1, 0, 1,
        0, 0, 3, 0, 3, 2, 1, 0,
        0, 1, 2, 0, 1, 3, 2, 0,
        2, 0, 6, 0, 1, 4, 1, 0,
        0, 3, 2, 2, 2, 1, 3, 0,
        2, 0, 3, 5, 3, 0, 1, 0,
        0, 3, 1, 0, 1, 2, 1, 1,
        2, 0, 0, 0, 0, 0, 0, 0
    };

    const int32 Filas = 8;
    const int32 Columnas = 8;
    const float AnchoMuro = 400.0f;

    for (int32 y = 0; y < Filas; y++)
    {
        for (int32 x = 0; x < Columnas; x++)
        {
            int32 Indice = x + (y * Columnas);
            int32 TipoDeCelda = PlanoNivel[Indice];

            if (TipoDeCelda == 0) continue;

            FVector PosicionMuro = FVector(x * AnchoMuro - 1000, y * AnchoMuro - 1500, 160.0f);
            FRotator RotacionMuro = FRotator::ZeroRotator;

			FVector PosicionAereo = FVector(1.0f, 1.0f, 2.5f);
			FRotator RotacionAdicional = FRotator(0.0f, 90.0f, 0.0f);

            AActor* NuevoMuroSpawneado = nullptr;

            switch (TipoDeCelda)
            {
                case 1:
                    NuevoMuroSpawneado = World->SpawnActor<AMuroMagico>(AMuroMagico::StaticClass(), PosicionMuro, RotacionMuro);
					break;
				case 2: 
                    NuevoMuroSpawneado = World->SpawnActor<AMuroFalso>(AMuroFalso::StaticClass(), PosicionMuro, RotacionMuro);
					break;
				case 3: 
                    NuevoMuroSpawneado = World->SpawnActor<AMuroMovedizo>(AMuroMovedizo::StaticClass(), PosicionMuro, RotacionMuro);
					break;
				case 4:
                    NuevoMuroSpawneado = World->SpawnActor<AEnemigo>(AEnemigo::StaticClass(), PosicionMuro, RotacionMuro);
                    break;
				case 5:
                    NuevoMuroSpawneado = World->SpawnActor<AEnemigoTerrestre>(AEnemigoTerrestre::StaticClass(), PosicionMuro, RotacionMuro);
					break;
				case 6:
					NuevoMuroSpawneado = World->SpawnActor<AEnemigoAereo>(AEnemigoAereo::StaticClass(), PosicionMuro*PosicionAereo, RotacionMuro);
					break;
                default:
                    break;
            }
            
            // 4. ALMACENAMIENTO
            if (NuevoMuroSpawneado)
            {
                ContenedorMuros.Add(NuevoMuroSpawneado);
            }
        }
    }
}

void ANavesUSFX_012026GameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
	// Aquí podríamos agregar lógica adicional que queramos que se ejecute cada frame
}

