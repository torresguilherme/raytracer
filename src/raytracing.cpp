#include "raytracing.hpp"
#include <cmath>

void trace_rays_in_row(const Scene& scene, std::vector<short int>& pixel_array, short int row, short int width, short int height, short int rpp)
{
    for(short int i = 0; i < width; i++)
    {
        Vec result_color = trace_rays_in_pixel(scene, row, i, width, height, rpp);
        pixel_array[row*width*3 + i*3] = result_color.x;
        pixel_array[row*width*3 + i*3 + 1] = result_color.y;
        pixel_array[row*width*3 + i*3 + 2] = result_color.z;
    }
}

Vec trace_rays_in_pixel(const Scene& scene, short int row, short int col, short int width, short int height, short int rpp)
{
    std::vector<Vec> colors;

    int sqrt_rpp = (int)floor(sqrt((float)rpp));
    for(short i = 0; i < rpp; i++)
    {
        float sampling_offset[2] = {
            sqrt_rpp - ((float)(i % sqrt_rpp) / (float)sqrt_rpp),
            sqrt_rpp - ((float)i / (float)sqrt_rpp / (float)sqrt_rpp)
        };

        // calculate ray direction
        Vec direction = Vec();
        Ray ray = Ray(scene.camera.pos, direction);
    }

    return Vec();
}

Vec trace_ray(const Scene& scene, const Ray&)
{
    return Vec();
}