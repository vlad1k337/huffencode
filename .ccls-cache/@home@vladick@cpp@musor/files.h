#ifndef FILES_H
#define FILES_H

#include <string>
#include <unordered_map>

std::string readFile(const std::string path);
std::unordered_map<char, int> countFrequency(const std::string file);
void showFrequncies(std::unordered_map<char, int> frequencies);

#endif
