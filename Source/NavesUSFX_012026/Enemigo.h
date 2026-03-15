// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemigo.generated.h"

class UStaticMeshComponent;

UCLASS()
class NAVESUSFX_012026_API AEnemigo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemigo();

	UStaticMeshComponent* MallaEnemigo;

	float VelocidadMovimiento = 200.0f;

	FVector WorldLimitesMin = FVector(-1800, -1800, 0);
	FVector WorldLimitesMax = FVector(1800, 1800, 0);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GenerarPuntosRuta();

	virtual void MoverEnemigo(float DeltaTime);

	TArray<FVector> PuntosRuta;

	int32 IndicePuntoRutaActual = 0;
	FVector PosicionInicial;
	float Tolerancia = 50.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
