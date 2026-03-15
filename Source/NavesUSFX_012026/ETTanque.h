// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemigoTerrestre.h"
#include "ETTanque.generated.h"

/**
 * 
 */
UCLASS()
class NAVESUSFX_012026_API AETTanque : public AEnemigoTerrestre
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AETTanque();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
