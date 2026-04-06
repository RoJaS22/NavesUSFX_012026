// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bloque.h"
#include "MuroMagico.generated.h"

/**
 * 
 */
UCLASS()
class NAVESUSFX_012026_API AMuroMagico : public ABloque
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMuroMagico();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Desaparecer();
	void Reaparecer();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle TimerHandle_Desaparecer;
	FTimerHandle TimerHandle_Reaparecer;
	
};
