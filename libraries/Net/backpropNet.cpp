/*
Autor 		Alex Krieg
Version 	1.0
Datum		7.11.2017
*/
#include "backpropNet.h"


backpropNet::backpropNet(int in,int hidX,int hidY,int out,float fac,bool _bias)
	: Net(in,hidX,hidY,out,_bias,false)
{
	_BACKPROP_NET_VERSION   = to_string(BACKPROP_NET_VERSION);
	mutFactor 				= fac;
	_outputError			= vector<float>(out,1);
	if(checkForWrongParam())
	{
		return;
	}
	_networkConfiguration	= networkConfiguration();
	_genom					= vector<float>(_weightSize,0);
	float tmp;
	for(int b=0; b<_weightSize; b++)
	{
		tmp = randEngine()%100;
		_genom[b] = (tmp-50)/100;
	}
}
	backpropNet::~backpropNet(){}
	
bool 		backpropNet::saveData(string name)
{
	#ifdef DEBUG2
	printf("backpropNet::saveData\n");
	#endif
	file = fopen(name.c_str(),"w");
	if(!file)
	{
		#ifdef DEBUG
		handleError(11);
		#endif 
		return 1;
	}
	rewind (file);
	fprintf(file,"%s\n",_networkConfiguration.c_str());	
	for(int a=0; a<_weightSize; a++)
	{
		fprintf(file,"%.8f ",_genom[a]);
	}
	fprintf(file,"\n");	
	fclose(file);
	return 0;
}
int			backpropNet::loadData(string name)
{
	//#ifdef DEBUG2
	printf("backpropNet::loadData\n");
	//#endif
	string tmpNetCheck;
	printf("_genom.size()=%i\n",_genom.size());
	file = fopen(name.c_str(),"r");
	if(!file)
	{
		#ifdef DEBUG
		handleError(12);
		#endif 
		return 2;
	}
	rewind (file);
	char tmpBuff[100];
	fscanf(file,"%s",tmpBuff);
	tmpNetCheck = tmpBuff;
	if(tmpNetCheck != _networkConfiguration)
	{
		#ifdef DEBUG
		handleError(13);
		#endif
		fclose(file);
		return 1;
	}
	//printf("DATA:\n");
	for(int a=0; a<_weightSize; a++)
	{
		fscanf(file,"%f",&_genom[a]);
		//printf("%.8f\n",_genom[a]);
	}
	//printf("END:\n");
	fclose(file);
	loadGenom();
	return 0;
}
void 		backpropNet::learn(vector<float> expected)
{
	//#define DEBUG3
	COORD coord;
	coord.X = 0;
	coord.Y = 15;
	#ifdef DEBUG2
	printf("backpropNet::learn\n");
	#endif
	vector<float>deltaWout;
	vector<vector<float>	>deltaWhidd(hiddenX-1,vector<float>((hiddenY+bias)*hiddenY));//-first layer +bias
	vector<float>deltaWin;
	vector<float>derivOut;
	vector<vector<float>	>derivHidd(hiddenX,vector<float>(hiddenY));
	float summHidden;
	int counter = 0;
	if(expected.size() != outputs)
	{
		#ifdef DEBUG 
		handleError(2,expected.size());
		#endif
		return;
	}
	//vector<float>tmp2(outputs);
	
	for(int a=0; a<outputs; a++)
	{
		_outputError[a] = expected[a]-_output[a];
		derivOut.push_back(abl(outputLayer[a].netInput())*_outputError[a]);
		for(int b=0; b<hiddenY+bias; b++)//+1 -> bias
		{
			if(b==hiddenY)
			{
				deltaWout.push_back(derivOut[a] * mutFactor * 1);//output of the bias
			}
			else
			{
				deltaWout.push_back(derivOut[a] * mutFactor * hiddenLayer[hiddenX-1][b].output());
			}
		}
	}
	float tmp2 = 0;
	for(int a=0; a<hiddenY; a++)
	{
		tmp2 = 0;
		for(int b=0; b<outputs; b++)
		{
			tmp2 += derivOut[b]*outputLayer[b].weight(a);
		}
		derivHidd[hiddenX-1][a] = abl(hiddenLayer[hiddenX-1][a].netInput())*tmp2;
		//printf("derivHidd: %.8f \thiddenX-1: %i a: %i\n",derivHidd[hiddenX-1][a],hiddenX-1,a);
	}
	for(int a=hiddenX-2; a>=0; a--)
	{
		for(int b=0; b<hiddenY; b++)
		{
			tmp2=0;
			for(int c=0; c<hiddenY; c++)
			{
				tmp2+=derivHidd[a+1][c]*hiddenLayer[a+1][c].weight(b);
			}
			derivHidd[a][b]= abl(hiddenLayer[a][b].netInput())*tmp2;
			//printf("derivHidd: %.8f      \ta: %i b: %i\n",derivHidd[a][b],a,b);
		}
	}
	for(int a=0; a<hiddenX-1; a++)//-inputLayer
	{
		counter = 0;
		for(int b=0; b<hiddenY; b++)
		{
			for(int c=0; c<hiddenY+bias; c++)
			{
				if(c==hiddenY)//is it the bias?
				{
					deltaWhidd[a][counter]=derivHidd[a+1][b] * mutFactor * 1;//output of the bias
				}
				else
				{
					deltaWhidd[a][counter]=derivHidd[a+1][b]*mutFactor*hiddenLayer[a][c].output();
				}
				//printf("deltaWhidd.x:%i y:%i=%i\n",a,counter);
				counter++;
			}
		}
	}
	for(int a=0; a<hiddenY; a++)
	{
		for(int b=0; b<inputs+bias; b++)
		{
			if(b==inputs)
			{
				deltaWin.push_back(derivHidd[0][a]*mutFactor*1);
				//printf("deltaW1: %.8f \tderiv: %.8f\tmutFac: %.8f\tinput: %.8f\n",deltaWin[deltaWin.size()-1],derivHidd[0][a],mutFactor,1);
			}
			else
			{
				deltaWin.push_back(derivHidd[0][a]*mutFactor*_input[b]);
				//printf("deltaW2: %.8f \tderiv: %.8f\tmutFac: %.8f\tinput: %.8f\n",deltaWin[deltaWin.size()-1],derivHidd[0][a],mutFactor,_input[b]);
				
			}
			#ifdef DEBUG3
			SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
			printf("deltaWin[%i]=%.3f a: %i b: %i          \n",deltaWin.size()-1,deltaWin[deltaWin.size()-1],a,b);
			coord.Y++;
			#endif
		}
	}
	#ifdef DEBUG3
	coord.Y++;
	#endif
	counter = 0;
	//printf("deltaSize: %i\n",deltaWin.size());
	for(int a=0; a<((inputs+bias)*hiddenY); a++)
	{
		_genom[counter]+=deltaWin[a];
		counter++;
	}
	for(int a=0; a<hiddenX-1; a++)
	{
		for(int b=0; b<(hiddenY+bias)*hiddenY; b++)
		{
			_genom[counter]+=deltaWhidd[a][b];
			counter++;
		}
	}
	for(int a=0; a<(hiddenY+bias)*outputs; a++)
	{
		//printf("genom[%i] %.3f delataOut[%i] %.3f delta: %.4f\n",counter,_genom[counter],a,deltaWout[a]);
		_genom[counter]+=deltaWout[a];
		counter++;
	}
	#ifdef DEBUG3
	counter = 0;
	for(int a=0; a<hiddenY;a++)
	{
		for(int b=0; b<inputs+bias; b++)
		{
			SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
			printf("Nhx: %i Nhy: %i W: %i -> %.3f \tdelta:\t%.8f\tderiv: \t%.8f                   ",0,a,b,hiddenLayer[0][a].weight(b),deltaWin[counter],derivHidd[0][a]);
			counter++;
			coord.Y++;
		}
	}
	counter = 0;
	coord.Y++;
	for(int a=1; a<hiddenX;a++)
	{
		counter = 0;
		for(int b=0; b<hiddenY; b++)
		{
			for(int c=0; c<hiddenY+bias; c++)
			{
				SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
				printf("Nhx: %i Nhy: %i W: %i -> %.3f \tdelta:\t%.8f\tderiv: \t%.8f                   ",a,b,c,hiddenLayer[a][b].weight(c),deltaWhidd[a][counter],derivHidd[a][b]);
				counter++;
				coord.Y++;
			}
		}
	}
	counter = 0;
	coord.Y++;
	for(int a=0; a<outputs; a++)
	{
		for(int b=0; b<hiddenY+bias; b++)
		{
			SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
			printf("No: %i W: %i -> %.3f \tdelta:\t%.8f\tderiv: \t%.8f                       ",a,b,outputLayer[a].weight(b),deltaWout[counter],derivOut[a]);
			counter++;
			coord.Y++;
		}
	}
	#endif
	
	
	/*for(int a=outputs-1; a>=0; a--)
	{	//Output Layer
		_outputError[a] = expected[a]-_output[a];
		deriv.push_back(abl(outputLayer[a].netInput())*(expected[a]-_output[a]));
		deltaW.push_back(deriv[counter] * mutFactor * hiddenLayer[hiddenX-1][a].output());
		counter++;
	}
	if(hiddenX > 1)
	{
		for(int a=hiddenX-1; a>=1; a--)
		{
			for(int b=hiddenY-1; b>=0; b--)
			{
				summHidden = 0;
				if(a==hiddenX-1)
				{
					for(int c=outputs-1; c>=0; c--)
					{
						//printf("backpropNet::learn->counter: %i %i\n",counter,counter-outputs);
						summHidden += outputLayer[c].weight(b)*deriv[counter-outputs];
					}
					//printf("backpropNet::learn-> 3\n");
					deriv.push_back(abl(outputLayer[b].netInput())*summHidden);
				}
				else
				{
					for(int c=hiddenY-1; c>=0; c--)
					{
						summHidden += hiddenLayer[a][c].weight(b)*deriv[counter-hiddenY];
					}
					deriv.push_back(abl(hiddenLayer[a][b].netInput())*summHidden);
				}
				deltaW.push_back(deriv[counter] * mutFactor * hiddenLayer[a][b].output());
				counter++;
			}
		}
	}
	//printf("backpropNet::learn-> 2\n");
	for(int a=inputs-1; a>=0; a--)
	{
		for(int b=hiddenY-1; b>=0; b--)
		{
			summHidden += hiddenLayer[0][b].weight(a)*deriv[counter-hiddenY];
		}
		deriv.push_back(abl(_input[a])*summHidden);
		deltaW.push_back(deriv[counter] * mutFactor * _input[a]);
		counter++;
	}*/
	for(int a=0; a<_weightSize; a++)
	{
	//	printf("Genom: %.3f delta: %.3f NR: %i \n",_genom[a],deltaW[_weightSize-a-1],_weightSize-a-1);
		//_genom[a]+=deltaW[_weightSize-a-1];
	}
	loadGenom();
}
void 		backpropNet::genom(vector<float> _Genom)	
{
	if(_Genom.size() != _genom.size())
	{
		#ifdef DEBUG 
		handleError(1,_Genom.size());
		#endif
		return;
	}
	_genom = _Genom;
	loadGenom();
}		
vector<float>	backpropNet::genom()
{
	return _genom;
}
string 		backpropNet::networkConfiguration()
{
	return "backpropagation_V"+_BACKPROP_NET_VERSION+"_V"+_NET_VERSION+"_"+to_string(inputs)+"_"+to_string(hiddenX)+"_"+to_string(hiddenY)+"_"+to_string(outputs)+"_"+to_string(bias);
}
float 		backpropNet::error()
{
	float ret=0.0;
	for(int a=0; a<outputs; a++)
	{
		if(_outputError[a] < 0)
		{
			ret+=-_outputError[a];
		}
		else
		{
			ret+=_outputError[a];
		}
		
	}
	return ret;
}

float 		backpropNet::error(int out)
{
	if(out < outputs && out>=0)
	{
		return _outputError[out];
	}
	return 0.0;
}

void 		backpropNet::loadGenom()
{
	#ifdef DEBUG2
	printf("backpropNet::loadGenom\n");
	#endif
	int count = 0;
	#ifdef DEBUG3
	printf("\n_genom:\t");
	for(int a=0; a<_genom.size(); a++)
	{
		printf("%.3f\t",_genom[a]);
	}
	printf("\n");
	#endif
	for(int a=0; a<hiddenY; a++)
	{
		for(int b=0; b<inputs+bias; b++)
		{
			hiddenLayer[0][a].weight(b,_genom[count]);
			count++;
		}
	}
	for(int a=1; a<hiddenX; a++)
	{
		for(int b=0; b<hiddenY; b++)
		{
			for(int c=0; c<hiddenY+bias; c++)
			{
				hiddenLayer[a][b].weight(c,_genom[count]);
				count++;
			}
		}
	}
	for(int a=0; a<outputs; a++)
	{
		for(int b=0; b<hiddenY+bias; b++)
		{
			outputLayer[a].weight(b,_genom[count]);
			count++;
		}
	}	
	#ifdef DEBUG3
	printf("Net:\t");
	
	for(int a=0; a<hiddenY; a++)
	{
		for(int b=0; b<inputs+bias; b++)
		{
			printf("%.3f\t",hiddenLayer[0][a].weight(b));
		}
	}
	for(int a=1; a<hiddenX; a++)
	{
		for(int b=0; b<hiddenY; b++)
		{
			for(int c=0; c<hiddenY+bias; c++)
			{
				printf("%.3f\t",hiddenLayer[a][b].weight(c));
			}
		}
	}
	for(int a=0; a<outputs; a++)
	{
		for(int b=0; b<hiddenY+bias; b++)
		{
			printf("%.3f\t",outputLayer[a].weight(b));
		}
	}
	printf("\n");
	#endif
}
bool 		backpropNet::checkForWrongParam(){
	#ifdef DEBUG2
	printf("Net::checkForWrongParam\n");
	#endif
	bool err = 0;
	if(mutFactor < 0 /*|| mutFactor > 1*/)
	{
		#ifdef DEBUG 
		handleError(0);
		#endif
		err = 1;
	}
	return err;
}
float		backpropNet::abl(float netinput)
{
	//printf("abl: %.8f\n",2*exp(netinput)/((exp(netinput)+1)*(exp(netinput)+1)));
	return (2*exp(netinput)/((exp(netinput)+1)*(exp(netinput)+1)));
}
#ifdef DEBUG
void 		backpropNet::handleError(int _ERROR,int zusatz){
	#ifdef DEBUG2
	printf("backpropNet::handleError\n");
	#endif
	printf("NET:\tERROR:\tcode: %i\t",_ERROR);
	if(_ERROR >= 0 && _ERROR <= 0)
	{
		printf("backpropNet::backpropNet(int in,int hidX,int hidY,int out,float fac,bool _bias,bool enaAver)\n    \t      \tParameter:\t");
	}
	switch(_ERROR)
	{
		case 0:	{ printf("fac muss zwischen 0.0 und 1.0 liegen");break;}
		case 1:	{ printf("backpropNet::genom(vector<float> _Genom) _Genom hat falsche Grösse: %i",zusatz);break;}
		case 2:	{ printf("backpropNet::learn(vector<float> expected) expected hat falsche Grösse: %i",zusatz);break;}
		
		case 11:{ printf("saveData(char *_file) Die Datei konnte nicht geoeffnet werden");break;}
		case 12:{ printf("loadData(char *_file) Die Datei konnte nicht geoeffnet werden. Sie muss zuerst erstellt werden");break;}
		case 13:{ printf("loadData(char *_file) Die Datei enthaelt falsche Netzwerk Konfiguration");break;}
		default:{ printf("UNKNOWN ERROR: %i",_ERROR);break;}
	}
	printf("\n");
}
#endif













