all: net

net: net.cpp net.h neuron.o globaldata.o tools.o mysemaphore.h
	g++ net.cpp neuron.o globaldata.o tools.o -lpthread -o net && echo success

neuron.o : neuron.cpp neuron.h globaldata.h object.h tools.h mysemaphore.h
	g++ -c  neuron.cpp

globaldata.o: globaldata.cpp globaldata.h object.h mysemaphore.h
	g++ -c globaldata.cpp 

tools.o: tools.cpp tools.h globaldata.h 
	g++ -c tools.cpp 


clean:
	rm  -f 0.txt 1.txt 2.txt *.o *.out net
