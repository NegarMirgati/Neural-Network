#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>
#include <vector>
#include <string>
#include <semaphore.h>
#include "mysemaphore.h"

struct Object{

	std::vector<std::vector<mysem_t> > inp_sem;

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

		for( int i = 0 ; i < size ; i++){

				inp_sem[i].resize(3);
				for( int j = 0 ; j < 3 ; j++){
					sem_init(&inp_sem[i][j].rw_mutex, 0, 1);
					sem_init(&inp_sem[i][j].mutex, 0, 1);
					inp_sem[i][j].read_count = 0;
				}
			}

	}

};



#endif