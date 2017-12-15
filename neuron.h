#ifndef NEURON_H
#define NEURON_H


#include <iostream>
#include <pthread.h> 
#include <semaphore.h>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <cmath>
#include <string>
#include <fstream>
#include "globaldata.h"
#include "tools.h"
#include "mysemaphore.h"

class FNeuron;
class HNeuron;
class ONeuron;

typedef std::vector<FNeuron> Layer1;
typedef std::vector<HNeuron> Layer2;
typedef std::vector<ONeuron> Layer3;


struct Connection{

	double weight;
	double deltaWeight;

};


class Neuron{
	
	protected:
		
		//std::vector<Connection> outputWeights;
		


	public:
		std::vector<Connection> outputWeights;
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

        double calcResult(double x, double y, double z , double w1 , double w2, double w3);
		void runNeuron(int neuron_num);
		void setBias(double Bias);
		void setPrevLayerRefrence(const Layer1 & ref);
		

	private:
		Layer1 prevLayer;
		double bias;

};


class ONeuron : public Neuron{

   public:
    double calcResult(int i);
   	void runNeuron(int neuron_num);
   	void setBias(double Bias);
   	void setPrevLayerRefrence(const Layer2 & ref);
   	

   private:
   	Layer2 prevLayer;
   	double bias;
};

#endif
