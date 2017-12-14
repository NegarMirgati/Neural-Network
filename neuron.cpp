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
        
		//sem_wait( &GlobalData::data1.inp_sem[counter][neuron_num].rw_mutex );
		//cout<<"updating value of" << neuron_num << " row " << counter << endl ;
		//write(STDOUT_FILENO, temp.c_str(), temp.size());
		GlobalData::data1.input[counter][neuron_num] = atof(line.c_str());
		sem_post( &GlobalData::data1.inp_sem[counter][neuron_num].rw_mutex);
		counter++;

	}
	
}

bool readcount_is_zero(int i){

	if(GlobalData::data1.inp_sem[i][0].read_count == 0 &&
           	   GlobalData::data1.inp_sem[i][1].read_count == 0 &&
               GlobalData::data1.inp_sem[i][2].read_count == 0)
		return true;
	return false;
}

void wait_mutex(int i){

	        sem_wait(&GlobalData::data1.inp_sem[i][0].mutex);
            sem_wait(&GlobalData::data1.inp_sem[i][1].mutex);
            sem_wait(&GlobalData::data1.inp_sem[i][2].mutex);
}

void wait_rw_mutex(int i){

			sem_wait(&GlobalData::data1.inp_sem[i][0].rw_mutex);
            sem_wait(&GlobalData::data1.inp_sem[i][1].rw_mutex);
            sem_wait(&GlobalData::data1.inp_sem[i][2].rw_mutex);

}

void signal_mutex(int i){

			sem_post(&GlobalData::data1.inp_sem[i][0].mutex);
            sem_post(&GlobalData::data1.inp_sem[i][1].mutex);
            sem_post(&GlobalData::data1.inp_sem[i][2].mutex);
}
void signal_rw_mutex(int i){

			sem_post(&GlobalData::data1.inp_sem[i][0].rw_mutex);
            sem_post(&GlobalData::data1.inp_sem[i][1].rw_mutex);
            sem_post(&GlobalData::data1.inp_sem[i][2].rw_mutex);
}
void incdec_readcount(int i, int val){

	        GlobalData::data1.inp_sem[i][0].read_count += val;
            GlobalData::data1.inp_sem[i][1].read_count += val;
            GlobalData::data1.inp_sem[i][2].read_count += val;
}

bool readcount_is_one(int i){

	if(GlobalData::data1.inp_sem[i][0].read_count &&
           	   GlobalData::data1.inp_sem[i][1].read_count &&
               GlobalData::data1.inp_sem[i][2].read_count)
		return true;
	return false;
}

void HNeuron::runNeuron(int neuron_num){

	//cout<<"Hello khare badbakht"<<endl;

	vector <bool> calculated (GlobalData::data1.input.size(), false);

	for( int i = 0; i < calculated.size() ; i++){

		if( calculated[i] == false ){

			int hlayersize = GlobalData::data1.hiddenLayerSize;
            int location = neuron_num * GlobalData::data1.hiddenLayerSize + i;

            wait_mutex(i);

            cout<<"AA"<<endl;

            int val = 1;
            incdec_readcount(i, val);

            if(readcount_is_one(i))
            	wait_rw_mutex(i);

            cout<<"BB "<< endl;

            signal_mutex(i);
            //cout<<"Neuron number "<< neuron_num << " ";
            //write(STDOUT_FILENO, "khar\n", 5);
            //write(STDOUT_FILENO, itos(neuron_num).c_str(), 2);
            //cout << GlobalData::data1.input[i][0] << " " << GlobalData::data1.input[i][1] <<" "<< GlobalData::data1.input[i][2] << endl;
            calculated[i] = true;

            wait_mutex(i);
            incdec_readcount(i, -1);

            if(readcount_is_zero(i))
            	signal_rw_mutex(i);

            signal_mutex(i);


            //sem_wait(&GlobalData::data1.inp_sem[i][0].rw_mutex);
			///calc
			//i = 0;
			//continue;
		}
	}

	//cout<<" Bye Bye khare Badbakht" << endl;



}


void ONeuron::runNeuron(int neuron_num){


}
