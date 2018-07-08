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
		cout<<"Uso: ./a.out <arquivo entrada> <arquivo saida> <largura(opcional)> <altura(opcional)>"<<endl;
		exit(1);
	}

	const char* fileName = argv[1];
	const char* imageName = argv[2];

	// recebe entrada
	FILE* f = fopen(fileName, "r");	
	float x, y, z;
	float af;
	int aux;

	vector<Light> lights;
	vector<Pigm> pigms;
	vector<Material> materials;
	vector<Object> objects;

	// recebe coordenadas da camera
	fscanf(f, "%f %f %f\n", &x, &y, &z);
	Vec pos(x, y, z);
	fscanf(f, "%f %f %f\n", &x, &y, &z);
	Vec dir(x, y, z);
	fscanf(f, "%f %f %f\n", &x, &y, &z);
	Vec up(x, y, z);
	fscanf(f, "%f\n", &af);
	Camera camera(pos, dir, up, af);

	// declara lista de luzes
	fscanf(f, "%i\n", aux);
	for(int i = 0; i < aux; i++)
	{
		fscanf(f, "%f %f %f", &x, &y, &z);
		pos = Vec(x, y, z);
		fscanf(f, "%f %f %f", &x, &y, &z);
		dir = Vec(x, y, z);
		fscanf(f, "%f %f %f\n", &x, &y, &z);
		lights.push_back(Light(pos, dir, x, y, z));
	}

	// recebe pigmentos
	fscanf(f, "%i\n", aux);
	for(int i = 0; i < aux; i++)
	{
		string type;
		fscanf(f, "%s", type);
		pigms.push_back(Pigm(type));
		if(type == "solid")
		{
			fscanf(f, "%f %f %f\n", &x, &y, &z);
			pigms[i].color1 = Vec(x, y, z);
		}
		else if(type == "checker")
		{
			fscanf(f, "%f %f %f", &x, &y, &z);
			pigms[i].color1 = Vec(x, y, z);
			fscanf(f, "%f %f %f", &x, &y, &z);
			pigms[i].color2 = Vec(x, y, z);
			fscanf(f, "%i\n", &pigms[i].squareSide);
		}
		else if(type == "texmap")
		{
			string imageName;
			fscanf(f, "%s\n", imageName);
			pigms[i].image = fopen(imageName.c_str(), "r");
		}
	}

	// recebe acabamentos
	fscanf(f, "%i\n", aux);
	for(int i = 0; i < aux; i++)
	{
		float a, d, s, se, kr, kt, ior;
		fscanf(f, "%f %f %f %f %f %f %f\n", &a, &d, &s, &se, &kr, &kt, &ior);
		materials.push_back(Material(a, d, s, se, kr, kt, ior));
	}

	// declara lista de objetos
	fscanf(f, "%i\n", aux);
	for(int i = 0; i < aux; i++)
	{
		string type;
		int p, m;
		fscanf(f, "%i %i %s", &p, &m, type);
		if(type == "sphere")
		{
			fscanf(f, "%f %f %f %f\n", &x, &y, &z, &af);
			objects.push_back(Sphere(p, m, Vec(x, y, z), af));
		}
		else if(type == "polyhedron")
		{
		}
	}


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
			// desenha cor no pixel do arquivo de saida
		}
	}
}
