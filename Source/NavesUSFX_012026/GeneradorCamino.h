// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Bloque.h"
#include "MuroFalso.h"
#include "MuroMagico.h"
#include "MuroMovedizo.h"
#include "GeneradorCamino.generated.h"

/**
 * 
 */
UCLASS()
class NAVESUSFX_012026_API UGeneradorCamino : public UObject
{
	GENERATED_BODY()

public:
	UGeneradorCamino();

	void ConstruirCamino(UWorld* World);


	TArray<ABloque*> ContenedorMurosCuadrante1;
	TArray<ABloque*> ContenedorMurosCuadrante2;
	TArray<ABloque*> ContenedorMurosCuadrante3;
	TArray<ABloque*> ContenedorMurosCuadrante4;

private:
	TArray<ABloque*> ContenedorMuros;

	void GenerarMapaMuros(UWorld* World);
	
	
};
