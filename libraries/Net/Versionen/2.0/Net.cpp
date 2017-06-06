//Autor Alex Krieg
//V2.1						
//30.5.2017

//Backpropagation
//Genetic




#include "Net.h"

//-----------------------------------NEURON-----------------------------
Neuron::Neuron(){
	result		= 0.0;
	error		= 0.0;
}
Neuron::~Neuron(){
	delete inputs;
	
}
void 	Neuron::setup(int in,float fac){
	a					= 0;
	b					= 0;
	c					= 0;
	d					= 0;
	
	factor 				= fac;
	anzInputs 			= in;
	inputs 				= new In[in+1];		//+1 -> BIAS
	inputs[in].data 	= 1.0;				//BIAS
	inputs[in].weight 	= (rand() %100)+1;
	inputs[in].weight 	= inputs[in].weight / 100;
	inputs[in].last_weight 	= inputs[in].weight ;
	for( a = 0; a<in; a++)
	{
		inputs[a].data 	= 0.0;	
		inputs[a].weight= (rand() %100)+1;		// Init Wert für das Gewicht aller Eingänge
		inputs[a].weight= inputs[a].weight/100;
		inputs[a].last_weight 	= inputs[a].weight ;
	}
	delete &in;
	delete &fac;
}
void 	Neuron::setInput(float DATA[]){
	for( a = 0; a<anzInputs; a++)
	{
		inputs[a].data = DATA[a];		//Set Inputs to the Input
	}
	result 	= 0.0;
	for( a = 0; a<anzInputs+1;a++)		//+1 -> BIAS
	{
		result = result + (inputs[a].weight * inputs[a].data);
	}
	#ifdef genetic
	result /= anzInputs+1;
	//------------Activation-Function--------
	
	result = ((1.0/(1.0+exp(-result)))-0.5)*2;
	//result = (1.0/(1+exp(-result)));
	#endif
	#ifdef backprop
	result = (1.0/(1.0+exp(-result)));
	#endif

	delete &DATA;
}
float 	Neuron::getOutput(){
	return result;
}
void 	Neuron::calculateError(float nextError[],int anzPins){
	error = 0.0;
	
	for( a = 0; a<anzPins; a++)
	{
		error = error + nextError[a];
	}
	error = error * result * (1-result);
	
	delete &nextError;
	delete &anzPins;
}
float 	Neuron::getErrorBack(int input){
	return error * inputs[input].weight;
}
void 	Neuron::changeWeights(float NetError){
	float tmp1 = 0.0;
	float tmp2 = 0.0;
	for( a = 0; a<anzInputs+1; a++)		// +1 -> BIAS
	{
		inputs[a].weight = inputs[a].weight + (inputs[a].data * inputs[a].last_weight * error *factor);
		inputs[a].last_weight = 1.0;
	}
	delete &tmp1;
	delete &tmp2;
}
//----------------------------------NET----------------------------------
#ifdef genetic 
Net::Net(int inputs,int hiddenX,int hiddenY,int outputs,int ani,float mutat){
#endif
#ifdef backprop
Net::Net(int inputs,int hiddenX,int hiddenY,int outputs,float fac){
#endif	
	
	//Für for() loops
	a					= 0;
	b					= 0;
	c					= 0;
	d					= 0;
	//---------------
	
	
	netError			= 0.0;
	hiddenUnitsY		= hiddenY;
	steps				= 0;
	#ifdef backprop
	factor 				= fac;
	#endif
	inputUnits			= inputs;
	hiddenUnitsX 		= hiddenX;
	outputUnits 		= outputs;
	FullOut				= new float[outputUnits];
	Myfile				= new FILE;
	//-------------Make-Genom----------------------
	#ifdef genetic 
	if(mutat != 0)
	{
		if(mutat > 1.0)
		{
			mutat = 1;
		}
		mutationRate 	= 1/mutat;
	}
	else
	{
		mutationRate = 0;
	}
	fitness			= 0.0;
	animals 		= ani;
	geneticSize 	= ((inputUnits+1) * hiddenUnitsX)+(((hiddenUnitsX+1)* hiddenUnitsX) * (hiddenUnitsY-1))+((hiddenUnitsX+1)*outputUnits); //Alle Gewichtungen hintereinander
	vector<float> tmpVecGen(geneticSize,0);	//Random Werte
	vector<float> tmpVecGenOut(geneticSize,0);
	for(b = 0; b<animals; b++)
	{
		FullOutOfAnimal.push_back(tmpVecGenOut);	//Erstellt Output Speicher der animals
		Genetic.push_back(tmpVecGen);				//Erstellt die random Genome
		for(a = 0; a<geneticSize; a++)
		{
			Genetic[b][a] = (rand() %100) +1;
			Genetic[b][a] = Genetic[b][a]/100;
		}
	}
	#endif
	//---------------------------------------------
	//-------------Make-Neurons--------------------		
	vector<Neuron> tmpVec(hiddenUnitsX,Neuron());
	for(a = 0; a<hiddenUnitsY; a++)
	{
		HiddenLayers.push_back(tmpVec);
	}
	
	OutputLayer 		= new Neuron[outputUnits];
	
	for(a = 0; a<hiddenUnitsX; a++)
	{
		HiddenLayers[0][a].setup(inputs,factor); 
	}
	for(a = 1; a<hiddenUnitsY; a++)
	{
		for(b = 0; b<hiddenUnitsX; b++)
		{
			HiddenLayers[a][b].setup(hiddenUnitsX,factor);
		}
	}
	for(a = 0; a<outputUnits; a++)
	{
		OutputLayer[a].setup(hiddenUnitsX,factor);	
	}
	
	delete &inputs;
	delete &hiddenX;
	delete &hiddenY;
	delete &outputs;
	#ifdef genetic
	delete &ani;
	delete &mutat;
	tmpVecGen.clear();
	tmpVecGenOut.clear();
	#endif
}
Net::~Net(){
	delete FullOut;
	delete OutputLayer;
	delete Myfile;
}
void Net::loadData(char* file){
	int tmpInput1 = 0;
	int tmpInput2 = 0;
	int tmpInput3 = 0;
	int tmpInput4 = 0;
	int tmpInput5 = 0;
	
	float tmp = 0.0;
	
  Myfile = fopen (file,"r");
   if (Myfile==NULL)
   {
	   printf("\nDatei exestiert nicht. Sie wird erstellt.\n");
   }
   else
   {
	  rewind (Myfile);
	  fscanf (Myfile, "%i", &tmpInput1);
	  fscanf (Myfile, "%i", &tmpInput2);
	  fscanf (Myfile, "%i", &tmpInput3);
	  fscanf (Myfile, "%i", &tmpInput4);
	  #ifdef genetic 
	  fscanf (Myfile, "%i", &tmpInput5);
	  #endif
	  
	  if((tmpInput1 == inputUnits) && (tmpInput2 == hiddenUnitsX) && (tmpInput3 == hiddenUnitsY) && (tmpInput4 == outputUnits))
	  {
		   #ifdef backprop
			printf("Input configuration: ok\n");
			for(a = 0; a<hiddenUnitsX; a++)
			{
				for(b = 0; b<inputUnits+1; b++)
				{
					fscanf (Myfile, "%f", &tmp);
					HiddenLayers[0][a].inputs[b].weight = tmp;
				}
			}
			for(c = 1; c<hiddenUnitsY; c++)
			{
				for(a = 0; a<hiddenUnitsX; a++)
				{
					for(b = 0; b<hiddenUnitsX+1; b++)
					{
						fscanf (Myfile, "%f", &tmp);
						HiddenLayers[c][a].inputs[b].weight = tmp;
					}
				}
			}
			for(a = 0; a<outputUnits; a++)
			{
				for(b = 0; b<hiddenUnitsX+1; b++)
				{
					fscanf (Myfile, "%f", &tmp);
					OutputLayer[a].inputs[b].weight = tmp;
				}
			}
			#endif
			#ifdef genetic
			if(tmpInput5 == animals)
			{
				for(a = 0; a < animals; a++)
				{
					for(b = 0; b<geneticSize; b++)
					{
						fscanf(Myfile, "%f ", &tmp);
						Genetic[a][b] = tmp;
					}
				}
			}
			else
			{
				printf("ERROR: Input data wrong confuguration");
				while(1)
				{}
			}
			#endif
			printf("Input done\n");
			Sleep(1000);
	  }
	  else
	  {
		  printf("ERROR: Input data wrong confuguration");
		  while(1)
		  {}
	  }
  
  }
  fclose (Myfile);
  
   delete &tmpInput1;
   delete &tmpInput2;
   delete &tmpInput3;
   delete &tmpInput4;
   delete &tmpInput5;
   delete &tmp;
   delete &file;
}
void Net::saveData(char* file){
	Myfile = fopen (file,"w");
	fprintf(Myfile ,"%i ", inputUnits);
	fprintf(Myfile ,"%i ", hiddenUnitsX);
	fprintf(Myfile ,"%i ", hiddenUnitsY);
	fprintf(Myfile ,"%i ", outputUnits);
	#ifdef genetic 
		fprintf(Myfile ,"%i ", animals);
	#endif
	fprintf(Myfile ,"\n");
	#ifdef backprop
	for(a = 0; a<hiddenUnitsX; a++)
	{
		for(b = 0; b<inputUnits+1; b++)
		{
			fprintf (Myfile, "%.8f ", HiddenLayers[0][a].inputs[b].weight);
		}
	}
	fprintf(Myfile ,"\n");
	if(hiddenUnitsY != 1)
	{
		for(c = 1; c<hiddenUnitsY; c++)
		{
			for(a = 0; a<hiddenUnitsX; a++)
			{
				for(b = 0; b<hiddenUnitsX+1; b++)
				{
					fprintf (Myfile, "%.8f ", HiddenLayers[c][a].inputs[b].weight);
				}
			}
			fprintf(Myfile ,"\n");
		}
	}
	for(a = 0; a<outputUnits; a++)
	{
		for(b = 0; b<hiddenUnitsX+1; b++)
		{
			fprintf (Myfile, "%.8f ", OutputLayer[a].inputs[b].weight);
		}
	}
	#endif
	#ifdef genetic
	for(a = 0; a < animals; a++)
	{
		for(b = 0; b<geneticSize; b++)
		{
			fprintf (Myfile, "%.8f ", Genetic[a][b]);
		}
		fprintf(Myfile ,"\n");
	}
	#endif
	fclose (Myfile);
	delete &file;
}
#ifdef backprop
void Net::setInputUnits(float input[]){
#endif
#ifdef genetic 
void Net::setInputUnits(float input[],int animal){
	
	c = animal;
	C1 = 0; 
	C2 = 0;
	C3 = 0;
		//--------------------------------Lade-Genom-in-das-Netzwerk-------------
		for(a = 0; a<hiddenUnitsX; a++)
		{
			for(b = 0; b<inputUnits+1; b++)
			{
				
				HiddenLayers[0][a].inputs[b].weight = Genetic[c][C1];				
				C1++;
				//Lädt die Gewichte der ersten Hidden Schicht
			}
		}
		for(d = 1; d<hiddenUnitsY; d++)
		{
			for(a = 0; a<hiddenUnitsX; a++)
			{
				for(b = 0; b<hiddenUnitsX+1; b++)
				{
					HiddenLayers[d][a].inputs[b].weight = Genetic[c][C1+C2];	
					C2++;
					//Lädt die Gewichte der restlichen Hidden Schichten
				}
			}
		}
		for(a = 0; a<outputUnits; a++)
		{
			for(b = 0; b<hiddenUnitsX+1; b++)
			{
				OutputLayer[a].inputs[b].weight = Genetic[c][C1+C2+C3];
				C3++;
				//Lädt die Gewichte der Output Schicht
			}
		}
		//------------------------------------------------------------------------
	#endif
		float tmp[hiddenUnitsY][hiddenUnitsX];
		for( a = 0; a<hiddenUnitsX; a++)	//Inputs to the first hidden unit
		{
			HiddenLayers[0][a].setInput(input);
			tmp[0][a] = HiddenLayers[0][a].getOutput();
		}
		for( a = 1; a<hiddenUnitsY; a++)	//Inputs to the first hidden unit
		{
			for( b = 0; b<hiddenUnitsX; b++)	//Inputs to the first hidden unit
			{
				HiddenLayers[a][b].setInput(tmp[a-1]);
				tmp[a][b] = HiddenLayers[a][b].getOutput();	
			}
		}
		for( a = 0; a<outputUnits; a++)	//OutputLayer
		{
			OutputLayer[a].setInput(tmp[hiddenUnitsY-1]);
			FullOut[a] = OutputLayer[a].getOutput();
		}
	#ifdef genetic 
		for(a = 0; a<outputUnits; a++)
		{
			FullOutOfAnimal[c][a] = FullOut[a]; 
		}
	
	#endif
	
	
	steps++;
	delete &input;
	#ifdef genetic
	delete &animal;
	#endif
}
void 	Net::debug(){
	int abstandRight = 1;

	COORD cord;
	//----------------------------------------------------------INPUTS
	cord.X = 0;	cord.Y = 5; //Start pos
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("INPUTS:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cord.X = 16;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	for(a=0;a<inputUnits; a++)
	{
		printf("%.3f ",HiddenLayers[0][0].inputs[a].data);//Inputs
	}
	//----------------------------------------------------------
	cord.Y+=2;
	//----------------------------------------------------------HIDDEN
	
	for(c = 0; c < hiddenUnitsY; c++)
	{
		cord.X = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("HIDDEN:");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cord.X = 16;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		for(a=0;a<hiddenUnitsX; a++)
		{
			if(c == 0)
			{
				for(b=0; b<inputUnits+1; b++)
				{
					printf("%.3f\t",HiddenLayers[c][a].inputs[b].data);
				}
			}
			else
			{
				for(b=0; b<hiddenUnitsX+1; b++)
				{
					printf("%.3f\t",HiddenLayers[c][a].inputs[b].data);
				}
			}
			cord.X = cord.X +8+((inputUnits+1) * 8);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		}
		cord.Y++;
		cord.X = 16;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		for(a=0;a<hiddenUnitsX; a++)
		{
			if(c == 0)
			{
				for(b=0; b<inputUnits+1; b++)
				{
					printf("--------");
				}
			}
			else
			{
				for(b=0; b<hiddenUnitsX+1; b++)
				{
					printf("--------");
				}
			}
			cord.X = cord.X +8+((inputUnits+1) * 8);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		}
		cord.Y++;
		cord.X=8;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		for(a=0;a<hiddenUnitsX; a++)
		{
			if(c == 0)
			{
				for(b=0; b<inputUnits+1; b++)
				{
					printf("\t%.3f",HiddenLayers[c][a].inputs[b].weight);
				}
			}
			else
			{
				for(b=0; b<hiddenUnitsX+1; b++)
				{
					printf("\t%.3f",HiddenLayers[c][a].inputs[b].weight);
				}
			}
			cord.X = cord.X +8+((inputUnits+1) * 8);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		}
		cord.Y++;
		cord.X=16;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		for(a=0;a<hiddenUnitsX; a++)
		{
			printf("%.3f",HiddenLayers[c][a].getOutput());
			
			cord.X = cord.X +8+((inputUnits+1) * 8);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		}
		cord.Y+=2;
	}
	
	//----------------------------------------------------------
	//cord.Y+=2;
	cord.X=0;
	//----------------------------------------------------------OUTPUTS
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("OUTPUT:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cord.X = 16;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	for(a=0;a<outputUnits; a++)
	{
		for(b=0; b<hiddenUnitsX+1; b++)
		{
			printf("%.3f\t",OutputLayer[a].inputs[b].data);
		}
		cord.X = cord.X +8+((hiddenUnitsX+1) * 8);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	}
	cord.Y++;
	cord.X = 16;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	for(a=0;a<outputUnits; a++)
	{
		for(b=0; b<hiddenUnitsX+1; b++)
		{
			printf("--------");
		}
		cord.X = cord.X +8+((hiddenUnitsX+1) * 8);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	}
	cord.Y++;
	cord.X=8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	for(a=0;a<outputUnits; a++)
	{
		for(b=0; b<hiddenUnitsX+1; b++)
		{
			printf("\t%.3f",OutputLayer[a].inputs[b].weight);
		}
		cord.X = cord.X +8+((hiddenUnitsX+1) * 8);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	}
	cord.Y++;
	cord.X=16;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	for(a=0;a<outputUnits; a++)
	{
		
		
		printf("%.3f",OutputLayer[a].getOutput());
		
		cord.X = cord.X +8+((hiddenUnitsX+1) * 8);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	}
	#ifdef backprop
	cord.X = 0;	cord.Y+= 5;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	printf("NetError:\t%.5f",netError);
	#endif
	cord.X = 0;	cord.Y = 2; //Start pos
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	//----------------------------------------------------------
	//delete &abstandRight;
}
#ifdef backprop
float 	Net::getOutput(int out){
#endif
#ifdef genetic
float 	Net::getOutput(int animal,int out){
#endif 
	#ifdef genetic
		return FullOutOfAnimal[animal][out];
	#endif
	#ifdef backprop
		return FullOut[out];
	#endif
}
#ifdef backprop
void 	Net::learn(float expactet[],int improve = 1){
#endif
#ifdef genetic
void 	Net::learn(float AnimalFitness[]){
#endif
	#ifdef backprop
		netError = 0.0;
		for( a = 0; a<outputUnits; a++)
		{
			OutputLayer[a].error = ((OutputLayer[a].getOutput()*(1-OutputLayer[a].getOutput())/*+(expactet[a]-OutputLayer[a].getOutput())*/*(expactet[a]-OutputLayer[a].getOutput())));
			netError+=(expactet[a]-OutputLayer[a].getOutput())*(expactet[a]-OutputLayer[a].getOutput());
		}
		if(improve == 1)
		{
			//-----------------------------------------Backpropagation---------------
			float tmp2[outputUnits];
			float tmp3[hiddenUnitsY+1][hiddenUnitsX];
			for( a = 0; a<hiddenUnitsX; a++)
			{
				for( b = 0; b<outputUnits; b++)
				{
					tmp2[b] = OutputLayer[b].getErrorBack(a);
				}
				HiddenLayers[hiddenUnitsY-1][a].calculateError(tmp2,outputUnits);
			}
			for( a = hiddenUnitsY-2; a>=0; a--)
			{
				for( b = 0; b<hiddenUnitsX; b++)
				{
					for( c = 0; c<hiddenUnitsX; c++)
					{
						tmp3[a][c] = HiddenLayers[a+1][c].getErrorBack(b);
					}
					HiddenLayers[a][b].calculateError(tmp3[a],hiddenUnitsX);
				}
			}
			for( a = 0; a<hiddenUnitsY; a++)
			{
				for( b = 0; b<hiddenUnitsX; b++)
				{
					HiddenLayers[a][b].changeWeights(netError);
				}
			}
			for(a = 0; a<outputUnits; a++)
			{
				OutputLayer[a].changeWeights(netError);
			}
			delete &tmp2;
			delete &tmp3;
			
			//-------------------------------------------------------------------------
		}
		delete &improve;
		delete &expactet;
		#endif 
		#ifdef genetic
		//---------------CROSSOVER--------------
		
//#define D	
		vector<vector<float>	> tmpGenetic;
		vector<float> tmpVecTmpGen(geneticSize,0);
		int crossoverRandom;
		int crossoverRandom2 = 0;
		float gs = 0.0;
		unsigned int gesamtScore 		= 0;
		float spinningScore 		= 0;
		float randomSelection1	= 0;
		float randomSelection2 	= 0;
		int 		 SelectedAnimal[2] = {-1,-1};
		#ifdef D
		system("cls");
		#endif
		for(a = 0; a < animals; a++)
		{
			gs +=  AnimalFitness[a];
			#ifdef D
				printf("%.5f\n", AnimalFitness[a]);
			#endif
			tmpGenetic.push_back(tmpVecTmpGen);
		}
		gesamtScore = gs*10;
		if(gesamtScore == 0)
		{
			printf("\nERROR: gamescore = 0 -> Net::learn()\n");
			while(1){}
		}
	
		#ifdef D
		printf("\n\ngesscore%i",gesamtScore);
		printf("    %.5f\n",gs);
		#endif
		C1 = 0;
		C2 = 0;
		e  = 0;

		for(a = 0; a < animals/2; a++)
		{
			b = 0;
			randomSelection1 = ((rand() % gesamtScore-10)/10)+1;
			randomSelection2 = ((rand() % gesamtScore-10)/10)+1;
			while(randomSelection1 > gesamtScore/10)
			{
				randomSelection1 = ((rand() % gesamtScore-10)/10)+1;
			}
			while(randomSelection2 > gesamtScore/10)
			{
				randomSelection2 = ((rand() % gesamtScore-10)/10)+1;
			}
			#ifdef D
			printf("Random1: %.1f\nRandom2: %.1f\n",randomSelection1,randomSelection2);
			#endif
			while(b == 0)
			{
				spinningScore = 0;
				for(c = 0; c < animals; c++)
				{
					if(randomSelection1 <= spinningScore+AnimalFitness[c] && randomSelection1 >= spinningScore)
					{
						SelectedAnimal[0] = c;
						#ifdef D
						printf("Selected Animal 1 1: %i\n",SelectedAnimal[0] );
						printf("Selected Animal 1 2: %i\n",SelectedAnimal[1] );
						#endif
						c = animals;
					}
					else
					{
						spinningScore+=AnimalFitness[c];
					}
				}
				spinningScore = 0;
				for(c = 0; c < animals; c++)
				{
					if(randomSelection2 <= spinningScore+AnimalFitness[c] && randomSelection2 >= spinningScore)
					{
						SelectedAnimal[1] = c;
						#ifdef D
						printf("Selected Animal 1: %i\n",SelectedAnimal[0] );	
						printf("Selected Animal 2: %i\n",SelectedAnimal[1] );
						#endif
						c = animals;
					}
					else
					{
						spinningScore+=AnimalFitness[c];
						#ifdef D
						printf("AnimalFitness: %.8f\n",AnimalFitness[c]);
						#endif
					}
				}
				if(SelectedAnimal[0] >= 0 && SelectedAnimal[1] >= 0)
				{
					#ifdef D		
					printf("Starting crossover\n");
				    #endif
					//Crosover
					int randCrossoverPoint;
					int buffCrossoverPoint;
					for(d = 0; d<2; d++)	// 2 animals
					{
						if(d == 0)
						{
							randCrossoverPoint= rand() %geneticSize;
							buffCrossoverPoint= 0;
						}
						else
						{
							randCrossoverPoint= geneticSize;
							buffCrossoverPoint= rand() %geneticSize;
						}
						#ifdef D
								
						printf("\nCrossover random: %i\nCross:\n",randCrossoverPoint);
						printf("Save in Animal: %i\n", C1);
						#endif
						for(e = 0; e<2; e++)	//2 genteilungen
						{
							for(c = buffCrossoverPoint; c < randCrossoverPoint; c++)
							{
								tmpGenetic[C1][c] = Genetic[SelectedAnimal[e]][c];
							}
							if(d == 0)
							{
								buffCrossoverPoint = randCrossoverPoint;
								randCrossoverPoint = geneticSize;
							}
							else
							{
								randCrossoverPoint = buffCrossoverPoint;
								buffCrossoverPoint = 0;
							}
						}
						C1++;
						if(C1 > animals)
						{
							printf("ERROR: C1 >= animals\n");
						}
					}
					delete &randCrossoverPoint;
					delete &buffCrossoverPoint;
					b = animals;
				}
				if(b == 0)
				{
					printf("rand1: %.3f \nrand2: %.3f\n",randomSelection1,randomSelection2);
					randomSelection1 = ((rand() % gesamtScore-10)/10)+1;
					randomSelection2 = ((rand() % gesamtScore-10)/10)+1;
				}
			}
		}
		for(a = 0; a < animals; a++)
		{
			for(b = 0; b < geneticSize; b++)
			{
				Genetic[a][b] = tmpGenetic[a][b];
			}
		}

		tmpGenetic.clear();
		tmpVecTmpGen.clear();;
		delete &crossoverRandom;
		//--------------------------------------
		//---------------MUTATION---------------
		if(mutationRate != 0)
		{
			float mutationRange;
			float tmpMutation = 0.0;
			for(a = 0; a < animals; a++)
			{
				for(b = 0; b < geneticSize; b++)
				{
					mutationRange = (rand() %(mutationRate));
					
					if(mutationRange == 0)
					{
						tmpMutation = (rand()%100)-50;	//Mutiert zu random wert
						Genetic[a][b] += tmpMutation /10000;
					}
				}
			}
		}
		//--------------------------------------
	#endif
}
#ifdef genetic
vector<float> Net::getGen(int genNR)
{
	return Genetic[genNR];
}
void Net::setGen(int genNR,vector<float> genData)
{
	Genetic[genNR] = genData;
	delete &genData;
}
#endif
