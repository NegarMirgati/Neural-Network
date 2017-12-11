#include "net.h"

using namespace std;


Net::Net(const vector<unsigned>& _topology){

	this->topology = _topology;


}


void Net::feedForward(){

}


void Net::startNet(){



}


void Net::startFirstLayer(){


 /* for(int i = 0 ; i < layers[0].size() ; i++){

    layers[0][i].startNeuron();
  }*/
}

void Net::testGlobal(){

  //GlobalData::data1.input.push_back(1);
  //cout<<" Global Data updateed " << GlobalData::data1.input.back()<<endl;
}


void Net::buildNet(){

	int numLayers =  topology.size();
	for(int i = 0; i  < numLayers ; i++){


    cout<<" Layer number "<< i << endl;

		layers.push_back(Layer());
		unsigned numOutputs = (i == topology.size() - 1) ? 0 : topology[i + 1];

		// We have added a new layer
		//now fill its neurons

		/*for(int j = 0; j< topology[i] ; j++){

      vector<double> weights;

			if(i == 0){

				

				for(int k = 0 ; k < firstLayerWeights.size() ; k++ ){

					weights.push_back(atof(firstLayerWeights[k][j].c_str()));

				}
      }

      else if( i == 1){

        

          weights.push_back(atof(secondLayerWeights[j].c_str()));


      }


        Neuron myn;
        myn.setWeights(numOutputs, weights);
				layers.back().push_back(myn);

			}*/


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
  topology.push_back(10);
  topology.push_back(1);
  init();
  Net mynet(topology);
  mynet.getLayersInfoAddr();
  mynet.readFirstLayerWeights();
  mynet.readSecondLayerWeights();
  mynet.buildNet();
  

  
}


