#ifndef RAYTRACING_H_
#define RAYTRACING_H_

#include "components.hpp"
#include "scene.hpp"

Vec mean(std::vector<Vec> vectors);
void trace_rays_in_row(const Scene& scene, std::vector<short int>& pixel_array, short int row, short int width, short int height, short int rpp);
Vec trace_rays_in_pixel(const Scene& scene, short int row, short int col, short int width, short int height, short int rpp);
template <typename ShapeType>
std::pair<float, Vec> intersects(const Shape<ShapeType>& shape, Ray ray, const int type, bool occlusion=false, bool is_refracted=false);
Vec get_occlusion(const Scene& scene, Ray ray, float t, Vec color);

#endif