// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo.h"

// Sets default values
AEnemigo::AEnemigo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEnemigo"));
	RootComponent = MallaEnemigo;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaEnemigoAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));

	if(MallaEnemigoAsset.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaEnemigoAsset.Object);
	}

    TiempoTransicionAcumulado = 0.0f;
}

// Called when the game starts or when spawned
void AEnemigo::BeginPlay()
{
	Super::BeginPlay();

    PosicionInicial = GetActorLocation();
    PuntosRuta.Empty();

    PuntosRuta.Add(PosicionInicial);

	GenerarPuntosRuta();

    IndicePuntoRutaActual = 1;
	
}

void AEnemigo::GenerarPuntosRuta()
{
	for (int32 i = 0; i < 10; i++)
	{
		float X = FMath::RandRange(WorldLimitesMin.X, WorldLimitesMax.X);
		float Y = FMath::RandRange(WorldLimitesMin.Y, WorldLimitesMax.Y);
		FVector NuevoPuntoRuta(X, Y, PosicionInicial.Z);  // Mantiene altura
		PuntosRuta.Add(NuevoPuntoRuta);
	}
}

/*void AEnemigo::MoverEnemigo(float DeltaTime)
{
    if (bEnFormacion)
    {
        FVector UbicacionActual = GetActorLocation();

        float Distancia = FVector::Dist(UbicacionActual, PosicionFormacion);

        if (Distancia <= Tolerancia)
        {
            // Waypoint alcanzado, siguiente
            return;
        }
        else
        {
            // Mover en línea recta
            FVector Direccion = (PosicionFormacion - UbicacionActual).GetSafeNormal();
            FVector NuevaUbicacion = UbicacionActual + (Direccion * VelocidadMovimiento * DeltaTime);
            SetActorLocation(NuevaUbicacion);
        }
    }

    else if (PuntosRuta.Num() > 1)
    {
        FVector UbicacionActual = GetActorLocation();
        FVector UbicacionDestino = PuntosRuta[IndicePuntoRutaActual];

        float Distancia = FVector::Dist(UbicacionActual, UbicacionDestino);

        if (Distancia <= Tolerancia)
        {
            IndicePuntoRutaActual = (IndicePuntoRutaActual + 1) % PuntosRuta.Num();
        }
        else
        {
            // Mover en línea recta
            FVector Direccion = (UbicacionDestino - UbicacionActual).GetSafeNormal();
            FVector NuevaUbicacion = UbicacionActual + (Direccion * VelocidadMovimiento * DeltaTime);
            SetActorLocation(NuevaUbicacion);
        }
    }
}*/

void AEnemigo::MoverEnemigo(float DeltaTime)
{
    if (bEnFormacion)
    {
        TiempoTransicionAcumulado += DeltaTime;
        float VelocidadGiroGlobal = 45.0f;

        FVector RadioVector = PosicionFormacionOriginal - CentroFormacion;

        FVector PosicionRotada = CentroFormacion + RadioVector.RotateAngleAxis(VelocidadGiroGlobal * TiempoTransicionAcumulado, FVector::UpVector);

        float VelocidadCirculoPequeno = 5.0f; // Qué tan rápido hace el circulito
        float RadioCirculoPequeno = 120.0f;   // Qué tan ancho es el circulito

        // Usamos Seno y Coseno estándar para el círculo 2D en el suelo
        FVector MovimientoLocal = FVector(
            FMath::Cos(TiempoTransicionAcumulado * VelocidadCirculoPequeno) * RadioCirculoPequeno,
            FMath::Sin(TiempoTransicionAcumulado * VelocidadCirculoPequeno) * RadioCirculoPequeno,
            0.0f
        );

        FVector DestinoDinamico = PosicionRotada + MovimientoLocal;
        FVector PosicionActual = GetActorLocation();

        FVector NuevaPosicion = FMath::VInterpTo(PosicionActual, DestinoDinamico, DeltaTime, 2.0f);

        SetActorLocation(NuevaPosicion);

        // La nave mira hacia donde se está moviendo en ese instante
        FVector DireccionMirada = (NuevaPosicion - PosicionActual).GetSafeNormal();
        if (!DireccionMirada.IsNearlyZero())
        {
            // Usamos RInterpTo para que no gire el cuello de forma robótica
            FRotator NuevaRotacion = FMath::RInterpTo(GetActorRotation(), DireccionMirada.Rotation(), DeltaTime, 5.0f);
            SetActorRotation(NuevaRotacion);
        }

        return;
    }
    else if (PuntosRuta.Num() > 1)
    {
        FVector UbicacionActual = GetActorLocation();
        FVector UbicacionDestino = PuntosRuta[IndicePuntoRutaActual];

        float Distancia = FVector::Dist(UbicacionActual, UbicacionDestino);

        if (Distancia <= Tolerancia)
        {
            IndicePuntoRutaActual = (IndicePuntoRutaActual + 1) % PuntosRuta.Num();
        }
        else
        {
            // Mover en línea recta
            FVector Direccion = (UbicacionDestino - UbicacionActual).GetSafeNormal();
            FVector NuevaUbicacion = UbicacionActual + (Direccion * VelocidadMovimiento * DeltaTime);
            SetActorLocation(NuevaUbicacion);
        }
    }
}

// Called every frame
void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoverEnemigo(DeltaTime);

}

