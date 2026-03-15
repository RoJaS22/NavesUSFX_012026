// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemigoAcuatico.h"
#include "EAMotoAcuatica.generated.h"

/**
 * 
 */
UCLASS()
class NAVESUSFX_012026_API AEAMotoAcuatica : public AEnemigoAcuatico
{
	GENERATED_BODY()

public:
	AEAMotoAcuatica();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
};
