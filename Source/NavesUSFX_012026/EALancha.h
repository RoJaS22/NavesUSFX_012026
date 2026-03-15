// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemigoAcuatico.h"
#include "EALancha.generated.h"

/**
 * 
 */
UCLASS()
class NAVESUSFX_012026_API AEALancha : public AEnemigoAcuatico
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AEALancha();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
