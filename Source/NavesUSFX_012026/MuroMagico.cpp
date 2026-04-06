// Fill out your copyright notice in the Description page of Project Settings.


#include "MuroMagico.h"
#include "TimerManager.h"

AMuroMagico::AMuroMagico()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMuroMagico::BeginPlay()
{
	Super::BeginPlay();

	Reaparecer();
    
}

void AMuroMagico::Desaparecer()
{
    SetActorHiddenInGame(true);

    SetActorEnableCollision(false);

    GetWorldTimerManager().SetTimer(
        TimerHandle_Reaparecer,
        this,
        &AMuroMagico::Reaparecer,
        5.0f,
        false
    );
}

void AMuroMagico::Reaparecer()
{
    SetActorHiddenInGame(false);

    SetActorEnableCollision(true);


    GetWorldTimerManager().SetTimer(
        TimerHandle_Desaparecer,
        this,
        &AMuroMagico::Desaparecer,
        5.0f,
        false
	);
}

void AMuroMagico::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
