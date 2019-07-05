#include "raytracing.hpp"
#include <cmath>
#include <iostream>
#include <random>

Vec SKY = Vec(0.2, 0.5, 0.7);
const float pixel_lenght = 0.005;
const float vision_range = MAXFLOAT;
const float too_near = 0.0005;
const int SPHERE_KIND = 0;
const int MESH_KIND = 1;

Vec mean(std::vector<Vec> vectors)
{
    Vec sum = Vec();
    for(auto it : vectors)
    {
        sum = sum + it;
    }

    sum = sum / vectors.size();
    return sum;
}

void trace_rays_in_row(const Scene& scene, std::vector<short int>& pixel_array, short int row, short int width, short int height, short int rpp)
{
    std::cout<<"Rendering row: "<<row<<'\n';
    for(short int i = 0; i < width; i++)
    {
        Vec result_color = trace_rays_in_pixel(scene, row, i, width, height, rpp);
        pixel_array[row*width*3 + i*3] = (short)result_color.x;
        pixel_array[row*width*3 + i*3 + 1] = (short)result_color.y;
        pixel_array[row*width*3 + i*3 + 2] = (short)result_color.z;
    }
}

Vec trace_rays_in_pixel(const Scene& scene, short int row, short int col, short int width, short int height, short int rpp)
{
    std::vector<Vec> colors;

    int sqrt_rpp = (int)floor(sqrt((float)rpp));
    float aspect_ratio = (float) width / (float) height;
    for(short i = 0; i < rpp; i++)
    {
        float sampling_offset[2] = {
            sqrt_rpp - ((float)(i % sqrt_rpp) / (float)sqrt_rpp),
            sqrt_rpp - ((float)i / (float)sqrt_rpp / (float)sqrt_rpp)
        };

        // calculate ray direction
        Vec direction = Vec(
            (2 * ((col + 0.5) / width) - 1) * tan(scene.camera.aperture / 2.0 * M_PI / 180.0) * aspect_ratio + sampling_offset[0] * pixel_lenght, // x coordinate
            (1 - 2 * ((row + 0.5) / height)) * tan(scene.camera.aperture / 2.0 * M_PI / 180.0) + sampling_offset[1] * pixel_lenght,
            1.0
        ) - scene.camera.pos;
        Ray ray = Ray(scene.camera.pos, direction);

        std::tuple<float, Vec, Vec> tuple = get_next_intersection(scene, ray);
        
        Vec color = get_occlusion(scene, ray, std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple));

        colors.push_back(color);
    }
    
    return mean(colors) * 255.0;
}

std::tuple<float, Vec, Vec> get_next_intersection(const Scene& scene, Ray ray)
{
    float min_distance = vision_range;
    Vec color = SKY;
    Vec normal = Vec();
    for(auto sphere : scene.spheres)
    {
        std::pair<float, Vec> intersection = intersects(scene, sphere, ray, SPHERE_KIND);
        if(intersection.first < min_distance && intersection.first > 0)
        {
            min_distance = intersection.first;
            color = intersection.second;
            normal = (ray.point_at_t(min_distance) = sphere.position).normalize();
        }
    }

    return std::make_tuple(min_distance, color, normal);
}

template <typename ShapeType>
std::pair<float, Vec> intersects(const Scene& scene, const Shape<ShapeType>& shape, Ray ray, const int type, bool occlusion, bool is_refracted)
{
    switch (type)
    {
        case SPHERE_KIND:
        {
            Vec oc = ray.origin - shape.position;
            float a = ray.dir.dot(ray.dir);
            float b = 2 * oc.dot(ray.dir);
            float c = oc.dot(oc) - shape.shape_type.radius * shape.shape_type.radius;
            float discriminant = b * b - 4 * a * c;
            if(discriminant > 0)
            {
                float solution = (-b - sqrt(discriminant)) / (2 * a);
                if (solution < too_near)
                {
                    return std::make_pair(-1, SKY);
                }

                if (shape.material.type == LAMBERT_TYPE)
                {
                    return std::make_pair(solution, shape.material.albedo * shape.material.lambert.k_diffuse);
                }
                else if(shape.material.type == REFLECT_TYPE)
                {
                    Ray reflected_ray = Ray(
                        ray.point_at_t(solution),
                        ray.dir.reflect((ray.point_at_t(solution) - shape.position).normalize()) + 
                            Vec(rand() / RAND_MAX, rand() / RAND_MAX, rand() / RAND_MAX) * shape.material.reflect.fuzz
                    );

                    std::tuple<float, Vec, Vec> result = get_next_intersection(scene, reflected_ray);
                    return std::make_pair(solution, 
                        std::get<1>(result).interpolate(shape.material.albedo, shape.material.reflect.k_attenuation)
                    );
                }
            }
            break;
        }

        default:
            return std::make_pair(-1, SKY);
    }

    return std::make_pair(-1, SKY);
}

Vec get_occlusion(const Scene& scene, Ray ray, float t, Vec color, const Vec& normal)
{
    std::vector<Vec> occluded_colors;
    for(auto light : scene.lights)
    {
        Ray ray_to_light = Ray(ray.point_at_t(t), light.pos - ray.point_at_t(t));
        for(auto sphere : scene.spheres)
        {
            if(intersects(scene, sphere, ray_to_light, SPHERE_KIND, true).first > too_near)
            {
                occluded_colors.push_back(Vec());
            }

            else
            {
                occluded_colors.push_back(color * ((ray_to_light.dir.dot(ray.dir.reflect(normal)) / 2 + 0.5)));
            }
        }
    }

    return mean(occluded_colors);
}