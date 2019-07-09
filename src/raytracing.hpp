#ifndef RAYTRACING_H_
#define RAYTRACING_H_

#include "components.hpp"
#include "scene.hpp"

Vec mean(std::vector<Vec> vectors);
void trace_rays_in_row(const Scene& scene, std::vector<short>& pixel_array, short row, short width, short height, short rpp);
Vec trace_rays_in_pixel(const Scene& scene, short row, short col, short width, short height, short rpp);
std::tuple<float, Vec, Vec> get_next_intersection(const Scene& scene, Ray ray, bool occlusion=false, bool is_refracted=false, bool self_collision=false);
template <typename ShapeType>
std::pair<float, Vec> intersects(const Scene& scene, const Shape<ShapeType>& shape, Ray ray, const int type, bool occlusion=false, bool is_refracted=false, bool self_collision=false);
Vec get_occlusion(const Scene& scene, Ray ray, float t, Vec color, const Vec& normal);

#endif