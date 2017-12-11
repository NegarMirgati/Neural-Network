#ifndef NEURON_H
#define NEURON_H


#include <iostream>
#include <pthread.h> 
#include <semaphore.h>
#include <cstdlib>
#include <vector>
#include <string>
#include "globaldata.h"

struct Connection{

	double weight;
	double deltaWeight;

};





class Neuron{
	
	private:
		
		std::vector<Connection> outputWeights;

	public:
		
		void setWeights(unsigned numOutputs, std::vector<double> weights);
		virtual void runNeuron() = 0;

	

};



class FNeuron : public Neuron{

	public:
		void setAddr();
		void runNeuron();

	private:
		std::string addr;


};


#endif
