// Fill out your copyright notice in the Description page of Project Settings.


#include "MuroMovedizo.h"

AMuroMovedizo::AMuroMovedizo()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMuroMovedizo::BeginPlay()
{
	Super::BeginPlay();

    UbicacionInicial = GetActorLocation();

}

void AMuroMovedizo::MoverMuro(float DeltaTime)
{
    FVector UbicacionActual = GetActorLocation();

    FVector Direccion = GetActorForwardVector();

    if (!bMoverAdelante)
    {
        Direccion *= -1.0f;
    }

    FVector NuevaUbicacion = UbicacionActual + (Direccion * Velocidad * DeltaTime);
    SetActorLocation(NuevaUbicacion);

    float DistanciaViajada = FVector::Dist(UbicacionInicial, NuevaUbicacion);

    if (DistanciaViajada >= Distancia)
    {
        // Invertimos la dirección
        bMoverAdelante = !bMoverAdelante;

        UbicacionInicial = UbicacionActual;
    }
}
	

void AMuroMovedizo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoverMuro(DeltaTime);
}
