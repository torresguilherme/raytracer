#include "components.hpp"
#include "scene.hpp"
#include <vector>

template <typename NodeType>
struct OctreeCube
{
    Vec center;
    NodeType& node;
    std::vector<NodeType> children;
};

template <typename NodeType>
struct Octree
{
    int num_nodes;
    OctreeCube<NodeType> root_node;

    Octree(const Mesh& mesh):
    num_nodes(0)
    {

    };
};