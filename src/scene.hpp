#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <memory>
#include "components.hpp"

template<typename T, typename C>
struct Shape
{
    Vec position;
    Material<C> material;
    std::unique_ptr<T> shape_type;

    Shape(Vec, Material<C>, T);
};

struct Sphere
{
    float radius;

    Sphere(float);
};

struct Mesh
{
    std::vector<Vec> vertices;
    std::vector<Vec> normals;
    std::vector<unsigned int> face_indices;
    std::vector<unsigned int> normal_indices;

    Mesh(std::string);
};

#endif