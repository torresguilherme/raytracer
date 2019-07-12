#include "scene.hpp"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

Mesh::Mesh(std::string filename, int shading_type, const Vec& scale, const Vec& translation): shading_type(shading_type)
{
    std::ifstream file;
    file.open(filename, std::ifstream::in);

    std::string line;
    while(file.good())
    {
        std::getline(file, line);
        std::istringstream iss(line);
        std::vector<std::string> split_line((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
        if(split_line[0] == "v")
        {
            char c;
            float x, y, z;
            iss>>c>>x>>y>>z;
            vertices.push_back(Vec((x + translation.x) * scale.x, (y + translation.y) * scale.y, (z + translation.z) * scale.z));
        }
        else if(split_line[0] == "vn")
        {
            std::string s;
            float x, y, z;
            iss>>s>>x>>y>>z;
            normals.push_back(Vec(x, y, z));
        }
        else if(split_line[0] == "vt")
        {
            std::string s;
            float u, v;
            iss>>s>>u>>v;
            uvs.push_back(u);
            uvs.push_back(v);
        }
        else if(split_line[0] == "f")
        {
            char c;
            uint v1, v2, v3, t1, t2, t3, n1, n2, n3;
            iss>>c>>v1>>v2>>v3>>t1>>t2>>t3>>n1>>n2>>n3;
            vertex_indices.push_back(v1-1);
            vertex_indices.push_back(v2-1);
            vertex_indices.push_back(v3-1);
            uv_indices.push_back(t1-1);
            uv_indices.push_back(t2-1);
            uv_indices.push_back(t3-1);
            normal_indices.push_back(n1-1);
            normal_indices.push_back(n2-1);
            normal_indices.push_back(n3-1);
        }
    }

    file.close();
}