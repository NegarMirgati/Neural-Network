#include "main.h"
#include "net.h"

int seed;

using namespace std;

double fRand(double fMin, double fMax)
{
	 
    double f = (double)rand() / RAND_MAX;
    //srand (time(NULL));
    return fMin + f * (fMax - fMin);
}

void write_on_file(string addr, double data){

  ofstream myfile;
  myfile.open(addr.c_str(), ios_base::app);

  if (myfile.is_open())
  	myfile << data << " ";
  else
  	exit(0);

  myfile.close();
  
}


void generate_input(string addr){

	for(int i = 0; i<50 ; i++){

		double out = fRand(0,50);
		write_on_file(addr, out);
	}
}

void get_seed(){

    cout<<"Enter seed for random generation" << endl;
    cin >> seed;
  }

void init(){

  get_seed();
  srand(seed);
  generate_input("./x.txt");
  generate_input("./y.txt");
  generate_input("./z.txt");
}



int main(){

  init();
  vector<unsigned> topology;
  topology.push_back(3);
  topology.push_back(10);
  topology.push_back(1);
  Net mynet(topology);

  
}