#include "neuron.h"

using namespace std;

/*Neuron::Neuron(){

	/*for(unsigned i = 0; i < numOutputs ; i++){

		outputWeights.push_back(Connection());
		cout<<"Assigning weight"<< i << " to neuron which equals to "<< weights[i] << endl;
		outputWeights.back().weight = weights[i];
	}

}*/

void Neuron::setWeights(unsigned numOutputs, std::vector<double> weights){

	cout<<" num outputs = "<< numOutputs << endl;

	for(unsigned i = 0; i < numOutputs ; i++){

		cout.precision(16);

		outputWeights.push_back(Connection());
		cout<<"Assigning weight"<< i << " to neuron which equals to "<< weights[i] << endl;
		outputWeights.back().weight = weights[i];
	}


}


void FNeuron::runNeuron(){

	
}
