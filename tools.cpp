#include "tools.h"


using namespace std;

int seed;
int num_of_inputs;

vector<string> split(string statement, char delimeter) {

  vector<string> result;
  string token;

  for (int i = 0; i < statement.length(); i++)
    if (statement[i] != delimeter)
      token += statement[i];
    else if (token.length()) {
      result.push_back(token);
      token = "";
    }

  if (token.length())
    result.push_back(token);
  return result;
}

double fRand(double fMin, double fMax)
{
   
    double f = (double)rand() / RAND_MAX;
    //srand (time(NULL));
    return fMin + f * (fMax - fMin);
}

string itos(int number) {
  ostringstream oss;
  oss << number;
  return oss.str();
}

int mystoi(string number) {
  int n;
  stringstream ss;
  ss << number;
  ss >> n;
  return n;
}


void set_global_vector_size(){

  GlobalData::data1.set_input_size(num_of_inputs);
  GlobalData::data1.set_firstLayerOut_size(num_of_inputs);
  GlobalData::data1.set_inpsem_size(num_of_inputs);
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

  for(int i = 0; i<num_of_inputs; i++){

    double out = fRand(0,50);
    write_on_file(addr, out);
  }
}

void get_num_of_inputs(){

 cout<<" Enter the number of input you wanna generate."<<endl;
 cin >> num_of_inputs;

}

void get_seed(){

    cout<<"Enter seed for random generation" << endl;
    cin >> seed;
  }

void init(){

  get_seed();
  srand(seed);
  get_num_of_inputs();
  set_global_vector_size();

  generate_input("./0.txt");
  generate_input("./1.txt");
  generate_input("./2.txt");
}



