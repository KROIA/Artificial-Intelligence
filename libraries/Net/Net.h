/*
Net 	REMAKE
Autor 		Alex Krieg
Version 	0.3
Datum		11.10.2017
*/
#ifndef NET_H
#define NET_H

#include <iostream>
#include <math.h>
#include <random>
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

#define DEBUG
//#define DEBUG2

using namespace std;

class Neuron
{ 
	public:
								Neuron(int anzInputs,bool enaAver);
								~Neuron();
	
	void 						setInput(vector<float> signal);
	float 						getOutput();
	float 						getWeightOnPos(int weightPos);
	void 						setWeightOnPos(int weightPos,float _weight);
	void 						setWeight(vector<float> _weight);
	vector<float>				getWeight();
	private:
	
	vector<float>				weight;
	float 						output;
	int 						inputs;
	bool 						enableAverage;
	default_random_engine 		randEngine;
	#ifdef DEBUG
	void 						handleError(int _ERROR,int zusatz = 0);
	#endif
};
/*
ERROR CODE:
1	->	netInput(vector<float> signal) signal.size() != Neuron::inputs
2	->	getWeightOnPos(int weightPos) weightPos.size() <> Neuron::inputs"
3	->	setWeightOnPos(int weightPos,float _weight) weightPos <> Neuron::inputs
4	->	setWeight(vector<float> _weight) _weight.size() != Neuron::inputs"

*/

class Net
{
	public:
								Net(int in,int hidX,int hidY,int out,int ani,float fac,bool _bias,bool enaAver = true);
								~Net();
	
	void 						saveData(string name);
	void						loadData(string name);
	void 						setInput(vector<float> signal);
	void 						setInputOnPos(int pos,float signal);
	vector<float>				getOutput();
	void						learn(vector<float> fitness);
	void						setGenomOfAnimal(int animal,vector<float> _genom);
	void						setGenom(vector<vector<float>	> _genom);
	vector<float>				getGenomOfAnimal(int ani);
	vector<vector<float>	>	getGenom();
	void 						run(int aditionalAnimal = 0);
	void 						setMutationValue(float val);
	unsigned int 				getGenomSize();
				
	vector<vector<Neuron>	>	hiddenLayer;			
	vector<Neuron>				outputLayer;
	
	private:
	void 						loadGenomOfAnimal();
	bool 						checkForWrongParam();
	FILE 					   *file;			
	vector<vector<float>	>	genom;
	vector<float>				input;
	vector<float>				output;
	int 						genomSize;				
	int 						inputs;
	int							hiddenX;		// x = nach rechts
	int							hiddenY;		// y = nach unten
	int							outputs;		
	unsigned int				mutFactor;
	int 						animals;
	int 						currentAnimal;
	bool 						bias;
	int 						mutationChangeDivisor;
	bool 						enableAverage;
	default_random_engine 		randEngine;
	#ifdef DEBUG
	void 						handleError(int _ERROR,int zusatz = 0);
	#endif
};
#endif