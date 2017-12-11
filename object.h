#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>
#include <vector>
#include <semaphore.h>

struct Object{

	std::vector<sem_t> inp_sem;

	std::vector<std::vector<double> > input;

	std::vector<double> firstLayerOut;

	std::vector<double> secondLayerOut;

};



#endif