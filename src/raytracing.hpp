#ifndef RAYTRACING_H_
#define RAYTRACING_H_

#include "components.hpp"
#include "scene.hpp"

inline float max(float a, float b);
Vec mean(std::vector<Vec> vectors);
void trace_rays_in_row(const Scene& scene, std::vector<short>& pixel_array, short row, short width, short height, short rpp);
Vec trace_rays_in_pixel(const Scene& scene, short row, short col, short width, short height, short rpp);
std::tuple<float, Vec, Vec> get_next_intersection(const Scene& scene, const Ray& ray, bool occlusion=false, bool is_refracted=false, bool self_collision=false);
template <typename ShapeType>
std::tuple<float, Vec, Vec> intersects(const Scene& scene, const Shape<ShapeType>& shape, const Ray& ray, const int type, bool occlusion=false, bool is_refracted=false, bool self_collision=false);
template<> std::tuple<float, Vec, Vec> intersects<Sphere>(const Scene& scene, const Shape<Sphere>& shape, const Ray& ray, const int type, bool occlusion, bool is_refracted, bool self_collision);
template<> std::tuple<float, Vec, Vec> intersects<Mesh>(const Scene& scene, const Shape<Mesh>& shape, const Ray& ray, const int type, bool occlusion, bool is_refracted, bool self_collision);
Vec get_occlusion(const Scene& scene, Ray ray, float t, Vec color, const Vec& normal);

#endif