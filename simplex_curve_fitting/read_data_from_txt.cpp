#include <fstream>
#include "container.h"
void get_file_data(const char* filename, int num_points, vvector& data_container)
{
	std::ifstream fileIn(filename, std::ios::in);
	if(fileIn.fail()) exit(0);
	data_container = vvector(num_points);
	for (int i = 1; i <= num_points; i++) {
		fileIn >> data_container[i];
	}
	
	fileIn.close();
}
