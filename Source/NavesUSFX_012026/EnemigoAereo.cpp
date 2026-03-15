// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoAereo.h"

// Sets default values
AEnemigoAereo::AEnemigoAereo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TiempoAcumulado = 0.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaEnemigoAereo(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid'"));

	if (MallaEnemigoAereo.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaEnemigoAereo.Object);
	}

}

// Called when the game starts or when spawned
void AEnemigoAereo::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemigoAereo::MoverEnemigo(float DeltaTime)
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
			TiempoAcumulado += DeltaTime; 

			float Amplitud = 35.0f;   // Qué tan alto/bajo llega la oscilación
			float Frecuencia = 2.0f;  // Qué tan rápido sube y baja

			// Formula del coseno para la oscilación vertical
			float DeltaZ = Amplitud * Frecuencia * FMath::Cos(TiempoAcumulado * Frecuencia) * DeltaTime;

			FVector Direccion = (UbicacionDestino - UbicacionActual).GetSafeNormal();
			FVector NuevaUbicacion = UbicacionActual + Direccion * VelocidadMovimiento * DeltaTime;
			NuevaUbicacion.Z += DeltaZ; // Agregamos la oscilación vertical
			SetActorLocation(NuevaUbicacion);
		}
	}
}

// Called every frame
void AEnemigoAereo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

