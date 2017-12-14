#ifndef NEURON_H
#define NEURON_H


#include <iostream>
#include <pthread.h> 
#include <semaphore.h>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <string>
#include <fstream>
#include "globaldata.h"
#include "tools.h"
#include "mysemaphore.h"

struct Connection{

	double weight;
	double deltaWeight;

};


class Neuron{
	
	private:
		
		std::vector<Connection> outputWeights;

	public:
		
		void setWeights(unsigned numOutputs, std::vector<double> weights);
		virtual void runNeuron(int neuron_num) = 0;

	

};



class FNeuron : public Neuron{

	public:
		void setAddr();
		void runNeuron(int neuron_num);

	private:
		std::string addr;


};

class HNeuron : public Neuron{

	public:

		void runNeuron(int neuron_num);
};


class ONeuron : public Neuron{

   public:

   	void runNeuron(int neuron_num);
};

#endif
