#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include "scene.hpp"

std::uint8_t CHANNELS = 3;

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		std::cout<<"Usage: ./a.out <output_file>.ppm <optional_width> <optional_height>"<<std::endl;
		return -1;
	}

	std::string output_file = argv[1];
	std::uint16_t width = 480;
	std::uint16_t height = 340;
	if(argc >= 4)
	{
		width = std::atoi(argv[2]);
		height = std::atoi(argv[3]);
	}

	std::vector<std::uint8_t> pixel_array;
	pixel_array.resize(height * width * CHANNELS);

	// write to file
	std::ofstream file;
	file.open(output_file);
	file<<"P3\n"<<width<<' '<<height<<"\n255\n";

	for(auto it : pixel_array)
	{
		file<<(int)it<<' ';
	}
	file.close();

	return 0;
}
