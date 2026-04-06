// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoTerrestre.h"

AEnemigoTerrestre::AEnemigoTerrestre()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaEnemigoTerrestre(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));

	if(MallaEnemigoTerrestre.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaEnemigoTerrestre.Object);
	}
}

void AEnemigoTerrestre::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemigoTerrestre::MoverEnemigo(float DeltaTime)
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

            float Amplitud = 300.0f;
            float Frecuencia = 5.0f;
            // Calculamos la dirección hacia el objetivo
            FVector Direccion = (UbicacionDestino - UbicacionActual).GetSafeNormal();

            // Movimiento base hacia el destino
            FVector NuevaUbicacion = UbicacionActual + Direccion * VelocidadMovimiento * DeltaTime;
            float DesplazamientoLateral = Amplitud * FMath::Sin(TiempoAcumulado * Frecuencia);
            FVector VectorDerecha = FVector::CrossProduct(Direccion, FVector::UpVector);
            NuevaUbicacion += VectorDerecha * DesplazamientoLateral * DeltaTime;

            SetActorLocation(NuevaUbicacion);
        }
    }
}

void AEnemigoTerrestre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
