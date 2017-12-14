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



class Net{
	
	public:

		Net(const std::vector<unsigned>& _topolopy);
		void feedForward();
		void getResults();
		void readFirstLayerWeights();
		void readSecondLayerWeights();
		void getLayersInfoAddr();
		void buildNet();
		void startNet();
		void startFirstLayer();
		void printarr();



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

