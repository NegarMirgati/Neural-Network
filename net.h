#ifndef NET_H
#define NET_H

#include <iostream>
#include <string>
#include <vector>
#include <semaphore.h>
#include <fstream>
#include <cstdlib>

#include "neuron.h"
#include "tools.h"
#include "globaldata.h"


//class Neuron;
//typedef std::vector<Neuron> Layer;

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
		void testGlobal();



	private:

		std::vector<Layer> layers;  ///layers[layer_num][neuron_num]
		std::vector<std::vector<std::string> > firstLayerWeights;
		std::vector<std::string> secondLayerWeights;
		std::string layersInfoAddr;
		std::vector<unsigned> topology;


};


#endif

