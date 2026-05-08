// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Lista.h"
#include "Bloque.h"
#include "GeneradorCamino.h"
#include "NavesUSFX_012026GameMode.generated.h"

class AEnemigo;
class APawn;
class ABloque;

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

	UGeneradorCamino* GestorDelNivel;

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

	Lista<ABloque*> ListaBloques;
	void GenerarCamino();

	TArray<ABloque*> ContenedorMurosCuadrante1;
	TArray<ABloque*> ContenedorMurosCuadrante2;
	TArray<ABloque*> ContenedorMurosCuadrante3;
	TArray<ABloque*> ContenedorMurosCuadrante4;

	

	void GenerarMapaMuros();

	void MoverCuadrante(TArray<ABloque*> Contenedor);

	void MoverCuadrante2(TArray<ABloque*> Contenedor);

	TArray<AActor*> Contenedor9;

public:
	virtual void Tick(float DeltaTime) override;
};



