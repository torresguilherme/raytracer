#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <memory>
#include <variant>
#include "components.hpp"

struct Sphere
{
    float radius;

    Sphere(float r): radius(r) {};
};

struct Mesh
{
    std::vector<Vec> vertices;
    std::vector<float> uvs;
    std::vector<Vec> normals;
    std::vector<unsigned int> vertex_indices;
    std::vector<unsigned int> uv_indices;
    std::vector<unsigned int> normal_indices;

    Mesh(std::string);
};

using ShapeType = std::variant<Sphere, Mesh>;

struct Shape
{
    Vec position;
    Material material;
    ShapeType shape_type;

    Shape(Vec v, Material m, ShapeType t):
    position(v),
    material(m),
    shape_type(t)
    {};
};

struct Scene
{
    std::vector<Shape> shapes;
    std::vector<Light> lights;
    Camera camera;

    Scene(Camera c): camera(c) {};
};


#endif