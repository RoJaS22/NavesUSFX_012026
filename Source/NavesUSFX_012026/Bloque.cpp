// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloque.h"

// Sets default values
ABloque::ABloque()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
	RootComponent = Malla;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaBloque(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if(MallaBloque.Succeeded())
	{
		Malla->SetStaticMesh(MallaBloque.Object);
	}

}

// Called when the game starts or when spawned
void ABloque::BeginPlay()
{
	Super::BeginPlay();

	if (Malla)
	{
		Malla->SetRelativeScale3D(FVector(2.0f, 4.0f, 2.0f));
	}
	
}

// Called every frame
void ABloque::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

