// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NavesUSFX_012026GameMode.generated.h"

class AEnemigo;

UCLASS(MinimalAPI)
class ANavesUSFX_012026GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANavesUSFX_012026GameMode();

protected:
	virtual void BeginPlay() override;

	// 1. Arreglos para almacenar a los miembros de cada cuadrilla
	TArray<AEnemigo*> Cuadrilla1;
	TArray<AEnemigo*> Cuadrilla2;

	// 2. El objeto temporizador exigido para controlar la desaparición
	FTimerHandle TimerDesaparicion;

	// 3. Funciones de control de oleadas
	void SpawnearCuadrilla1();
	void DesaparecerCuadrilla1();
	void SpawnearCuadrilla2();

public:
	virtual void Tick(float DeltaTime) override;
};



