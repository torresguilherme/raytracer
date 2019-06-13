#include "components.hpp"
#include <cmath>

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