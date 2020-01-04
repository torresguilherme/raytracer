#ifndef RAYTRACING_H_
#define RAYTRACING_H_

#include "components.hpp"
#include "scene.hpp"

struct PointPack
{
    bool has_intersected;
    Material material;
    Vec point;
    Vec normal;

    PointPack():
    has_intersected(false),
    material(Material(LAMBERT_TYPE, Vec())),
    point(Vec()),
    normal(Vec())
    {};
};

inline float max(float a, float b);
Vec mean(std::vector<Vec> vectors);
void trace_rays_in_row(const Scene& scene, std::vector<short>& pixel_array, short row, short width, short height, short rpp);
Vec trace_rays_in_pixel(const Scene& scene, short row, short col, short width, short height, short rpp);
Vec get_ray_color(const Scene& scene, const Ray& ray);
PointPack get_final_intersection(const Scene& scene, const Ray& ray);
Vec material_color(PointPack& pack, const Scene& scene);
/*
std::tuple<float, Vec, Vec, bool> get_next_intersection(const Scene& scene, const Ray& ray, bool occlusion=false, bool is_refracted=false, bool self_collision=false);
template <typename ShapeType>
std::tuple<float, Vec, Vec, bool> intersects(const Scene& scene, const Shape<ShapeType>& shape, const Ray& ray, bool occlusion, bool is_refracted, bool self_collision);
template<> std::tuple<float, Vec, Vec, bool> intersects<Sphere>(const Scene& scene, const Shape<Sphere>& shape, const Ray& ray, bool occlusion, bool is_refracted, bool self_collision);
template<> std::tuple<float, Vec, Vec, bool> intersects<Mesh>(const Scene& scene, const Shape<Mesh>& shape, const Ray& ray, bool occlusion, bool is_refracted, bool self_collision);
float intersect_with_triangle(const Scene& scene, const Shape<Mesh>& shape, const Ray& ray, const Vec& v1, const Vec& v2, const Vec& v3);
Vec get_occlusion(const Scene& scene, Ray ray, float t, Vec color, const Vec& normal);
*/
#endif