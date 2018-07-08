#include "scene.h"
#include <cmath>
 
Vec::Vec()
{
	x = 0;
	y = 0;
	z = 0;
}

Vec::Vec(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

float Vec::dot(Vec other)
{
	return(x*other.x + y*other.y + z*other.z);
}

float Vec::magnitude()
{
	return sqrt(dot(*this));
}

Vec Vec::normalize()
{
	return Vec(x/magnitude(), y/magnitude(), z/magnitude());
}

Vec Vec::operator+(Vec other)
{
	return Vec(x+other.x, y+other.y, z+other.z);
}

Vec Vec::operator-(Vec other)
{
	return Vec(x-other.x, y-other.y, z-other.z);
}

Vec Vec::operator*(Vec other)
{
	return Vec(x*other.x, y*other.y, z*other.z);
}

Vec Vec::operator/(Vec other)
{
	return Vec(x/other.x, y/other.y, z/other.z);
}
/************************************/

Ray::Ray(Vec o, Vec d)
{
	origin = o;
	dir = d;
}
/************************************/

Camera::Camera(Vec p, Vec a, Vec u, float ab)
{
	pos = p;
	aim = a;
	up = u;
	abertura = ab;
}
/************************************/

Light::Light(Vec c, Vec p, float a, float pa, float pa2)
{
	pos = p;
	color = c;
	constAten = a;
	propAten = pa;
	squarePropAten = pa2;
}
/************************************/

Pigm::Pigm(std::string t)
{
	type = t;
}
/************************************/

Material::Material(float a, float d, float s, float se, float kr, float kt, float i)
{
	ambient = a;
	diffuse = d;
	specular = s;
	specularExp = se;
	reflection = kr;
	transmission = kt;
	ior = i;
}
/************************************/

Sphere::Sphere(int p, int m, Vec c, float r)
{
	pigm = p;
	material = m;
	pos = c;
	radius = r;
}

bool Sphere::intersect(Ray ray, float& depth)
{
	return false;
}
