#include <iostream>
#include <fstream>
#include <sstream>
#include "files.h"

std::string readFile(const std::string path)
{
	std::ifstream input(path);
	std::stringstream file;

	if(input.good())
	{
		file << input.rdbuf();
		return file.str();
	}
	else {
		std::cout<< "Gde fail blyad";
		return nullptr;
	}
}
std::unordered_map<char, int> countFrequency(const std::string file)
{
	std::unordered_map<char, int> frequencies;
	for(char symbol : file)
	{
		frequencies[symbol] += 1;
	}
	return frequencies;
}

void showFrequncies(std::unordered_map<char, int> frequencies)
{
	for(std::pair<char, int> entry : frequencies)
	{
		std::cout << "Symbol \"" << entry.first << "\" found " << entry.second << " times\n";
	}
	
}


