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

void AEnemigo::MoverEnemigo(float DeltaTime)
{
    if (PuntosRuta.Num() > 1)
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

