#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>

#include "raytracing.hpp"
#include "components.hpp"
#include "scene.hpp"
#include "thread_pool.hpp"

short int CHANNELS = 3;
short int num_threads = std::thread::hardware_concurrency();

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		std::cout<<"Usage: ./a.out <output_file>.ppm <optional_width> <optional_height>\n";
		return -1;
	}

	std::string output_file = argv[1];
	short int width = 480;
	short int height = 340;
	if(argc >= 4)
	{
		width = std::atoi(argv[2]);
		height = std::atoi(argv[3]);
	}

	std::vector<short int> pixel_array;
	pixel_array.resize(height * width * CHANNELS);

	// write to file
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
