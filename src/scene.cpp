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
