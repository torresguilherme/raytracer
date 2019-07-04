#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <memory>
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

template <typename ShapeType>
struct Shape
{
    Vec position;
    Material material;
    ShapeType shape_type;
    bool emitting;

    Shape(Vec v, const Material& m, const ShapeType& t, bool emitting=false):
    position(v),
    material(m),
    shape_type(t),
    emitting(emitting)
    {};
};

struct Scene
{
    std::vector<Shape<Sphere>> spheres;
    std::vector<Shape<Mesh>> meshes;
    std::vector<Light> lights;
    Camera camera;

    Scene(Camera c): camera(c) {};
};


#endif