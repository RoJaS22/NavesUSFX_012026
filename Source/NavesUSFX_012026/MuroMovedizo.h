// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bloque.h"
#include "MuroMovedizo.generated.h"

/**
 * 
 */
UCLASS()
class NAVESUSFX_012026_API AMuroMovedizo : public ABloque
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMuroMovedizo();	

	float Velocidad = 200.0f;
	float Distancia = 400.0f;

	FVector UbicacionInicial;

	bool bMoverAdelante = true; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoverMuro(float DeltaTime);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
