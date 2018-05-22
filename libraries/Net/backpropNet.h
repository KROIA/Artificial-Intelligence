/*
Autor 		Alex Krieg
Version 	0.0
Datum		7.11.2017
*/
#ifndef BACKPROP_NET
#define BACKPROP_NET
//-------------------------------
#define BACKPROP_NET_VERSION 0
//-------------------------------
#include "Net.h"
//#include "Net.cpp"

class backpropNet	:	public Net
{
	public:
	backpropNet(int in,int hidX,int hidY,int out,float fac,bool _bias);
	~backpropNet();
	
	bool 						saveData(string name);
	int							loadData(string name);
	void 						learn(vector<float> expected);
	void 						genom(vector<float> _Genom);			
	vector<float>				genom();			
	string 						networkConfiguration();
	float 						error();
	float 						error(int out);
	private:	
	void 						loadGenom();
	bool 						checkForWrongParam();
	#ifdef DEBUG
	float						abl(float netinput);
	void 						handleError(int _ERROR,int zusatz = 0);
	#endif
	vector<float>				_genom;
	float						mutFactor;
	string 						_BACKPROP_NET_VERSION;
	string 						_networkConfiguration;
	vector<float>				_outputError;
	bool 						_manuellOutputError;
};
#endif