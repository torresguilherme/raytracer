#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>

struct Vec
{
	float x;
	float y;
	float z;

	Vec();
	Vec(float, float, float);

	float dot(Vec other);
	float magnitude();
	Vec normalize();
	Vec operator+(Vec other);
	Vec operator-(Vec other);
	Vec operator*(Vec other);
	Vec operator/(Vec other);
};

struct Ray
{
	Vec origin;
	Vec dir;

	Ray(Vec, Vec);
};

struct Camera
{
	Vec pos;
	Vec aim;
	Vec up;
	float abertura;

	Camera(Vec, Vec, Vec, float);
};

struct Light
{
	Vec pos;
	Vec color;
	float constAten;
	float propAten;
	float squarePropAten;

	Light(Vec, Vec, float, float, float);
};

struct Pigm
{
	std::string type;
	Vec color1;
	Vec color2;
	float squareSide;
	FILE* image;

	Pigm(std::string);
};

struct Material
{
	float ambient;
	float diffuse;
	float specular;
	float specularExp;
	float reflection;
	float transmission;
	float ior;

	Material(float, float, float, float, float, float, float);
};

struct Object
{
	Vec pos;
	int pigm;
	int material;

	virtual bool intersect(Ray, float&);
};

struct Sphere: Object
{
	float radius;

	Sphere(int, int, Vec, float);
	bool intersect(Ray, float&);
};

/*
struct Plain
{
	float a;
	float b;
	float c;
	float d;

	Plain(float, float, float, float);
};

struct Polyhedron: Object
{
	std::vector<Plain>;

	Polyhedron(int, int, Vec, FILE*);
};
*/
