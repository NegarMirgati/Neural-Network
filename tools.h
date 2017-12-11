#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>

std::vector<std::string> split(std::string, char);
double fRand(double fMin, double fMax);
void write_on_file(std::string addr, double data);
void generate_input(std::string addr);
void get_seed();
void get_num_of_inputs();
void init();


#endif