#include "scene.hpp"
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <iostream>

Mesh::Mesh(std::string filename, int shading_type, const Vec& scale): shading_type(shading_type)
{
    std::ifstream file;
    file.open(filename, std::ifstream::in);

    std::string line;
    while(file.good())
    {
        std::getline(file, line);
        std::istringstream iss(line);
        std::string key;
        iss>>key>>std::ws;

        if(key == "v")
        {
            float x, y, z;
            iss>>x>>y>>z;
            vertices.push_back(Vec(x * scale.x, y * scale.y, z * scale.z));
        }
        else if(key == "vn")
        {
            float x, y, z;
            iss>>x>>y>>z;
            normals.push_back(Vec(x, y, z));
        }
        else if(key == "vt")
        {
            float u, v;
            iss>>u>>v;
            uvs.push_back(u);
            uvs.push_back(v);
        }
        else if(key == "f")
        {
            uint v, t, n;
            while(!iss.eof())
            {
                iss>>v>>std::ws;
                vertex_indices.push_back(v);
                if(iss.peek() == '/')
                {
                    iss.get();
                    if(iss.peek() == '/')
                    {
                        iss.get();
                        iss>>n>>std::ws;
                        normal_indices.push_back(n);
                    }
                    else
                    {
                        iss>>t>>std::ws;
                        uv_indices.push_back(t);
                        if(iss.peek() == '/')
                        {
                            iss.get();
                            iss>>n>>std::ws;
                            normal_indices.push_back(n);
                        }
                    }
                }
            }
        }
    }

    file.close();
}