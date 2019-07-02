#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <memory>

struct Vec
{
	float x;
	float y;
	float z;

	Vec(): x(0), y(0), z(0) {};
	Vec(float _x, float _y, float _z):
    x(_x),
    y(_y),
    z(_z)
    {};

	float dot(const Vec& other);
	Vec cross(const Vec& other);
	float magnitude();
	Vec normalize();
    float euclid_distance(const Vec& other);
    Vec reflect(Vec& normal);
    Vec refract(Vec& normal, float ni_over_nt);
    Vec interpolate(Vec& other, float coefficient);

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

	Ray(Vec o, Vec d):
    origin(o),
    dir(d)
    {};
};

struct Camera
{
	Vec pos;
	Vec aim;
	Vec up;
	float aperture;

	Camera(Vec p, Vec a, Vec u, float ap):
    pos(p),
    aim(a),
    up(u),
    aperture(ap)
    {};
};

struct Light
{
	Vec pos;
	Vec color;
	float const_aten;
	float prop_aten;
	float square_prop_aten;

	Light(Vec p, Vec c, float ca, float pa, float spa):
    pos(p),
    color(c),
    const_aten(ca),
    prop_aten(pa),
    square_prop_aten(spa)
    {};
};

struct LambertComponent
{
    float k_diffuse;

    LambertComponent(float kd):
    k_diffuse(kd)
    {};
};

struct ReflectComponent
{
    float k_attenuation;
    float fuzz;

    ReflectComponent(float ka, float f):
    k_attenuation(ka),
    fuzz(f)
    {};
};

struct DielectricComponent
{
    float k_attenuation;
    float k_refraction;
    float fuzz;

    DielectricComponent(float ka, float kr, float f):
    k_attenuation(ka),
    k_refraction(kr),
    fuzz(f)
    {};
};

struct Material
{
    Vec albedo;
    std::string type;
    LambertComponent lambert;
    ReflectComponent reflect;
    DielectricComponent dielectric;

    Material(std::string t, Vec a, float kd=0.0, float ka=0.0, float f=0.0, float kr=0.0):
    type(t),
    albedo(a),
    lambert(LambertComponent(kd)),
    reflect(ReflectComponent(ka, f)),
    dielectric(DielectricComponent(ka, kr, f))
    {};
};

#endif