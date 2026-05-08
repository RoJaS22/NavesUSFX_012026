// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneradorCamino.h"

UGeneradorCamino::UGeneradorCamino()
{
}

void UGeneradorCamino::ConstruirCamino(UWorld* World)
{
    if (!World) return;

    GenerarMapaMuros(World);
}

void UGeneradorCamino::GenerarMapaMuros(UWorld* World)
{
  
    //MAPA 
    TArray<int32> PlanoNivel = {
        1, 1, 1, 1, 2, 2, 2, 2,
        1, 0, 0, 1, 2, 0, 0, 2,
        1, 0, 0, 1, 2, 0, 0, 2,
        1, 1, 1, 1, 2, 2, 2, 2,
        4, 4, 4, 4, 3, 3, 3, 3,
        4, 0, 0, 4, 3, 0, 0, 3,
        4, 0, 0, 4, 3, 0, 0, 3,
        4, 4, 4, 4, 3, 3, 3, 3
    };

    const int32 Filas = 8;
    const int32 Columnas = 8;
    const float AnchoMuro = 400.0f;

    for (int32 y = 0; y < Filas; y++)
    {
        for (int32 x = 0; x < Columnas; x++)
        {
            int32 Indice = x + (y * Columnas);
            int32 TipoDeCelda = PlanoNivel[Indice];

            if (TipoDeCelda == 0) continue;

            FVector PosicionMuro = FVector(x * AnchoMuro - 1000, y * AnchoMuro - 1500, 160.0f);
            FRotator RotacionMuro = FRotator::ZeroRotator;

            FVector PosicionAereo = FVector(1.0f, 1.0f, 2.5f);
            FRotator RotacionAdicional = FRotator(0.0f, 90.0f, 0.0f);

            ABloque* NuevoMuroSpawneado1 = nullptr;
            ABloque* NuevoMuroSpawneado2 = nullptr;
            ABloque* NuevoMuroSpawneado3 = nullptr;
            ABloque* NuevoMuroSpawneado4 = nullptr;

            switch (TipoDeCelda)
            {
            case 1:
                NuevoMuroSpawneado1 = World->SpawnActor<AMuroMagico>(AMuroMagico::StaticClass(), PosicionMuro, RotacionMuro);
                break;
            case 2:
                NuevoMuroSpawneado2 = World->SpawnActor<AMuroFalso>(AMuroFalso::StaticClass(), PosicionMuro, RotacionMuro);
                break;
            case 3:
                NuevoMuroSpawneado3 = World->SpawnActor<AMuroMovedizo>(AMuroMovedizo::StaticClass(), PosicionMuro, RotacionMuro);
                break;
            case 4:
                NuevoMuroSpawneado4 = World->SpawnActor<ABloque>(ABloque::StaticClass(), PosicionMuro, RotacionMuro);
                break;
            default:
                break;
            }

            // 4. ALMACENAMIENTO
            if (NuevoMuroSpawneado1)
            {
                ContenedorMurosCuadrante1.Add(NuevoMuroSpawneado1);
            }
            else if (NuevoMuroSpawneado2)
            {
                ContenedorMurosCuadrante2.Add(NuevoMuroSpawneado2);
            }
            else if (NuevoMuroSpawneado3)
            {
                ContenedorMurosCuadrante3.Add(NuevoMuroSpawneado3);
            }
            else if (NuevoMuroSpawneado4)
            {
                ContenedorMurosCuadrante4.Add(NuevoMuroSpawneado4);
            }
        }
    }
}
