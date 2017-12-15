#ifndef NET_H
#define NET_H

#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <semaphore.h>
#include <fstream>
#include <cstdlib>
#include <pthread.h>
#include <cmath>
#include <tgmath.h>

#include "neuron.h"
#include "tools.h"
#include "globaldata.h"
#include "mysemaphore.h"


//class Neuron;
typedef std::vector<FNeuron> Layer1;
typedef std::vector<HNeuron> Layer2;
typedef std::vector<ONeuron> Layer3;

typedef struct helper_runFN{

	int neuron_num;
	FNeuron* ptr;
} runFN_args;

typedef struct helper_runHN{

	int neuron_num;
	HNeuron* ptr;
} runHN_args;

typedef struct helper_runON{

	int neuron_num;
	ONeuron* ptr;
} runON_args;



class Net{
	
	public:

		Net(const std::vector<unsigned>& _topolopy);

		void readFirstLayerWeights();
		void readSecondLayerWeights();
		void readSecondLayerBias(); 
		void readOutputLayerBias(); 

		void getLayersInfoAddr();
		void buildNet();
		void startNet();
		void startFirstLayer(pthread_t*);
		void startSecondLayer(pthread_t*);
		void startOutputLayer(pthread_t*);
		void printarr();
		double calcRealOutputs(double, double, double);



	private:

		Layer1 l1;
		Layer2 l2;
		Layer3 l3;


		std::vector<std::vector<std::string> > firstLayerWeights;
		std::vector<std::string> secondLayerWeights;
		std::string layersInfoAddr;
		std::vector<unsigned> topology;


};


#endif

