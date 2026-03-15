// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoAereo.generated.h"

/**
 *
 */
UCLASS()
class NAVESUSFX_012026_API AEnemigoAereo : public AEnemigo
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemigoAereo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MoverEnemigo(float DeltaTime) override;

	float TiempoAcumulado;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
