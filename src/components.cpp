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

float Vec::euclid_distance(const Vec& other)
{
    return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

Vec Vec::reflect(Vec& normal)
{
    return *this - (normal * (float)2.0 * (*this).dot(normal));
}

Vec Vec::refract(Vec& normal, float ni_over_nt)
{
    Vec unit_v = this->normalize();
    float cosine = unit_v.dot(normal);
    float discriminant = 1 - ni_over_nt * ni_over_nt * (1 - cosine * cosine);
    if(discriminant > 0)
    {
        return (unit_v - normal * cosine) * ni_over_nt - normal * (float)sqrt(discriminant);
    }

    return this->reflect(normal);
}

Vec Vec::interpolate(Vec& other, float coefficient)
{
    return *this * coefficient + other * (float)(1.0 - coefficient);
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