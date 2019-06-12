#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <memory>

struct Vec
{
	float x;
	float y;
	float z;

	Vec();
	Vec(float, float, float);

	float dot(const Vec& other);
	Vec cross(const Vec& other);
	float magnitude();
	Vec normalize();

	Vec operator+(const Vec& other);
	Vec operator-(const Vec& other);
	Vec operator*(const Vec& other);
	Vec operator/(const Vec& other);
	Vec operator*(float scalar);
	Vec operator/(float scalar);
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

template <typename T>
struct Material
{
    Vec albedo;
    std::string type;
    std::unique_ptr<T> component;

    Material(std::string, Vec, T);
};

struct LambertComponent
{
    float k_diffuse;

    LambertComponent(float);
};

struct ReflectComponent
{
    float k_attenuation;
    float fuzz;

    ReflectComponent(float, float);
};

struct DielectricComponent
{
    float k_attenuation;
    float k_refraction;
    float fuzz;

    DielectricComponent(float, float, float);
};

#endif