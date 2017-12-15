#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>
#include <vector>
#include <string>
#include <semaphore.h>
#include "mysemaphore.h"

struct Object{

	std::vector<mysem_t> inp_sem;
	std::vector<mysem_t> hidden_sem;

	std::vector<std::vector<double> > input;
	std::vector<double> firstLayerOut;
	std::vector<double> secondLayerOut;

	int hiddenLayerSize;

	void set_input_size(int size){

		input.resize(size); 

		std::cout << "******************************************************\n";

		std::cout<< " Resizing input to size " << size << "\n";

		std::cout << "******************************************************\n";


		for( int i = 0 ; i < size ; i++){

			input[i].resize(3, -100);        
		}


	}

	void  set_firstLayerOut_size( int size ){
		std::cout << "******************************************************\n";

		std::cout<< " Resizing firstLayerout_size to size " << size * hiddenLayerSize << "\n";

		std::cout << "******************************************************\n";

		firstLayerOut.resize( hiddenLayerSize * size , -100 ); 
		/// -100 for detecting wether the location has been used before or not         
	}

	void set_inpsem_size(int size){

		std::cout << "******************************************************\n";

		std::cout<< " Resizing inp_sem to size " << size << "\n";

		std::cout << "******************************************************\n";

		inp_sem.resize(size); 

		for( int i = 0 ; i < inp_sem.size() ; i++){

					sem_init(&inp_sem[i].rw_mutex, 0, -2);
					sem_init(&inp_sem[i].mutex, 0, 1);
					inp_sem[i].read_count = 0;
			}

	}

	void set_hiddensem_size(int size){


		std::cout << "******************************************************\n";

		std::cout<< " Resizing hidden_sem to size " << size << "\n";

		std::cout << "******************************************************\n";

		hidden_sem.resize(size); 

		std::cout<<"hidden sem size is" << hidden_sem.size()<<std::endl; 

		for( int i = 0 ; i < hidden_sem.size() ; i++){

					sem_init(&hidden_sem[i].rw_mutex, 0, 0);
					sem_init(&hidden_sem[i].mutex, 0, 1);
					hidden_sem[i].read_count = 0;
			}



	}

};



#endif