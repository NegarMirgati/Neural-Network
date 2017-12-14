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


void FNeuron::runNeuron(int neuron_num){

	//cout<<"Hello fucking world"<<endl;

	ifstream myfile;
	string line;
	int counter = 0;

	string addr = "./" + itos(neuron_num) + ".txt";
	//cout<<"addr is "<<addr << endl;

	string temp = itos(neuron_num);
	//write(STDOUT_FILENO, "Hello from : ", 12);
	//write(STDOUT_FILENO, temp.c_str(), temp.size());
	myfile.open(addr.c_str());
    
	while ( myfile >> line ){

		//cout<<"Waiting Here" << endl;
        
		sem_wait( &GlobalData::data1.inp_sem[counter][neuron_num].rw_mutex );
		//cout<<"updating value of" << neuron_num << " row " << counter << endl ;
		write(STDOUT_FILENO, temp.c_str(), temp.size());
		GlobalData::data1.input[counter][neuron_num] = atof(line.c_str());
		sem_post( &GlobalData::data1.inp_sem[counter][neuron_num].rw_mutex);
		counter++;

	}



	
}

void HNeuron::runNeuron(int neuron_num){


}


void ONeuron::runNeuron(int neuron_num){


}
