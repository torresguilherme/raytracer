#ifndef RAYTRACING_H_
#define RAYTRACING_H_

#include "components.hpp"
#include "scene.hpp"

void trace_rays_in_row(const Scene& scene, std::vector<short int>& pixel_array, short int row, short int width, short int height, short int rpp);
Vec trace_rays_in_pixel(const Scene& scene, short int row, short int col, short int width, short int height, short int rpp);
Vec trace_ray(const Scene& scene, const Ray&);

#endif