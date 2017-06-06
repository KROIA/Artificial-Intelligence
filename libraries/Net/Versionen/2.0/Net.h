//Autor Alex Krieg
//V2.1							
//30.5.2017

//----------SETTINGS		//Nur eines von beiden definieren
#define genetic
//#define backprop
//------------------
#ifndef NET_H
#define NET_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <vector>
#include <math.h>

using namespace std;



struct In{
  float weight;
  float last_weight;
  float data;
};
class Neuron;
class Net;
class Neuron
{
public:
	Neuron();
	~Neuron();
	void setup(int in,float fac);
	void setInput(float DATA[]);
	float getOutput();
	void calculateError(float nextError[],int anzPins);	//Array aus allen von vorne kommenden Errors*gewichte
	float getErrorBack(int input);						//durch welchen Input der Error gehen soll
	In *inputs;
	float error;
	void changeWeights(float NetError);
	
private:
	int a;
	int b;
	int c;
	int d;
	
	float factor;
	float result;
	int anzInputs;
};

class Net
{
public:
	#ifdef genetic 
			#endif
	#ifdef backprop
		Net(int inputs,int hiddenX,int hiddenY,int outputs,float fac);	//X -> Neurons/Layer Y-> anz hidden Layer
		float getOutput(int out);
		void learn(float expactet[],int improve);
		void setInputUnits(float input[]);
	#endif
	#ifdef genetic
		Net(int inputs,int hiddenX,int hiddenY,int outputs,int ani,float mutat);	//X -> Neurons/Layer Y-> anz hidden Layer
		float getOutput(int animal,int out);
		void learn(float AnimalFitness[]);
		void setInputUnits(float input[],int animal);
		vector<float>  getGen(int genNR);
		void setGen(int genNR,vector<float> genData);
		
	#endif
	~Net();
	
	void loadData(char * file);
	void saveData(char * file);
	
	float *FullOut;
	void debug();
	float netError;
	unsigned long steps;
private:

	FILE * Myfile;
	int a;
	int b;
	int c;
	int d;
	int e;
	float factor;
	int inputUnits;
	int hiddenUnitsX; 
	int hiddenUnitsY;
	int outputUnits;
	
	vector<vector<Neuron>	> HiddenLayers;
	Neuron *OutputLayer; 
	
	#ifdef genetic 
	unsigned int animals;
	unsigned int geneticSize;
	vector<vector<float>	> Genetic;
	vector<vector<float>	> FullOutOfAnimal;
	float fitness;
	unsigned int mutationRate;
	
	int C1; 
	int C2;
	int C3;
	#endif
};

#endif