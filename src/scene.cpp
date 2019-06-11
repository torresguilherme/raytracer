#include "scene.hpp"
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

float Vec::dot(const Vec& other)
{
	return(x*other.x + y*other.y + z*other.z);
}

Vec Vec::cross(const Vec& other)
{
	return Vec(
		y * other.z - z * other.y,
		x * other.z - z * other.x,
		x * other.y - y * other.x
	);
}

float Vec::magnitude()
{
	return sqrt(dot(*this));
}

Vec Vec::normalize()
{
	return Vec(x/magnitude(), y/magnitude(), z/magnitude());
}

Vec Vec::operator+(const Vec& other)
{
	return Vec(x+other.x, y+other.y, z+other.z);
}

Vec Vec::operator-(const Vec& other)
{
	return Vec(x-other.x, y-other.y, z-other.z);
}

Vec Vec::operator*(const Vec& other)
{
	return Vec(x*other.x, y*other.y, z*other.z);
}

Vec Vec::operator/(const Vec& other)
{
	return Vec(x/other.x, y/other.y, z/other.z);
}

Vec Vec::operator*(float scalar)
{
	return Vec(x*scalar, y*scalar, z*scalar);
}

Vec Vec::operator/(float scalar)
{
	return Vec(x/scalar, y/scalar, z/scalar);
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