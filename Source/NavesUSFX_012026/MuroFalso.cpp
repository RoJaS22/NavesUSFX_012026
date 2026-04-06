// Fill out your copyright notice in the Description page of Project Settings.


#include "MuroFalso.h"

AMuroFalso::AMuroFalso()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialMuro(TEXT("Material'/Game/StarterContent/Materials/M_Concrete_Panels.M_Concrete_Panels'"));
	
	if (MaterialMuro.Succeeded()) {
		Malla->SetMaterial(0, MaterialMuro.Object);
	}

}

void AMuroFalso::BeginPlay()
{
	Super::BeginPlay();

	SetActorEnableCollision(false);
}

void AMuroFalso::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
