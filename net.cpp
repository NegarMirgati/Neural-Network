#include "net.h"

using namespace std;

Net::Net(const vector<unsigned>& _topology){

	this->topology = _topology;

}

void Net::startNet(){

   pthread_t myThread1[l1.size()];
   pthread_t myThread2[l2.size()];
   pthread_t myThread3[l3.size()];
   void* ret_join;

   startFirstLayer(myThread1);
   startSecondLayer(myThread2);
   //startOutputLayer(myThread3);

   for(int i = 0 ; i < l2.size() ; i++){
      pthread_join(myThread2[i], &ret_join);
      cout<<"Thread "<< i << "exited"<<endl;
    }

   for(int i = 0 ; i < l1.size() ; i++)
      pthread_join(myThread1[i], &ret_join);


    cout<<"HERRRREEEEE"<<endl;

    cout<<"BYE BYE"<<endl;

    /*for(int i = 0 ; i < l3.size() ; i++){
      pthread_join(myThread3[i], &ret_join);
      cout<<"Thread output "<< i << "exited"<<endl;
    }*/

}

void *helper_runFN(void* args){

  runFN_args *ptr = (runFN_args*) args;

  FNeuron* fn_ptr = ptr->ptr ;

  fn_ptr-> runNeuron(ptr->neuron_num); 

}

void* helper_runHN(void* args){

   runHN_args *ptr = (runHN_args*) args;

  HNeuron* hn_ptr = ptr->ptr ; 
  hn_ptr-> runNeuron(ptr->neuron_num);


}

void* helper_runON(void* args){

   runON_args *ptr = (runON_args*) args;

  ONeuron* on_ptr = ptr->ptr ; 
  on_ptr-> runNeuron(ptr->neuron_num);

}


void Net::startFirstLayer(pthread_t* myThread1){


for(int i = 0 ; i < l1.size() ; i++){

  int neuron_num = i;


  //cout<<"size of l1 " << l1.size() << endl;

  FNeuron* ptr = &l1[i];

  runFN_args* args = new runFN_args();
  args->ptr = ptr;
  args->neuron_num = neuron_num;

  pthread_create(&myThread1[i], 0, helper_runFN, args);
 

  }

}


void Net::startSecondLayer(pthread_t* myThread2){

  for(int i = 0; i < l2.size() ; i++){

    int neuron_num = i;

    HNeuron* my_ptr = &l2[i];

    runHN_args* args = new runHN_args();
    args->ptr = my_ptr;
    args->neuron_num = neuron_num;
    pthread_create(&myThread2[i], 0, helper_runHN, args);

    

  }



}

void Net::startOutputLayer(pthread_t* myThread3){

  for(int i = 0 ; i < l3.size() ; i++){

    int neuron_num = i;
    ONeuron* ptr = &l3[i];

    runON_args* args = new runON_args();
    args->ptr = ptr;
    args->neuron_num = neuron_num;
    pthread_create(&myThread3[i], 0, helper_runON, args);


  }

}


void Net::readSecondLayerBias(){

  ifstream myfile;
  string line;
  int counter = 0;
  myfile.open(layersInfoAddr.c_str(),  ios_base::app);
  getline(myfile, line);

  while(line != "b1:(bias of hidden neurons)")
    getline(myfile, line);

  /////////Setting
  getline(myfile, line);

  while(line != "IW1:(weights of input neurons to hidden neurons)"){

    cout<<"bias is "<< line << endl;
    cout<<"Neuron Num is "<< counter << endl;

    l2[counter].setBias(atof(line.c_str()));

    getline(myfile, line);

    counter++;
  }

  myfile.close();

}

  void Net::readOutputLayerBias(){

    ifstream myfile;
    string line;

    cout<<" size of l3 "<<l3.size()<<endl;
    myfile.open(layersInfoAddr.c_str(), ios_base::app);
    getline(myfile, line);

    while(line != "b2:(bias of output neuron)")
      getline(myfile, line);

    getline(myfile,line);
    l3[0].setBias(atof(line.c_str()));

    myfile.close();

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
          myn.setPrevLayerRefrence(l1);
          l2.push_back(myn);


      }

      else if ( i == 2){

        cout<<" making layer 3"<< endl;
        ONeuron myn;
        myn.setWeights(numOutputs, weights);
        myn.setPrevLayerRefrence(l2);
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

  topology.push_back(1);

  //set the hidden layer size in global data

  GlobalData::data1.hiddenLayerSize = num ;


  //init();
  Net mynet(topology);
  mynet.getLayersInfoAddr();

  init(); 

  mynet.readFirstLayerWeights();
  mynet.readSecondLayerWeights();

  mynet.buildNet();

  mynet.readSecondLayerBias();
  mynet.readOutputLayerBias();


  mynet.startNet();
  //mynet.printarr();

  return 0;

  

  
}



void Net::printarr(){

  for(int i  = 0 ; i < GlobalData::data1.input.size() ; ++i)
  {
    for(int j = 0 ; j < 3 ; j ++)
      cout << GlobalData::data1.input[i][j] << " ";
    cout<<endl;
  }
}


double calcRealOutputs(double d1, double d2, double d3){

  /*double result = -1*in2;
  double res1 = sqrt( abs( pow(d2,2) - 4*d1*d3 ) );
  double res2 = 2*d1 + sin(d1 * M_PI);

  result += res1/res2;*/

  return 1.12;



}


