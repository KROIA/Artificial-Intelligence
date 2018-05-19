/*
Net 	REMAKE
Autor 		Alex Krieg
Version 	1.2.1
Datum		25.11.2017
*/
#ifndef NET_H
#define NET_H
//-------------------------------
#define NET_VERSION 0
//-------------------------------
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
	
	void 						input(vector<float> signal);
	float 						output();
	float 						weight(int weightPos);
	void 						weight(int weightPos,float __weight);
	void 						weight(vector<float> __weight);
	vector<float>				weight();
	float 						netInput();
	private:
	
	vector<float>				_weight;
	float 						_netInput;
	float 						_output;
	int 						inputs;
	bool 						enableAverage;
	default_random_engine 		randEngine;
	#ifdef DEBUG
	void 						handleError(int _ERROR,int zusatz = 0);
	#endif
};


class Net
{
	public:
								Net(int in,int hidX,int hidY,int out,bool _bias,bool enaAver = false);
								~Net();
	void 						input(vector<float> signal);
	void 						input(int pos,float signal);
	vector<float>				input();
	float						input(int pos);
	vector<float>				output();
	float						output(int pos);
	void 						weightOfNet(vector<float> weight);
	vector<float>				weightOfNet();
	void 						run();
	unsigned int 				genomSize();
				
	vector<vector<Neuron>	>	hiddenLayer;			
	vector<Neuron>				outputLayer;
	
	bool 						_checkForWrongParam();
	
	FILE 					   *file;			
	vector<float>				_input;
	vector<float>				_output;
	
	int 						_weightSize;				
	int 						inputs;
	int							hiddenX;		// x = nach rechts
	int							hiddenY;		// y = nach unten
	int							outputs;		
	bool 						bias;
	bool 						enableAverage;
	default_random_engine 		randEngine;
	string						_NET_VERSION;
	
	private:
	vector<float>				weight_net;
#ifdef DEBUG
void 						_handleError(int _ERROR,int zusatz = 0);
#endif
};
#endif