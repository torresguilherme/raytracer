#include "components.hpp"
#include <cmath>

float Vec::dot(const Vec& other) const
{
	return(x*other.x + y*other.y + z*other.z);
}

Vec Vec::cross(const Vec& other) const
{
	return Vec(
		y * other.z - z * other.y,
		x * other.z - z * other.x,
		x * other.y - y * other.x
	);
}

float Vec::magnitude() const
{
	return sqrt(dot(*this));
}

Vec Vec::normalize() const
{
	return Vec(x/magnitude(), y/magnitude(), z/magnitude());
}

float Vec::euclid_distance(const Vec& other) const
{
    return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

Vec Vec::reflect(const Vec& normal) const
{
    return *this - (normal * (float)2.0 * this->dot(normal));
}

Vec Vec::refract(const Vec& normal, float ni_over_nt) const
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

Vec Vec::interpolate(const Vec& other, float coefficient) const
{
    return *this * coefficient + other * (float)(1.0 - coefficient);
}

Vec Vec::operator+(const Vec& other) const
{
	return Vec(x+other.x, y+other.y, z+other.z);
}

Vec Vec::operator-(const Vec& other) const
{
	return Vec(x-other.x, y-other.y, z-other.z);
}

Vec Vec::operator*(const Vec& other) const
{
	return Vec(x*other.x, y*other.y, z*other.z);
}

Vec Vec::operator/(const Vec& other) const
{
	return Vec(x/other.x, y/other.y, z/other.z);
}

Vec Vec::operator*(float scalar) const
{
	return Vec(x*scalar, y*scalar, z*scalar);
}

Vec Vec::operator/(float scalar) const
{
	return Vec(x/scalar, y/scalar, z/scalar);
}

/*****************************************/

Vec Ray::point_at_t(float t) const
{
    return this->origin + this->dir * t;
}