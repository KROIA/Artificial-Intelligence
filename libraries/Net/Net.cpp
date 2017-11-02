/*
Net 	REMAKE
Autor 		Alex Krieg
Version 	0.3
Datum		11.10.2017
*/
#include "Net.h"


//--------------------------NEURON--------------------------
				Neuron::Neuron(int anzInputs,bool enaAver){
	#ifdef DEBUG2
	printf("Neuron::Neuron\n");
	#endif
	inputs					= anzInputs;
	randEngine				= default_random_engine(rand()%500);
	weight 					= vector<float>	(inputs,(randEngine()%1000)/1000);
	enableAverage			= enaAver;
}
				Neuron::~Neuron(){
	weight.clear();
}
void 			Neuron::setInput(vector<float> signal){
	#ifdef DEBUG2
	printf("Neuron::setInput\n");
	#endif
	if(signal.size() == inputs)
	{
		output = 0.0;
		for(int a = 0; a<inputs; a++)
		{
			output += signal[a] * weight[a];		//Berechnet den Netzinput
		}
		if(enableAverage)
		{
			output /= inputs;						//Erstellt den Durchschnitt daraus um eine
		}											//flachere Aktivierung der Sigmoid Funktion zu erreichen
		
													
		output = ((1.0/(1.0+exp(-output)))-0.5)*2;	//Aktivierungs Funktion 
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
					  Netzinput
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
float 			Neuron::getOutput(){
	#ifdef DEBUG2
	printf("Neuron::getOutput\n");
	#endif
	return output;
}
float 			Neuron::getWeightOnPos(int weightPos){
	#ifdef DEBUG2
	printf("Neuron::getWeightOnPo\n");
	#endif
	if(weightPos<inputs && weightPos>-1)
	{
		return weight[weightPos];
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
void 			Neuron::setWeightOnPos(int weightPos,float _weight){
	#ifdef DEBUG2
	//printf("Neuron::setWeightOnPos\n");
	#endif
	if(weightPos<inputs && weightPos>-1)
	{
		weight[weightPos] = _weight;
	}
	#ifdef DEBUG
	else
	{
		handleError(3,weightPos);
		printf("Neuron::inputs = %i\n",inputs);
	}
	#endif
}
void 			Neuron::setWeight(vector<float> _weight){
	#ifdef DEBUG2
	printf("Neuron::setWeight\n");
	#endif
	if(_weight.size() == inputs)
	{
		weight = _weight;
	}
	#ifdef DEBUG
	else
	{
		handleError(4,_weight.size());
		printf("Neuron::inputs = %i\n",inputs);
	}
	#endif
}
vector<float>	Neuron::getWeight(){
	#ifdef DEBUG2
	printf("Neuron::getWeight\n");
	#endif
	return weight;
}

#ifdef DEBUG
void 			Neuron::handleError(int _ERROR,int zusatz){
	#ifdef DEBUG2
	printf("Neuron::handleError\n");
	#endif
	printf("NEURON:\tERROR:\tcode: %i\t",_ERROR);
	switch(_ERROR)
	{
		case 1:{ printf("netInput(vector<float> signal) signal.size() != Neuron::inputs : %i",zusatz);break;}
		case 2:{ printf("getWeightOnPos(int weightPos) weightPos.size() <> Neuron::inputs weightPos.size() = %i",zusatz);break;}
		case 3:{ printf("setWeightOnPos(int weightPos,float _weight) weightPos <> Neuron::inputs weightPos = %i",zusatz);break;}
		case 4:{ printf("setWeight(vector<float> _weight) _weight.size() != Neuron::inputs _weight.size() = %i",zusatz);break;}
	}
	printf("\n");
}
#endif
//----------------------------------------------------------
//--------------------------NET-----------------------------
				Net::Net(int in,int hidX,int hidY,int out,int ani,float fac,bool _bias,bool enaAver){
	#ifdef DEBUG2
	printf("Net::Net\n");
	#endif
	inputs 					= in;
	hiddenX					= hidX;
	hiddenY					= hidY;
	outputs					= out;
	animals					= ani;
	bias 					= _bias;
	currentAnimal			= 0;
	mutationChangeDivisor	= 100000;
	enableAverage			= enaAver;
	if(fac != 0)
	{
		if(fac > 1.0)
		{
			fac = 1;
		}
		mutFactor 	= 1/fac;
	}
	else
	{
		mutFactor = 0;
	}
	
	if(checkForWrongParam())
	{
		return;
	}
	randEngine				= default_random_engine(rand()%500);

	//----------------------- +1 wegen dem BIAS
	genomSize 			= (inputs+bias) * hiddenY + (hiddenY+bias) * hiddenY * (hiddenX-1) + (hiddenY+bias) * outputs;
	//-------------------------------------------Erstelle das Array aus Neuronen	
	if(bias)
	{
		hiddenLayer				= vector<vector<Neuron>	>(hiddenX,vector<Neuron>(hiddenY+1,Neuron(hiddenY+1,enableAverage)));
		hiddenLayer[0]			= vector<Neuron>(hiddenY,Neuron(inputs+1,enableAverage));
		outputLayer 			= vector<Neuron>(outputs,Neuron(hiddenY+1,enableAverage));
	}
	else
	{
		hiddenLayer				= vector<vector<Neuron>	>(hiddenX,vector<Neuron>(hiddenY,Neuron(hiddenY,enableAverage)));
		hiddenLayer[0]			= vector<Neuron>(hiddenY,Neuron(inputs,enableAverage));
		outputLayer 			= vector<Neuron>(outputs,Neuron(hiddenY,enableAverage));
	}
	//--------------------------------------------------------------------------
	genom 					= vector<vector<float>	>(animals,vector<float>(genomSize,0));
	input					= vector<float>	(inputs);
	output					= vector<float>	(outputs);
	
	for(int a=0; a<animals; a++)
	{
		float tmp;
		for(int b=0; b<genomSize; b++)
		{
			tmp = randEngine()%100;
			genom[a][b] = (tmp-50)/100;
		}
	}
	loadGenomOfAnimal();
}
				Net::~Net(){
	
}
void 			Net::saveData(string name){
	#ifdef DEBUG2
	printf("Net::saveData\n");
	#endif
	file = fopen(name.c_str(),"w");
	if(!file)
	{
		#ifdef DEBUG
		handleError(11);
		#endif 
		return;
	}
	rewind (file);
	fprintf(file,"%i %i %i %i %i %i %i\n",inputs,hiddenY,hiddenX,outputs,animals,bias,enableAverage);
	for(int a=0; a<animals; a++)
	{
		for(int b=0; b<genomSize; b++)
		{
			fprintf(file,"%.8f ",genom[a][b]);
		}
		fprintf(file,"\n");
	}
	fclose(file);
}
void			Net::loadData(string name){
	#ifdef DEBUG2
	printf("Net::loadData\n");
	#endif
	int tmpInputs;
	int tmpHiddenY;
	int tmpHiddenX;
	int tmpOutputs;
	int tmpAnimals;	
	int tmpBias;
	int tmpEnableAverage;
	
	file = fopen(name.c_str(),"r");
	if(!file)
	{
		#ifdef DEBUG
		handleError(12);
		#endif 
		return;
	}
	rewind (file);
	fscanf(file,"%i",&tmpInputs);
	fscanf(file,"%i",&tmpHiddenY);
	fscanf(file,"%i",&tmpHiddenX);
	fscanf(file,"%i",&tmpOutputs);
	fscanf(file,"%i",&tmpAnimals);
	fscanf(file,"%i",&tmpBias);
	fscanf(file,"%i",&tmpEnableAverage);
	
	if(tmpInputs!=inputs || tmpHiddenY!=hiddenY || tmpHiddenX!=hiddenX || tmpOutputs!=outputs || tmpAnimals!=animals || tmpBias!=bias || tmpEnableAverage!=enableAverage)
	{
		#ifdef DEBUG
		handleError(13);
		#endif
		fclose(file);
		return;
	}
	for(int a=0; a<animals; a++)
	{
		for(int b=0; b<genomSize; b++)
		{
			fscanf(file,"%f",&genom[a][b]);
		}
	}
	fclose(file);
	loadGenomOfAnimal();
}
void 			Net::setInput(vector<float> signal){
	#ifdef DEBUG2
	printf("Net::setInput\n");
	#endif
	if(signal.size()!=inputs)
	{
		#ifdef DEBUG 
		handleError(11,signal.size());
		#endif 
		return;
	}
	else
	{
		input = signal;
	}
}
void 			Net::setInputOnPos(int pos,float signal){
	#ifdef DEBUG2
	printf("Net::setInputOnPos\n");
	#endif
	if(pos<0 || pos>=inputs)
	{
		#ifdef DEBUG 
		handleError(10,pos);
		#endif 
		return;
	}
	else
	{
		input[pos] = signal;
	}
}
vector<float>	Net::getOutput(){
	#ifdef DEBUG2
	printf("Net::setInputOnPos\n");
	#endif
	return output;
}
void			Net::learn(vector<float> fitness){
	#ifdef DEBUG2
	printf("Net::learn\n");
	#endif
	if(fitness.size()!=animals)
	{
		#ifdef DEBUG
		handleError(15,fitness.size());
		#endif
		return;
	}
	vector<vector<float>	>	tmpGenetic = genom;
	for(int x=0; x<animals/2; x++)
	{
		float gesFitnessF = 0;
		int gesFitnessI;
		float randomPos1;
		float randomPos2;
		int randomSelection1;
		int randomSelection2;
		for(int a=0; a<animals; a++)
		{
			gesFitnessF += fitness[a]; //Berechne gesamte Fitness
			
		}
		#ifdef DEBUG2
		printf("Net::learn->gesFitnessF: %.8f\n",gesFitnessF);
		#endif
		gesFitnessI = gesFitnessF;
		gesFitnessF = 0;
		//------------------------------RANDOM SELECTION----------------------------------------------
		/*
		
		GENOM	  |  RANKING  |
		----------|-----------|
		GENOM 1:  |	   125    |
		GENOM 2:  |	   17     |
		GENOM 3:  |	   230    |                       |--> "gesFitnessF" Gesamte Fitness aller Genomen(animals)
													  |
				|-------------------------------------|------------------------------------------------------|
				|                                                                                            |
				|--------------------------------------------------------------------------------------------|
				|       GENOM 1       | GENOM 2 |                           GENOM 3                          |
				|--------------------------------------------------------------------------------------------|
				|
				|                                    |
				|----------------|-------------------|
								 |   				 |
								 |
								 |--> Random Selektion über das gesamte Specktrum
									  Selektiert wurde GENOM 3.
									  Das GENOM mit der höchsten "fitness" hat die gröste chance selektiert zu werden 
		
		*/
		//-------------------------------------------------------------------------Selektiere Animal 1
		randomPos1 = randEngine()%(gesFitnessI*10);
		randomPos1 /= 10;
		for(int a=0; a<animals; a++)
		{
			if(randomPos1<gesFitnessF+fitness[a] && randomPos1>=gesFitnessF)
			{
				randomSelection1 = a;
				a				 = animals;
			}
			gesFitnessF+=fitness[a];
		}
		randomPos2 = randEngine()%(gesFitnessI*10);
		randomPos2 /= 10;
		gesFitnessF = 0;
		bool ret = false;
		#ifdef DEBUG2
		printf("Net::learn->randomSelection1: %i\n",randomSelection1);
		#endif
		//--------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------Selektiere Animal 2
		while(!ret)						//Mache es solange bis nicht zweimal die gleichen selektiert wurden
		{
			for(int a=0; a<animals; a++)
			{
				if(randomPos2<(gesFitnessF+fitness[a]) && randomPos2>=gesFitnessF)
				{
					randomSelection2 = a;
					#ifdef DEBUG2
					printf("Net::learn->randomSelection2  true: %i %.8f \n",randomSelection2,gesFitnessF);
					#endif
					a				 = animals;
					gesFitnessF		 = 0;
					
				}
				else
				{
					gesFitnessF+=fitness[a];
				}
			}
			if(randomSelection2 == randomSelection1)
			{
				#ifdef DEBUG2
				printf("Net::learn->randomSelection2: %i\n",randomSelection2);
				#endif
				randomPos2 = randEngine()%(gesFitnessI*10);
				randomPos2 /= 10;
				gesFitnessF		 = 0;
				
			}
			else
			{
				ret = true;
			}
		}
		#ifdef DEBUG2
		printf("Net::learn->randomSelection2: %i\n",randomSelection2);
		#endif
		//--------------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------Starte Crossover
		int randomCrossoverPoint = ((randEngine()+1)%genomSize-1);	//Crossover Break Position 
		/*
		
									|--> genomSize
									|
					|---------------|--------------|	
					|							   |
		GENOM 1:	|xxxxxxxxx|xxxxxxxxxxxxxxxxxxxx|
					|		  |					   |
		GENOM 2:	|yyyyyyyyy|yyyyyyyyyyyyyyyyyyyy|
							  |
							  |--> Random crossover break point
		
		Crossover:
		
		GENOM 1:	|xxxxxxxxx|yyyyyyyyyyyyyyyyyyyy|
					|		  |					   |
		GENOM 2:	|yyyyyyyyy|xxxxxxxxxxxxxxxxxxxx|
		
		*/
		vector<float>	tmpGenom1(genomSize,3);
		vector<float>	tmpGenom2(genomSize,3);
		#ifdef DEBUG2
		printf("Net::learn->Crossover -> randomCrossoverPoint: %i randomSelection1: %i randomSelection2: %i\n",randomCrossoverPoint,randomSelection1,randomSelection2);
		#endif
		for(int a=0; a<genomSize-randomCrossoverPoint; a++)
		{
			tmpGenom1[a] = genom[randomSelection1][a];
			tmpGenom2[a] = genom[randomSelection2][a];
		}
		for(int a=genomSize-randomCrossoverPoint; a<genomSize; a++)
		{
			tmpGenom1[a] = genom[randomSelection2][a];
			tmpGenom2[a] = genom[randomSelection1][a];
		}
		tmpGenetic[randomSelection1] = tmpGenom1;
		tmpGenetic[randomSelection2] = tmpGenom2;
		#ifdef DEBUG2
		printf("Net::learn->Crossover end\n");
		#endif
		//--------------------------------------------------------------------------------------------	
	}
	genom = tmpGenetic;

		//-----------------------------------------------------------------------------Random mutation
		
		/*
				|		|		|		|		|		|		|		|		|		|		|
		GENOM :	| 0.125 | 0.380 | 1.532 | 0.821 | 0.012 |-0.435 | 0.723	|-1.433 |-0.243 | 0.352 |
				|       |       |       |       |       |       |       |       |       |       |
		
							|						|				|
		RANDOM			  +0.3	                  -0.83           +0.1
							|                   	|           	|
		
				|		|		|		|		|		|		|		|		|		|		|
		GENOM :	| 0.125 | 0.680 | 1.532 | 0.821 |-0.818 |-0.435 | 0.823	|-1.433 |-0.243 | 0.352 |
				|       |       |       |       |       |       |       |       |       |       |
				
				
				
				Je grösser der Faktor "mutFactor" ist desto öfters ist ein bestimmtes Geen betroffen.
				Zu hoher "mutFactor" bedeutet, dass das Netzwerk nicht lernen kann da es mehr Brute force wäre.
				Zu kleiner "mutFactor" bedeutet, dass das Netzwerk sz langsam lernt und darum länger benötigt.
		
		*/
	#ifdef DEBUG2
	printf("Net::learn->Mutation\n");
	#endif
	if(mutFactor != 0)
	{
		int doMutate;
		for(int a=0; a<animals; a++)
		{
			for(int b=0; b<genomSize; b++)
			{
				doMutate = randEngine() % mutFactor;
				if(doMutate == 0)
				{
					float tmp = randEngine()%100;
					genom[a][b] += (tmp-50)/mutationChangeDivisor;
				}
			}
		}
	}
	#ifdef DEBUG2
	printf("Net::learn->Mutation end\n");
	#endif
		//--------------------------------------------------------------------------------------------
}
void			Net::setGenomOfAnimal(int animal,vector<float> _genom){
	#ifdef DEBUG2
	printf("Net::setGenomOfAnimal\n");
	#endif
	if(animal<0 || animal>=animals)
	{
		#ifdef DEBUG 
		handleError(7,animal);
		#endif 
		return;
	}
	genom[animal] = _genom;
	if(animal == 0)
	{
		loadGenomOfAnimal();
	}
}
void			Net::setGenom(vector<vector<float>	> _genom){
	#ifdef DEBUG2
	printf("Net::setGenom\n");
	#endif
	if(genomSize != _genom.size())
	{
		#ifdef DEBUG 
		handleError(8,_genom.size());
		#endif 
		return;
	}
	genom = _genom;
}
vector<float>	Net::getGenomOfAnimal(int ani){
	#ifdef DEBUG2
	printf("Net::getGenomOfAnimal(%i)\n",ani);
	#endif
	
	if(ani<0 || ani>=animals)
	{
		#ifdef DEBUG 
		handleError(9,ani);
		#endif 
		return genom[0];;
	}
	//printf("\n\n\n\nNet::getGenomOfAnimal(%i)  genom.size() = %i %i\n",ani,genom[1].size(),genom[99].size());
	return genom[ani];
}
vector<vector<float>	>Net::getGenom(){
	#ifdef DEBUG2
	printf("Net::getGenom\n");
	#endif
	return genom;
}
void 			Net::run(int aditionalAnimal){
	#ifdef DEBUG2
	printf("Net::run\n");
	#endif
	if(aditionalAnimal != 0)
	{
		if(aditionalAnimal < 0 || aditionalAnimal >=animals)
		{
			#ifdef DEBUG
			handleError(14,aditionalAnimal);
			#endif
			return;
		}
		currentAnimal = aditionalAnimal;
		loadGenomOfAnimal();
	}
	//-------------------------------------CALCULATE-THE-NEURONAL-NET----------------------------
	
	vector<float> tmpIn = input;
	if(bias)
	{
		tmpIn.push_back(1);
	}						//BIAS
	#ifdef DEBUG2
	printf("--------------INPUTS-------------\n");
	#endif
	for(int a=0; a<hiddenY; a++)
	{
		hiddenLayer[0][a].setInput(tmpIn);	//Erster Hidden Layer
	}
	tmpIn = vector<float>(hiddenY+bias);		//+1 wegen dem BIAS
	for(int a=0; a<hiddenY; a++)
	{
		tmpIn[a] = hiddenLayer[0][a].getOutput();//Erste Outputs
	}
	if(bias)
	{
		tmpIn[hiddenY]	= 1;					//BIAS
	}
	#ifdef DEBUG2
	printf("--------------HIDDEN-------------\n");
	#endif
	for(int a=1; a<hiddenX; a++)
	{
		for(int b=0; b<hiddenY; b++)
		{
			hiddenLayer[a][b].setInput(tmpIn);//Restliche Hidden Layer
		}
		for(int b=0; b<hiddenY; b++)
		{
			tmpIn[b] = hiddenLayer[a][b].getOutput();//Ergebnisse der Hidden Layer
		}
		if(bias)
		{
			tmpIn[hiddenY]	= 1;
		}
	}
	#ifdef DEBUG2
	printf("--------------OUTPUTS-------------\n");
	#endif
	for(int a=0; a<outputs; a++)
	{
		outputLayer[a].setInput(tmpIn);		//Output Layer
	}
	for(int a=0; a<outputs; a++)
	{
		output[a] = outputLayer[a].getOutput();//Endresultate 
	} 
	//-------------------------------------------------------------------------------------------
	
}
void 			Net::loadGenomOfAnimal(){
	#ifdef DEBUG2
	printf("Net::loadGenomOfAnimal\n");
	#endif
	int count = 0;
	for(int a=0; a<hiddenY; a++)
	{
		for(int b=0; b<inputs+bias; b++)
		{
			//printf("INPUTS\n");
			hiddenLayer[0][a].setWeightOnPos(b,genom[currentAnimal][count]);
			count++;
		}
	}
	for(int a=1; a<hiddenX; a++)
	{
		for(int b=0; b<hiddenY; b++)
		{
			for(int c=0; c<hiddenY+bias; c++)
			{
				//printf("HIDDEN\n");
				hiddenLayer[a][b].setWeightOnPos(c,genom[currentAnimal][count]);
				count++;
			}
		}
	}
	for(int a=0; a<outputs; a++)
	{
		for(int b=0; b<hiddenY+bias; b++)
		{
			//printf("OUTPUTS\n");
			//printf("GENOM on Pos %i ist: %.8f\n",b,genom[currentAnimal][count]);
			outputLayer[a].setWeightOnPos(b,genom[currentAnimal][count]);
			count++;
		}
	}	
}
bool 			Net::checkForWrongParam(){
	#ifdef DEBUG2
	printf("Net::checkForWrongParam\n");
	#endif
	bool err = 0;
	if(inputs <= 0)
	{
		#ifdef DEBUG 
		handleError(1);
		#endif 
		err = 1;
	}
	if(hiddenX <= 0)
	{
		#ifdef DEBUG 
		handleError(2);
		#endif 
		err = 1;
	}
	if(hiddenY <= 0)
	{
		#ifdef DEBUG 
		handleError(3);
		#endif 
		err = 1;
	}
	if(outputs <= 0)
	{
		#ifdef DEBUG 
		handleError(4);
		#endif 
		err = 1;
	}
	if(animals <= 0)
	{
		#ifdef DEBUG 
		handleError(5);
		#endif 
		err = 1;
	}
	return err;
}
void 			Net::setMutationValue(float val){
	if(val < 0)
	{
		mutationChangeDivisor = 1/val;
	}
}
unsigned int 	Net::getGenomSize(){
	return genomSize;
}
#ifdef DEBUG
void 			Net::handleError(int _ERROR,int zusatz){
	#ifdef DEBUG2
	printf("Net::handleError\n");
	#endif
	printf("NET:\tERROR:\tcode: %i\t",_ERROR);
	if(_ERROR >= 0 && _ERROR <= 6)
	{
		printf("Net::Net(int in,int hidX,int hidY,int out,int ani,float fac)\n    \t      \tParameter:\t");
	}
	switch(_ERROR)
	{
		case 1:	{ printf("in ist zu klein: %i",inputs);break;}
		case 2:	{ printf("hidX ist zu klein: %i",hiddenX);break;}
		case 3:	{ printf("hidY ist zu klein: %i",hiddenY);break;}
		case 4:	{ printf("out ist zu klein: %i",outputs);break;}
		case 5:	{ printf("ani ist zu klein: %i",animals);break;}
		
		case 7:	{ printf("setGenomOfAnimal(int animal,vector<float> _genom) animal out of range: %i",zusatz);break;}
		case 8:	{ printf("setGenom(vector<vector<float>	> _genom) _genom.size() out of range: %i",zusatz);break;}
		case 9:	{ printf("getGenomOfAnimal(int ani) ani out of range: %i",zusatz);break;}
		case 10:{ printf("setInputOnPos(int pos,float signal) pos out of range: %i",zusatz);break;}
		case 11:{ printf("saveData(char *_file) Die Datei konnte nicht geoeffnet werden");break;}
		case 12:{ printf("loadData(char *_file) Die Datei konnte nicht geoeffnet werden. Sie muss zuerst erstellt werden");break;}
		case 13:{ printf("loadData(char *_file) Die Datei entaelt falsche Netzwerk Konfiguration");break;}
		case 14:{ printf("run(int aditionalAnimal) aditionalAnimal out of range: %i",zusatz);break;}
		case 15:{ printf("learn(vector<float> fitness) fitness.size() out of range: %i",zusatz);break;}
		
		default:{ printf("UNKNOWN ERROR: %i",_ERROR);break;}
	}
	printf("\n");
}
#endif
//----------------------------------------------------------
