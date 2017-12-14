#include "net.h"

using namespace std;

pthread_t *layer1_threads, *layer2_threads, *layer3_threads; 


Net::Net(const vector<unsigned>& _topology){

	this->topology = _topology;


}


void Net::feedForward(){

}


void Net::startNet(){



}

void *helper_runFN(void* args){

  runFN_args *ptr = (runFN_args*) args;

  FNeuron* nptr = ptr->ptr ;
  //cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  //cout<<"running neuron " << ptr->neuron_num;
  nptr-> runNeuron(ptr->neuron_num);

  //cout <<" hello world!!!! " <<ptr->neuron_num<< endl;
 

}


void Net::startFirstLayer(){

 pthread_t myThread1[l1.size()];
 pthread_t myThread2[l2.size()];
 pthread_t myThread3[l3.size()];

 layer1_threads = myThread1;
 layer2_threads = myThread2;
 layer3_threads = myThread3;
  void* ret_join;


for(int i = 0 ; i < l1.size() ; i++){

  int neuron_num = i;


  //cout<<"size of l1 " << l1.size() << endl;

  FNeuron* ptr = &l1[i];

  runFN_args* args = new runFN_args();
  args->ptr = ptr;
  args->neuron_num = neuron_num;

  pthread_create(&layer1_threads[i], 0, helper_runFN, args);
  //write(STDOUT_FILENO,"^&^&^&^&^&^&^&^&^&^&^&^&^&^&^&\n", 25);



  }

  for(int k = 0 ; k<3 ; k++)
      pthread_join(layer1_threads[k], &ret_join);


}


void Net::buildNet(){

	//int numLayers =  topology.size();
	for(int i = 0; i  < 3 ; i++){


    cout<<" Layer number "<< i << endl;

		//layers.push_back(Layer());
		unsigned numOutputs = (i == topology.size() - 1) ? 0 : topology[i + 1];

		// We have added a new layer
		//now fill its neurons

		for(int j = 0; j< topology[i] ; j++){

      vector<double> weights;

			if(i == 0){

				

				for(int k = 0 ; k < firstLayerWeights.size() ; k++ ){

					weights.push_back(atof(firstLayerWeights[k][j].c_str()));

				}

        FNeuron myn;
        myn.setWeights(numOutputs, weights);
        l1.push_back(myn);
      }

      else if( i == 1){

        

          weights.push_back(atof(secondLayerWeights[j].c_str()));

          HNeuron myn;
          myn.setWeights(numOutputs, weights);
          l2.push_back(myn);


      }

      else if ( i == 2){


        ONeuron myn;
        myn.setWeights(numOutputs, weights);
        l3.push_back(myn);

      }            

			}


		}

		
	}



void Net::getLayersInfoAddr(){

	cout<< " Enter the LayersInfo file address"<<endl;
	cin >> layersInfoAddr;
}


void Net::readFirstLayerWeights(){

  ifstream myfile;
  string line;
  myfile.open(layersInfoAddr.c_str(), ios_base::app);

  if (myfile.is_open()){


  	while( getline(myfile, line) ){

  		if(line == "IW1:(weights of input neurons to hidden neurons)"){
  			cout<<"here"<<endl;

  			string weights;
  			
  			int i = 0;

  			while(true){

  				
  				getline(myfile, weights);
  				if(weights == "b2:(bias of output neuron)")
  					break;
  				cout<<"i = " << i++ << endl;
  				cout << weights << endl;
  				vector<string> tokens = split(weights, ' ');

  				firstLayerWeights.push_back(tokens);

  				


  			}

  		}
  	}


  }
  	
  else
  	exit(0);

  myfile.close();

}

void Net::readSecondLayerWeights(){

	ifstream myfile;
  string line;
  myfile.open(layersInfoAddr.c_str(), ios_base::app);

  if (myfile.is_open()){


  	while( getline(myfile, line) ){

  		if(line == "LW2:(weights of hidden neurons to output neuron)"){
  			cout<<"----------------------------------------------------------"<<endl;

  			string weights;
  			int i = 0 ;

  			while(myfile >> weights){

  				cout<<" k = "<< i++ <<endl;
      
  				
  				cout << weights << endl;
  				
  					secondLayerWeights.push_back(weights);
  				
  			}

  		}
  	}


  }
  	
  else
  	exit(0);

  myfile.close();


}

int main(){

  
  vector<unsigned> topology;
  topology.push_back(3);

  cout<<"herere" << endl;

  cout << "Enter the number of hidden Layer Neurons" << endl;
  int num; 
  cin >> num;

  topology.push_back(num);

  //set the hidden layer size in global data

  GlobalData::data1.hiddenLayerSize = num ;


  //init();
  Net mynet(topology);
  mynet.getLayersInfoAddr();

  init(); 

  mynet.readFirstLayerWeights();
  mynet.readSecondLayerWeights();
  mynet.buildNet();
  mynet.startFirstLayer();
  mynet.printarr();

  

  
}



void Net::printarr(){

  for(int i  = 0 ; i < GlobalData::data1.input.size() ; ++i)
  {
    for(int j = 0 ; j < 3 ; j ++)
      cout << GlobalData::data1.input[i][j] << " ";
    cout<<endl;
  }
}


