#include "raytracing.hpp"
#include <cmath>
#include <iostream>
#include <random>
#include <mutex>
#include <cstring>

const float pixel_lenght = 0.005;
const float vision_range = MAXFLOAT;
const float too_near = 0.0005;
const int SPHERE_KIND = 0;
const int MESH_KIND = 1;
const float SHADOW_JITTER = 0.8;
std::mutex mu;

inline float max(float a, float b)
{
    return a > b? a : b;
}

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

void trace_rays_in_row(const Scene& scene, std::vector<short>& pixel_array, short row, short width, short height, short rpp)
{
    std::unique_lock<std::mutex> lock(mu);
    std::cout<<"Rendering row: "<<row<<'\n';
    lock.unlock();
    for(short int i = 0; i < width; i++)
    {
        Vec result_color = trace_rays_in_pixel(scene, row, i, width, height, rpp);
        pixel_array[row*width*3 + i*3] = (short)result_color.x;
        pixel_array[row*width*3 + i*3 + 1] = (short)result_color.y;
        pixel_array[row*width*3 + i*3 + 2] = (short)result_color.z;
    }
}

Vec trace_rays_in_pixel(const Scene& scene, short row, short col, short width, short height, short rpp)
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

        colors.push_back(get_ray_color(scene, ray));
    }

    return mean(colors) * 255.0;
}

Vec get_ray_color(const Scene& scene, const Ray& ray)
{
    PointPack pack = get_final_intersection(scene, ray);
    return material_color(pack, scene);
}

PointPack get_final_intersection(const Scene& scene, const Ray& ray)
{
    PointPack ret;
    return ret;
}

Vec material_color(PointPack& pack, const Scene& scene)
{
    return Vec();
}

/*
std::tuple<float, Vec, Vec, bool> get_next_intersection(const Scene& scene, const Ray& ray, bool occlusion, bool is_refracted, bool self_collision)
{
    float min_distance = vision_range;
    Vec color = SKY;
    Vec normal = Vec();
    bool dot_product_light = true;
    for(auto const &sphere : scene.spheres)
    {
        std::tuple<float, Vec, Vec, bool> intersection = intersects(scene, sphere, ray, occlusion, is_refracted, self_collision);
        if(std::get<0>(intersection) < min_distance && std::get<0>(intersection) > 0)
        {
            min_distance = std::get<0>(intersection);
            color = std::get<1>(intersection);
            normal = std::get<2>(intersection);
            dot_product_light = std::get<3>(intersection);
        }
    }

    for(auto const &mesh : scene.meshes)
    {
        std::tuple<float, Vec, Vec, bool> intersection = intersects(scene, mesh, ray, occlusion, is_refracted, self_collision);
        if(std::get<0>(intersection) < min_distance && std::get<0>(intersection) > 0)
        {
            min_distance = std::get<0>(intersection);
            color = std::get<1>(intersection);
            normal = std::get<2>(intersection);
            dot_product_light = std::get<3>(intersection);
        }
    }

    if(min_distance < vision_range)
    {
        return std::make_tuple(min_distance, color, normal, dot_product_light);
    }

    return std::make_tuple(-1, SKY, Vec(), dot_product_light);
}

template<> std::tuple<float, Vec, Vec, bool> intersects<Sphere>(const Scene& scene, const Shape<Sphere>& shape, const Ray& ray, bool occlusion, bool is_refracted, bool self_collision)
{
    Vec oc = ray.origin - shape.position;
    float a = ray.dir.dot(ray.dir);
    float b = 2 * oc.dot(ray.dir);
    float c = oc.dot(oc) - shape.shape_type.radius * shape.shape_type.radius;
    float discriminant = b * b - 4 * a * c;
    if(discriminant > 0)
    {
        float solution = (-b - sqrt(discriminant)) / (2 * a);
        if (solution < too_near && !self_collision)
        {
            return std::make_tuple(-1, SKY, Vec(), true);
        }

        Vec normal = (ray.point_at_t(solution) - shape.position).normalize();

        if (shape.material.type == LAMBERT_TYPE)
        {
            return std::make_tuple(solution, shape.material.albedo * shape.material.lambert.k_diffuse, normal, true);
        }
        else if(shape.material.type == REFLECT_TYPE)
        {
            Ray reflected_ray = Ray(
                ray.point_at_t(solution),
                ray.dir.reflect((ray.point_at_t(solution) - shape.position).normalize()) + 
                    Vec(rand() / (double)RAND_MAX, rand() / (double)RAND_MAX, rand() / (double)RAND_MAX) * shape.material.reflect.fuzz
            );

            std::tuple<float, Vec, Vec, bool> result = get_next_intersection(scene, reflected_ray, occlusion, is_refracted, false);
            return std::make_tuple(solution, 
                std::get<1>(result).interpolate(shape.material.albedo, 1 - shape.material.reflect.k_attenuation),
                normal,
                std::get<3>(result)
            );
        }
        else if(shape.material.type == DIELECTRIC_TYPE)
        {
            if(is_refracted)
            {
                Ray reflected_ray = Ray(
                    ray.point_at_t(solution),
                    ray.dir.refract((ray.point_at_t(solution) - shape.position).normalize(), shape.material.dielectric.k_refraction) + 
                        Vec(rand() / (double)RAND_MAX, rand() / (double)RAND_MAX, rand() / (double)RAND_MAX) * shape.material.dielectric.fuzz
                );

                std::tuple<float, Vec, Vec, bool> result = get_next_intersection(scene, reflected_ray, occlusion, false, false);
                return std::make_tuple(solution, 
                    std::get<1>(result).interpolate(shape.material.albedo, 1 - shape.material.dielectric.k_attenuation),
                    normal, 
                    false
                );
            }
            else
            {
                Ray reflected_ray = Ray(
                    ray.point_at_t(solution),
                    ray.dir.refract((ray.point_at_t(solution) - shape.position).normalize(), 1.0/shape.material.dielectric.k_refraction) + 
                        Vec(rand() / (double)RAND_MAX, rand() / (double)RAND_MAX, rand() / (double)RAND_MAX) * shape.material.dielectric.fuzz
                );
                std::tuple<float, Vec, Vec, bool> result = get_next_intersection(scene, reflected_ray, occlusion, true, false);
                return std::make_tuple(!occlusion ? solution : std::get<0>(result), 
                    std::get<1>(result).interpolate(shape.material.albedo, 1 - shape.material.dielectric.k_attenuation),
                    normal, 
                    false
                );
            }
        }
    }
    return std::make_tuple(-1, SKY, Vec(), true);
}

template<> std::tuple<float, Vec, Vec, bool> intersects<Mesh>(const Scene& scene, const Shape<Mesh>& shape, const Ray& ray, bool occlusion, bool is_refracted, bool self_collision)
{
    float min_distance = vision_range;
    uint index;
    for(uint i = 0; i < shape.shape_type.vertex_indices.size() / 3; i++)
    {
        float intersection = intersect_with_triangle(scene, shape, ray,
            shape.shape_type.vertices[shape.shape_type.vertex_indices[i*3]] + shape.position,
            shape.shape_type.vertices[shape.shape_type.vertex_indices[i*3+1]] + shape.position,
            shape.shape_type.vertices[shape.shape_type.vertex_indices[i*3+2]] + shape.position);
        if(intersection > (self_collision ? 0 : too_near) && intersection < min_distance)
        {
            min_distance = intersection;
            index = i;
        }
    }

    if(min_distance < vision_range)
    {
        Vec normal1 = shape.shape_type.normals[shape.shape_type.normal_indices[index*3]];
        Vec normal2 = shape.shape_type.normals[shape.shape_type.normal_indices[index*3 + 1]];
        Vec normal3 = shape.shape_type.normals[shape.shape_type.normal_indices[index*3 + 2]];
        Vec normal = normal1.interpolate(normal2, 0.5).interpolate(normal3, 0.5);
        if(shape.shape_type.shading_type == PHONG_SHADING)
        {
            // apply interpolation proportional to vertex distance
        }

        // apply material effect
        if(shape.material.type == LAMBERT_TYPE)
        {
            return std::make_tuple(min_distance, shape.material.albedo * shape.material.lambert.k_diffuse, normal, true);
        }
        else if(shape.material.type == REFLECT_TYPE)
        {
            Ray reflected_ray = Ray(
                ray.point_at_t(min_distance),
                ray.dir.reflect(normal) + 
                    Vec(rand() / (double)RAND_MAX, rand() / (double)RAND_MAX, rand() / (double)RAND_MAX) * shape.material.reflect.fuzz
            );

            std::tuple<float, Vec, Vec, bool> result = get_next_intersection(scene, reflected_ray, occlusion, is_refracted, false);
            return std::make_tuple(min_distance, 
                std::get<1>(result).interpolate(shape.material.albedo, 1 - shape.material.reflect.k_attenuation),
                normal, 
                std::get<3>(result)
            );
        }
        else if(shape.material.type == DIELECTRIC_TYPE)
        {
            if(is_refracted)
            {
                Ray reflected_ray = Ray(
                    ray.point_at_t(min_distance),
                    ray.dir.refract(normal, shape.material.dielectric.k_refraction) + 
                        Vec(rand() / (double)RAND_MAX, rand() / (double)RAND_MAX, rand() / (double)RAND_MAX) * shape.material.dielectric.fuzz
                );

                std::tuple<float, Vec, Vec, bool> result = get_next_intersection(scene, reflected_ray, occlusion, false, false);
                return std::make_tuple(min_distance, 
                    std::get<1>(result).interpolate(shape.material.albedo, 1 - shape.material.dielectric.k_attenuation),
                    normal, 
                    false
                );
            }
            else
            {
                Ray reflected_ray = Ray(
                    ray.point_at_t(min_distance),
                    ray.dir.refract(normal, 1.0/shape.material.dielectric.k_refraction) + 
                        Vec(rand() / (double)RAND_MAX, rand() / (double)RAND_MAX, rand() / (double)RAND_MAX) * shape.material.dielectric.fuzz
                );
                std::tuple<float, Vec, Vec, bool> result = get_next_intersection(scene, reflected_ray, occlusion, true, false);
                return std::make_tuple(!occlusion ? min_distance : std::get<0>(result), 
                    std::get<1>(result).interpolate(shape.material.albedo, 1 - shape.material.dielectric.k_attenuation),
                    normal,
                    false
                );
            }
        }
    }

    return std::make_tuple(-1, SKY, Vec(), true);
}

float intersect_with_triangle(const Scene& scene, const Shape<Mesh>& shape, const Ray& ray, const Vec& v0, const Vec& v1, const Vec& v2)
{
    Vec edge0 = v1 - v0;
    Vec edge1 = v2 - v1;
    Vec edge2 = v0 - v2;

    // compute plane intersection 
    Vec v0v1 = v1 - v0;
    Vec v0v2 = v2 - v0;
    Vec plane_normal = v0v1.cross(v0v2);
    float area2 = plane_normal.magnitude();

    float n_dot_ray_dir = plane_normal.dot(ray.dir);
    if(n_dot_ray_dir < too_near)
    {
        // paralelas (ou quase), nao tem interseçao
        return -1;
    }

    float d = plane_normal.dot(v0);

    // compute t
    float t = (plane_normal.dot(ray.origin) + d) / n_dot_ray_dir;

    if(t < 0)
    {
        // triangulo esta atras do raio
        return -1;
    }

    // compute intersection point
    Vec intersection_point = ray.origin + ray.dir * t;

    // inside/outside test
    Vec vp0 = intersection_point - v0;
    Vec cross = edge0.cross(vp0);
    if(plane_normal.dot(cross) < 0)
        return -1;

    Vec vp1 = intersection_point - v1;
    cross = edge1.cross(vp1);
    if(plane_normal.dot(cross) < 0)
        return -1;

    Vec vp2 = intersection_point - v2;
    cross = edge2.cross(vp2);
    if(plane_normal.dot(cross) < 0)
        return -1;

    return t;
}

Vec get_occlusion(const Scene& scene, Ray ray, float t, Vec color, const Vec& normal)
{
    std::vector<Vec> occluded_colors;
    for(auto light : scene.lights)
    {
        Ray ray_to_light = Ray(ray.point_at_t(t) + normal * too_near,
            light.pos - ray.point_at_t(t) + Vec(rand() / (double)RAND_MAX, rand() / (double)RAND_MAX, rand() / (double)RAND_MAX) * SHADOW_JITTER);
        std::tuple<float, Vec, Vec, bool> tuple = get_next_intersection(scene, ray_to_light, true, false, false);
        float distance = std::get<0>(tuple);
        bool dot_product_light = std::get<3>(tuple);
        if(distance > 0 && distance < ray_to_light.origin.euclid_distance(light.pos))
        {
            occluded_colors.push_back(Vec());
        }
        else
        {
            float light_distance = ray_to_light.origin.euclid_distance(light.pos);
            occluded_colors.push_back(color * light.energy * (1 / light.const_aten) *
                max(ray_to_light.dir.dot(normal) * dot_product_light, 0) *
                (1 / (light.prop_aten * light_distance * light_distance)));
        }
    }

    return mean(occluded_colors);
}
*/