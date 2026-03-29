#pragma once

#include "CoreMinimal.h"

template<class T>
class Nodo {
public:
	T Dato;
	Nodo<T>* Siguiente;

	Nodo(T Valor){
		Dato = Valor;
		Siguiente = nullptr;
	}

};

template<class T>
class Lista {
private:
	Nodo<T>* Cabeza;
	int32 CantidadElementos;

public:
	Lista() {
		Cabeza = nullptr;
		CantidadElementos = 0;
	}

    ~Lista()
    {
        Vaciar();
    }

    void Agregar(T NuevoDato)
    {
        Nodo<T>* NuevoNodo = new Nodo<T>(NuevoDato);

        if (Cabeza == nullptr)
        {
            Cabeza = NuevoNodo;
        }
        else
        {
            Nodo<T>* Auxiliar = Cabeza;
            while (Auxiliar->Siguiente != nullptr)
            {
                Auxiliar = Auxiliar->Siguiente;
            }
            Auxiliar->Siguiente = NuevoNodo;
        }
        CantidadElementos++;
    }

    int32 ObtenerCantidad()
    {
        return CantidadElementos;
    }

    T ObtenerPorIndice(int32 Indice)
    {
        if (Indice < 0 || Indice >= CantidadElementos || Cabeza == nullptr)
        {
            return T(); 
        }

        Nodo<T>* Auxiliar = Cabeza;
        for (int32 i = 0; i < Indice; i++)
        {
            Auxiliar = Auxiliar->Siguiente;
        }

        return Auxiliar->Dato;
    }

    void Vaciar()
    {
        Nodo<T>* Auxiliar = Cabeza;
        while (Auxiliar != nullptr)
        {
            Nodo<T>* NodoABorrar = Auxiliar;
            Auxiliar = Auxiliar->Siguiente;
            delete NodoABorrar; // Liberamos la RAM
        }
        Cabeza = nullptr;
        CantidadElementos = 0;
    }
};