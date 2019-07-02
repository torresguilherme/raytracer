#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>

#include "raytracing.hpp"
#include "components.hpp"
#include "scene.hpp"
#include "thread_pool.hpp"

short int CHANNELS = 3;
short int RAYS_PER_PIXEL = 100;
short int num_threads = std::thread::hardware_concurrency();

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		std::cout<<"Usage: ./a.out <output_file>.ppm <optional_width> <optional_height>\n";
		return -1;
	}

    std::cout<<"Reading parameters\n";
	std::string output_file = argv[1];
	short int width = 480;
	short int height = 340;
	if(argc >= 4)
	{
		width = std::atoi(argv[2]);
		height = std::atoi(argv[3]);
	}

    std::cout<<"Making pixel array\n";
	std::vector<short int> pixel_array;
	pixel_array.resize(height * width * CHANNELS);

    std::cout<<"Preparing scene\n";
    // declare scene
    Camera camera = Camera(Vec(0.0, 0.0, 0.0),
        Vec(0.0, 0.0, 5.0),
        Vec(0.0, 1.0, 0.0),
        45.0);
    
    Scene scene = Scene(camera);

    // declare materials
    Material red_material = Material("lambert", Vec(1.0, 0.0, 0.0), 0.7);
    Material gold_material = Material("reflect", Vec(0.8, 0.8, 0.2), 0.0, 0.5, 0.1);
    Material glass_material = Material("dielectric", Vec(0.9, 0.9, 0.9), 0.0, 0.1, 0.0, 1.7);
    Material ground_material = Material("lambert", Vec(0.2, 0.3, 0.2), 0.6);

    scene.spheres.push_back(Shape<Sphere>(Vec(0.0, 0.0, 5.0), red_material, Sphere(1.0)));
    scene.spheres.push_back(Shape<Sphere>(Vec(-1.0, -0.5, 4.5), glass_material, Sphere(1.0)));
    scene.spheres.push_back(Shape<Sphere>(Vec(1.0, -0.5, 4.5), gold_material, Sphere(1.0)));
    scene.spheres.push_back(Shape<Sphere>(Vec(0.0, -100.5, 0.0), ground_material, Sphere(100.0)));

    std::cout<<"Casting rays\n";
    for(short int i = 0; i < height; i++)
    {
        trace_rays_in_row(scene, pixel_array, i, width, height, RAYS_PER_PIXEL);
    }

	// write to file
    std::cout<<"Writing to file\n";
	std::ofstream file;
	file.open(output_file);
	file<<"P3\n"<<width<<' '<<height<<"\n255\n";

	for(auto it : pixel_array)
	{
		file<<it<<' ';
	}
	file.close();

	return 0;
}
