#include "neuron.h"

using namespace std;


void HNeuron::setBias(double Bias){

	cout<<" Setting Bias " << Bias << endl;

	this->bias = Bias;
}

void ONeuron::setBias(double Bias){

	cout<<" Setting Bias " << Bias << endl;

	this->bias = Bias;
}

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


	string temp = itos(neuron_num);

	myfile.open(addr.c_str());
    
	while ( myfile >> line ){

		GlobalData::data1.input[counter][neuron_num] = atof(line.c_str());
		sem_post( &GlobalData::data1.inp_sem[counter].rw_mutex);
		counter++;

	}
	
}


void HNeuron::runNeuron(int neuron_num){

	
	vector <bool> calculated (GlobalData::data1.input.size(), false);

	for( int i = 0; i < calculated.size() ; i++){

		if( calculated[i] == false ){

			int hiddenLayerSize = GlobalData::data1.hiddenLayerSize;


            sem_wait(&GlobalData::data1.inp_sem[i].mutex);

            
            GlobalData::data1.inp_sem[i].read_count += 1;

          if( GlobalData::data1.inp_sem[i].read_count == 1 )
            	sem_wait(&GlobalData::data1.inp_sem[i].rw_mutex);


            sem_post(&GlobalData::data1.inp_sem[i].mutex);

            ///Perform Reading //

            //for(int counter = 0 ; counter < hiddenLayerSize ; counter ++){

           // int location = i % hiddenLayerSize;
            //cout << " i =" << i << " neuron num  = " << neuron_num << endl;
            //cout<<"Location = " << location << endl;
    
            FNeuron* n1 =  &this->prevLayer[0];
            FNeuron* n2 =  &this->prevLayer[1];
            FNeuron* n3 =  &this->prevLayer[2];

            double w1 = n1->outputWeights[neuron_num].weight;
            double w2 = n2->outputWeights[neuron_num].weight;
            double w3 = n3->outputWeights[neuron_num].weight;
            
            cout << "I am neuron " << neuron_num << " and my bias value is : " << bias << endl;
            cout<<" w1 = " <<  w1 << endl; 
             cout<<" w2 = " << w2 << endl;
             cout<<" w3 = " << w3 << endl;

            double d1 = GlobalData::data1.input[i][0];
            double d2 = GlobalData::data1.input[i][1];
            double d3 = GlobalData::data1.input[i][2];

            cout<< " d1  = " << d1 << " d2 = "<< d2 <<" d3 = "<<d3 << endl;

            double res = calcResult(d1, d2, d3, w1, w2, w3);

            cout << " res is : "<< res << endl;

            //GlobalData::data1.firstLayerOut[location] = res;*/
            calculated[i] = true;

            
            //This Neuron has done its part on data number i
            ///The semaphore on data set number #i gets incrementer
            ///Until its value becomes 1 , the initial value is 10 (num of hidden layer neurons)
            ///This means that all hidden neurons have done their part on data set number #i
            cout<<"size of hidden_sem "<< GlobalData::data1.hidden_sem.size() << endl;
            cout<<" i = " <<i << endl;
            //sem_post(&GlobalData::data1.hidden_sem[i].rw_mutex); 


            //End of Reading
       // }


            

            sem_wait(&GlobalData::data1.inp_sem[i].mutex);
            GlobalData::data1.inp_sem[i].read_count += -1;

            if(GlobalData::data1.inp_sem[i].read_count == 0)  
            	sem_post(&GlobalData::data1.inp_sem[i].rw_mutex);

            sem_post(&GlobalData::data1.inp_sem[i].mutex);

		}
	}


}


void ONeuron::runNeuron(int neuron_num){




    /// A vector of size #num_of_inputs 
	vector<bool> calculated (GlobalData::data1.input.size(), -100);

	int hiddenLayerSize = GlobalData::data1.hiddenLayerSize;
	int num_of_outputs = GlobalData::data1.firstLayerOut.size();

	/// i changes form 0 to #num_of_inputs 

	for(int i = 0 ; i < calculated.size(); i++){

		sem_wait(&GlobalData::data1.hidden_sem[i].mutex);
		GlobalData::data1.hidden_sem[i].read_count += 1;

		if(GlobalData::data1.hidden_sem[i].read_count == 1)
			sem_wait(&GlobalData::data1.hidden_sem[i].rw_mutex);

		sem_post(&GlobalData::data1.hidden_sem[i].mutex);

		//////////Start Reading


        double res = calcResult(i);

        cout << " Output for data #" << i << res << endl;




		////Stop Reading
		sem_wait(&GlobalData::data1.hidden_sem[i].mutex);
		GlobalData::data1.hidden_sem[i].read_count += -1;

		if(GlobalData::data1.hidden_sem[i].read_count == 0)
			sem_post(&GlobalData::data1.hidden_sem[i].rw_mutex);

		sem_post(&GlobalData::data1.hidden_sem[i].mutex);



	}




}

double HNeuron::calcResult(double x, double y, double z , double w1, double w2, double w3){

	return tanh(x*w1 + y*w2 + z*w3 + this->bias);


}

double ONeuron::calcResult(int i){

	int hiddenLayerSize = GlobalData::data1.hiddenLayerSize;

	double output = 0;


	for(int counter = 0 ; counter < hiddenLayerSize ; counter ++ ){

		int location = counter * hiddenLayerSize + i ;
		int weight = this->prevLayer[i].outputWeights[0].weight;

		output += GlobalData::data1.firstLayerOut[i] * weight;
	}

	output += this->bias;

	return output;



}

void HNeuron::setPrevLayerRefrence(const Layer1& ref){

	prevLayer = ref;
	cout<<" Hello From HNeuron and prev layer size is :" << prevLayer.size();
	
}

void ONeuron::setPrevLayerRefrence(const Layer2& ref){

	prevLayer = ref;
	cout<<" Hello From ONeuron and prev layer size is :" << prevLayer.size();
}
