/*
Net 	REMAKE
Autor 		Alex Krieg
Version 	1.2.1
Datum		25.11.2017
*/
#include "Net.h"


//--------------------------NEURON--------------------------
				Neuron::Neuron(int anzInputs,bool enaAver){
	#ifdef DEBUG2
	printf("Neuron::Neuron\n");
	#endif
	inputs					= anzInputs;
	randEngine				= default_random_engine(rand()%500);
	_weight					= vector<float>	(inputs,(randEngine()%1000)/1000);
	enableAverage			= enaAver;
	#ifdef DEBUG2
	printf("Neuron::Neuron->inputs:%i %i\n",inputs,_weight.size());
	#endif
}
				Neuron::~Neuron(){
	//_weight.clear();
}
void 			Neuron::input(vector<float> signal){
	
	#ifdef DEBUG2
	printf("Neuron::input\n");
	#endif
	if(signal.size() == inputs)
	{
		_netInput = 0.0;
		for(int a = 0; a<inputs; a++)
		{
			_netInput += signal[a] * _weight[a];		//Berechnet den Netzinput
		}
		if(enableAverage)
		{
			_netInput /= _netInput;						//Erstellt den Durchschnitt daraus um eine
		}												//flachere Aktivierung der Sigmoid Funktion zu erreichen
		
													
		_output = ((1.0/(1.0+exp(-_netInput)))-0.5)*2;	//Aktivierungs Funktion 
		/*
		___________________________________
		|								  |		--|
		|	                     OOOOOOOOO|	  1.0 |
		|                    OOOO         |	      |
		|                 OO              |	      |
		|                O                |	    0 |- Output
		|              OO                 |	      |
		|         OOOO                    |	      |
		|OOOOOOOOO						  |  -1.0 |
		|_________________________________|		--|
		
		 ... -5		-1	  0    1      5 ...  
		|								   |
		|-----------------|----------------|
					      |
					  netInput
		*/
	}
	#ifdef DEBUG
	else
	{
		handleError(1,signal.size());
		printf("inputs: %i\n",inputs);
	}
	#endif
}
float 			Neuron::output(){
	#ifdef DEBUG2
	printf("Neuron::output\n");
	#endif
	return _output;
}
float 			Neuron::weight(int weightPos){
	#ifdef DEBUG2
	printf("Neuron::weight\n");
	#endif
	if(weightPos<inputs && weightPos>-1)
	{
		#ifdef DEBUG2
		printf("->_weight.size()= %i \n",_weight.size());
		printf("Neuron::Neuron->inputs:%i %i\n",inputs,_weight.size());
		#endif
		return _weight[weightPos];
	}
	#ifdef DEBUG
	else
	{
		handleError(2,weightPos);
		printf("Neuron::inputs = %i\n",inputs);
	}
	#endif
	return 0;
}
void 			Neuron::weight(int weightPos,float __weight){
	#ifdef DEBUG2
	printf("Neuron::weight(int weightPos,float __weight)\n");
	#endif
	if(weightPos<inputs && weightPos>-1)
	{
		_weight[weightPos] = __weight;
	}
	#ifdef DEBUG
	else
	{
		handleError(3,weightPos);
		printf("Neuron::inputs = %i\n",inputs);
	}
	#endif
}
void 			Neuron::weight(vector<float> __weight){
	#ifdef DEBUG2
	printf("Neuron::weight\n");
	#endif
	if(_weight.size() == inputs)
	{
		_weight = __weight;
	}
	#ifdef DEBUG
	else
	{
		handleError(4,_weight.size());
		printf("Neuron::inputs = %i\n",inputs);
	}
	#endif
}
vector<float>	Neuron::weight(){
	#ifdef DEBUG2
	printf("Neuron::weight\n");
	#endif
	return _weight;
}
float			Neuron::netInput(){
	return _netInput;
}
#ifdef DEBUG
void 			Neuron::handleError(int _ERROR,int zusatz){
	#ifdef DEBUG2
	printf("Neuron::handleError\n");
	#endif
	printf("NEURON:\tERROR:\tcode: %i\t",_ERROR);
	switch(_ERROR)
	{
		case 1:{ printf("input(vector<float> signal) signal.size() != Neuron::inputs : %i",zusatz);break;}
		case 2:{ printf("weight(int weightPos) weightPos <> Neuron::inputs weightPos = %i",zusatz);break;}
		case 3:{ printf("weight(int weightPos,float _weight) weightPos <> Neuron::inputs weightPos = %i",zusatz);break;}
		case 4:{ printf("weight(vector<float> _weight) _weight.size() != Neuron::inputs _weight.size() = %i",zusatz);break;}
	}
	printf("\n");
}
#endif
//----------------------------------------------------------
//--------------------------NET-----------------------------
				Net::Net(int in,int hidX,int hidY,int out,bool _bias,bool enaAver){
	#ifdef DEBUG2
	printf("Net::Net\n");
	#endif
	_NET_VERSION			= to_string(NET_VERSION);
	inputs 					= in;
	hiddenX					= hidX;
	hiddenY					= hidY;
	outputs					= out;
	bias 					= _bias;
	enableAverage			= enaAver;

	if(_checkForWrongParam())
	{
		return;
	}
	randEngine				= default_random_engine(rand()%500);

	//----------------------- +1 wegen dem BIAS
	_weightSize 			= (inputs+bias) * hiddenY + (hiddenY+bias) * hiddenY * (hiddenX-1) + (hiddenY+bias) * outputs;
	//-------------------------------------------Erstelle das Array aus Neuronen	

	hiddenLayer				= vector<vector<Neuron>	>(hiddenX,vector<Neuron>(hiddenY,Neuron(hiddenY+bias,enableAverage)));
	hiddenLayer[0]			= vector<Neuron>(hiddenY,Neuron(inputs+bias,enableAverage));
	outputLayer 			= vector<Neuron>(outputs,Neuron(hiddenY+bias,enableAverage));
	//--------------------------------------------------------------------------
	_input					= vector<float>	(inputs);
	_output					= vector<float>	(outputs);
}
				Net::~Net(){
	
}
void 			Net::input(vector<float> signal){
	#ifdef DEBUG2
	printf("Net::input\n");
	#endif
	if(signal.size()!=inputs)
	{
		#ifdef DEBUG 
		_handleError(5,signal.size());
		#endif 
		return;
	}
	else
	{
		_input = signal;
	}
}
void 			Net::input(int pos,float signal){
	#ifdef DEBUG2
	printf("Net::input\n");
	#endif
	if(pos<0 || pos>=inputs)
	{
		#ifdef DEBUG 
		_handleError(4,pos);
		#endif 
		return;
	}
	_input[pos] = signal;
}
vector<float>	Net::input(){
	return _input;
}
float		    Net::input(int pos){
	if(pos<0 || pos>=inputs)
	{
        return 0.0;
	}
	return _input[pos];
}	
vector<float>	Net::output(){
	#ifdef DEBUG2
	printf("Net::inputOnPos\n");
	#endif
	return _output;
}
float			Net::output(int pos){
	if(pos<0){pos=0;}
	
	if(pos>inputs-1){pos=inputs-1;}
	return _output[pos];
}
void 			Net::weightOfNet(vector<float> weight){
	if(weight.size() == _weightSize)
	{
		weight_net = weight;
		int count = 0;
		for(int a=0; a<hiddenY; a++)
		{
			for(int b=0; b<inputs+bias; b++)
			{
				hiddenLayer[0][a].weight(b,weight_net[count]);
				count++;
			}
		}
		for(int a=1; a<hiddenX; a++)
		{
			for(int b=0; b<hiddenY; b++)
			{
				for(int c=0; c<hiddenY+bias; c++)
				{
					hiddenLayer[a][b].weight(c,weight_net[count]);
					count++;
				}
			}
		}
		for(int a=0; a<outputs; a++)
		{
			for(int b=0; b<hiddenY+bias; b++)
			{
				outputLayer[a].weight(b,weight_net[count]);
				count++;
			}
		}	
	}
}
vector<float>	Net::weightOfNet(){
	return weight_net;
}
void 			Net::run(){
	//-------------------------------------CALCULATE-THE-NEURONAL-NET----------------------------
	vector<float>tmpInpt = _input;
	if(bias)
	{
		tmpInpt.push_back(1);//BIAS
	}						
	#ifdef DEBUG2
	printf("--------------INPUTS-------------\n");
	#endif
	for(int a=0; a<hiddenY; a++)
	{
		hiddenLayer[0][a].input(tmpInpt);	//first hidden layer
	}
	tmpInpt = vector<float>(hiddenY+bias);		//+1 because of the BIAS if it is true
	for(int a=0; a<hiddenY; a++)
	{
		tmpInpt[a] = hiddenLayer[0][a].output();//first outputs
	}
	if(bias)
	{
		tmpInpt[hiddenY]	= 1;					//BIAS
	}
	#ifdef DEBUG2
	printf("--------------HIDDEN-------------\n");
	#endif
	for(int a=1; a<hiddenX; a++)
	{
		for(int b=0; b<hiddenY; b++)
		{
			hiddenLayer[a][b].input(tmpInpt);//other hidden layer
		}
		for(int b=0; b<hiddenY; b++)
		{
			tmpInpt[b] = hiddenLayer[a][b].output();//result of the hidden layer 
		}
		if(bias)
		{
			tmpInpt[hiddenY]	= 1;
		}
	}
	#ifdef DEBUG2
	printf("--------------OUTPUTS-------------\n");
	#endif
	for(int a=0; a<outputs; a++)
	{
		outputLayer[a].input(tmpInpt);		//Output layer
		
	}
	for(int a=0; a<outputs; a++)
	{
		_output[a] = outputLayer[a].output();//final result
	} 
	//-------------------------------------------------------------------------------------------
	
}
bool 			Net::_checkForWrongParam(){
	#ifdef DEBUG2
	printf("Net::_checkForWrongParam\n");
	#endif
	bool err = 0;
	if(inputs <= 0)
	{
		#ifdef DEBUG 
		_handleError(0,inputs);
		#endif 
		err = 1;
	}
	if(hiddenX <= 0)
	{
		#ifdef DEBUG 
		_handleError(1,hiddenX);
		#endif 
		err = 1;
	}
	if(hiddenY <= 0)
	{
		#ifdef DEBUG 
		_handleError(2,hiddenY);
		#endif 
		err = 1;
	}
	if(outputs <= 0)
	{
		#ifdef DEBUG 
		_handleError(3,outputs);
		#endif 
		err = 1;
	}
	return err;
}
unsigned int 	Net::genomSize(){
	return _weightSize;
}
#ifdef DEBUG
void 			Net::_handleError(int _ERROR,int zusatz){
	#ifdef DEBUG2
	printf("Net::handleError\n");
	#endif
	printf("NET:\tERROR:\tcode: %i\t",_ERROR);
	if(_ERROR >= 0 && _ERROR <= 3)
	{
		printf("Net::Net(int in,int hidX,int hidY,int out,int ani,float fac)\n    \t      \tParameter:\t");
	}
	switch(_ERROR)
	{
		
		case 0:	{ printf("in ist zu klein: %i",inputs);break;}
		case 1:	{ printf("hidX ist zu klein: %i",hiddenX);break;}
		case 2:	{ printf("hidY ist zu klein: %i",hiddenY);break;}
		case 3:	{ printf("out ist zu klein: %i",outputs);break;}
		case 4:{ printf("input(int pos,float signal) pos out of range: %i",zusatz);break;}
		case 5:{ printf("input(vector<float> signal) signal.size()!=inputs %i",zusatz);break;}
		
		default:{ printf("UNKNOWN ERROR: %i",_ERROR);break;}
	}
	printf("\n");
}
#endif
//----------------------------------------------------------
