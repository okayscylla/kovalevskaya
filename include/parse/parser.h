#pragma once

#include "types/basic/world.h"

#include <string>
#include <fstream>


World loadFromSillyFile(std::string infile); // TODO: implement this;

bool saveToSillyFile(const World* world, std::string outfile); // TODO: implement this