// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NavesUSFX_012026GameMode.generated.h"

class AEnemigo;
class APawn;

UCLASS(MinimalAPI)
class ANavesUSFX_012026GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANavesUSFX_012026GameMode();

protected:
	virtual void BeginPlay() override;

	// Contenedor para almacenar a los enemigos 
	TArray<AEnemigo*> ContenedorNaves;

	void GenerarNaves();

	TArray<AEnemigo*> Cuadrilla1;
	TArray<AEnemigo*> Cuadrilla2;

	FTimerHandle TimerDesaparicion;

	void SpawnearCuadrilla1();
	void DesaparecerCuadrilla1();
	void SpawnearCuadrilla2();

	FTimerHandle TimerFormacion;
	FTimerHandle TimerRetorno;

	float IntervaloFormacion = 5.0f;
	float EspaciadoVertical = 100.0f;

	void OrdenarFormacion();
	void OrdenarMovimientoLibre();

public:
	virtual void Tick(float DeltaTime) override;
};



