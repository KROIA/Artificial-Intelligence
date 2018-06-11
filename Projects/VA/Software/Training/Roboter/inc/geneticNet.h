/*
Autor 		Alex Krieg
Version 	0.3.1
Datum		25.11.2017
*/
#ifndef GENETIC_NET
#define GENETIC_NET
//-------------------------------
#define GENETIC_NET_VERSION 0	
//-------------------------------
#include "Net.h"



class geneticNet	:	public Net
{
	public:
	geneticNet(int in,int hidX,int hidY,int out,int ani,float fac,bool _bias,bool enaAver = false);
	~geneticNet();
	
	void 						mutationFactor(float fac);
	float						mutationFactor();
	
	bool 						saveData(string name);
	int							loadData(string name);
	void						learn(vector<float> fitness);
	void						genom(vector<vector<float>	> _Genom);
	void						genom(int animal,vector<float> _Genom);
	vector<float>				genom(int ani);
	vector<vector<float>	>	genom();
	void 						mutationDivisor(float val);
	float						mutationDivisor();
	string 						networkConfiguration();
	void 						animal(unsigned int animalNr);
	unsigned int				animal();
	private:
	void 						loadGenomOfAnimal();
	bool 						checkForWrongParam();
	#ifdef DEBUG
	void 						handleError(int _ERROR,int zusatz = 0);
	#endif
	vector<vector<float>	>	_genom;
	int 						animals;
	unsigned int 				currentAnimal;
	unsigned int				mutFactor;
	float 						mutationChangeDivisor;
	string 						_GENETIC_NET_VERSION;
	string 						_networkConfiguration;
};

#endif
