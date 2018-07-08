#include <iostream>
#include <cstdlib>
#include "scene.h"
using namespace std;

int main(int argc, char **argv)
{
	int altura, largura;
	if(argc == 3)
	{
		altura = 600;
		largura = 800;
	}
	else if(argc == 5)
	{
		altura = atoi(argv[4]);
		largura = atoi(argv[3]);
	}
	else
	{
		cout<<"Uso: ./exec <arquivo entrada> <arquivo saida> <largura(opcional)> <altura(opcional)>";
		exit(1);
	}

	const char* fileName = argv[1];
	const char* imageName = argv[2];

	// recebe entrada
	// recebe coordenadas da camera
	// declara lista de luzes
	// recebe pigmentos
	// recebe acabamentos
	// declara lista de objetos

	// lanca um raio para cada pixel na tela
	for(int i = 0; i < largura; i++)
	{
		for(int j = 0; j < altura; j++)
		{
			// lanca o raio de visibilidade
			// pega o objeto mais proximo que o raio atinge
			// lanca o raio do objeto a cada fonte de luz
			// usa luz ambiente
			// se acerta um objeto, só luz ambiente
			// se nao, soma cor difusa (ponderado pelo coeficiente
			// se angulo da normal com direçao a luz < threshold, soma luz especular ponderada pelo coeficiente
			// se ha coeficiente de reflexao: lança mais raios recursivamente
		}
	}
}
