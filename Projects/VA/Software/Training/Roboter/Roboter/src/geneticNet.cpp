/*
Autor 		Alex Krieg
Version 	0.3.1
Datum		25.11.2017
*/

#include "geneticNet.h"


geneticNet::geneticNet(int in,int hidX,int hidY,int out,int ani,float fac,bool _bias,bool enaAver)
	: Net(in,hidX,hidY,out,_bias,enaAver)
{
	_GENETIC_NET_VERSION	= to_string(GENETIC_NET_VERSION);
	animals					= ani;
	currentAnimal			= 0;
	mutationChangeDivisor	= 10000;
	mutationFactor(fac);
	if(checkForWrongParam())
	{
		return;
	}
	_genom 					= vector<vector<float>	>(animals,vector<float>(_weightSize,0));
	for(int a=0; a<animals; a++)
	{
		float tmp;
		for(int b=0; b<_weightSize; b++)
		{
			tmp = randEngine()%200;
			_genom[a][b] = (tmp-100)/100;
		}
	}
	_networkConfiguration	= networkConfiguration();
	loadGenomOfAnimal();
}
	
	
	geneticNet::~geneticNet(){}
void 			geneticNet::mutationFactor(float fac)
{
    if(fac > 0)
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
}
float			geneticNet::mutationFactor()
{
	if(mutFactor == 0)
	{
		return 0;
	}
    return 1/(float)mutFactor;
}
bool 			geneticNet::saveData(string name){
	#ifdef DEBUG2
	printf("geneticNet::saveData\n");
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
	//fprintf(file,"genetic\n");
	for(int a=0; a<animals; a++)
	{
		for(int b=0; b<_weightSize; b++)
		{
			fprintf(file,"%.8f ",_genom[a][b]);
		}
		fprintf(file,"\n");
	}
	fclose(file);
	return 0;
}
int		geneticNet::loadData(string name){
	#ifdef DEBUG2
	printf("geneticNet::loadData\n");
	#endif
	string tmpNetCheck = "";
	
	file = fopen(name.c_str(),"r");
	//printf("open file: %s\n",name.c_str());
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
	//printf("if( %s != %s)\n",tmpNetCheck.c_str(),_networkConfiguration.c_str());
	//if(tmpNetCheck != _networkConfiguration)
	if(tmpNetCheck != _networkConfiguration)
	{
		printf("!=\n");
		#ifdef DEBUG
		handleError(13);
		#endif
		fclose(file);
		return 1;
	}
	for(int a=0; a<animals; a++)
	{
		for(int b=0; b<_weightSize; b++)
		{
			fscanf(file,"%f",&_genom[a][b]);
		}
	}
	fclose(file);
	loadGenomOfAnimal();
	return 0;
}	
void			geneticNet::learn(vector<float> fitness){
//#define DEBUG2
//#define DEBUG_FILE
#ifdef DEBUG_FILE
      bool onlyOne = true;
      FILE *dbgFile;
      dbgFile = fopen("learn_dbg.txt","w");
      fclose(dbgFile);
#endif


	#ifdef DEBUG2
	printf("geneticNet::learn\n");
	#endif
	if(fitness.size()!=animals)
	{
		#ifdef DEBUG
		handleError(14,fitness.size());
		#endif
#ifdef DEBUG_FILE
        dbgFile = fopen("learn_dbg.txt","a");
        fprintf(dbgFile,"handleError(14,fitness.size()); fitness.size(): %i\n",fitness.size());
        fclose(dbgFile);
#endif
		return;
	}
	vector<vector<float>	>	tmpGenetic = _genom;
    int counter = 0;
	for(int x=0; x<animals/2; x++)
	{
#ifdef DEBUG_FILE
        dbgFile = fopen("learn_dbg.txt","a");
        fprintf(dbgFile,"------------------------ X: %i -----------------------------\n",x);
        fclose(dbgFile);
#endif

		float gesFitnessF = 0;
		int gesFitnessI;
		float randomPos1;
		float randomPos2;
		int randomSelection1;
		int randomSelection2;
		for(int a=0; a<animals; a++)
		{
#ifdef DEBUG_FILE
                  if(onlyOne)
                  {
        dbgFile = fopen("learn_dbg.txt","a");
        fprintf(dbgFile,"   gesFitnessF: %.8f += fitness[%i]: %.8f ;",gesFitnessF,a,fitness[a]);
        fclose(dbgFile);
                  }
#endif
			gesFitnessF += fitness[a]; //Berechne gesamte Fitness
#ifdef DEBUG_FILE
                        if(onlyOne)
                        {
        dbgFile = fopen("learn_dbg.txt","a");
        fprintf(dbgFile," = %.8f\n",gesFitnessF);
        fclose(dbgFile);
                        }
#endif

		}
		#ifdef DEBUG2
		printf("Net::learn->gesFitnessF: %.8f\n",gesFitnessF);
		#endif
		gesFitnessI = gesFitnessF;
#ifdef DEBUG_FILE
                onlyOne = false;
        dbgFile = fopen("learn_dbg.txt","a");
        fprintf(dbgFile,"gesFitnessI: %i = gesFitnessF: %.8f;\n",gesFitnessI,gesFitnessF);
        fclose(dbgFile);
#endif
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
								 |--> Random Selektion �ber das gesamte Specktrum
									  Selektiert wurde GENOM 3.
									  Das GENOM mit der h�chsten "fitness" hat die gr�ste chance selektiert zu werden 
		
		*/
		//-------------------------------------------------------------------------Selektiere Animal 1

        randomPos1 = randEngine()%(gesFitnessI*10);
#ifdef DEBUG_FILE
        dbgFile = fopen("learn_dbg.txt","a");
        fprintf(dbgFile,"randomPos1: %.8f\n",randomPos1);
        fclose(dbgFile);
#endif
		randomPos1 /= 10;
#ifdef DEBUG_FILE
        dbgFile = fopen("learn_dbg.txt","a");
        fprintf(dbgFile,"/=10 -> randomPos1: %.8f\n",randomPos1);
        fclose(dbgFile);
#endif
		for(int a=0; a<animals; a++)
		{
			if(randomPos1<gesFitnessF+fitness[a] && randomPos1>=gesFitnessF)
			{
				randomSelection1 = a;
#ifdef DEBUG_FILE
                dbgFile = fopen("learn_dbg.txt","a");
                fprintf(dbgFile,"   randomSelection1: %i\n",randomSelection1);
                fprintf(dbgFile,"   gesFitnessF: %.8f +fitness[%i]: %.8f = %.8f\n",gesFitnessF,a,fitness[a],gesFitnessF+fitness[a]);
                fclose(dbgFile);
#endif
				a				 = animals;
			}
			gesFitnessF+=fitness[a];
#ifdef DEBUG_FILE
            if(gesFitnessF == 0)
            {
                dbgFile = fopen("learn_dbg.txt","a");
                fprintf(dbgFile,"   gesFitnessF == 0\ngesFitnessF: %.8f +=fitness[%i]: %.8f ;\n",gesFitnessF,a,fitness[a]);
                fclose(dbgFile);
            }
#endif
		}
		randomPos2 = randEngine()%(gesFitnessI*10);
#ifdef DEBUG_FILE
        dbgFile = fopen("learn_dbg.txt","a");
        fprintf(dbgFile,"   randomPos2: %.8f\n",randomPos2);
        fclose(dbgFile);
#endif
		randomPos2 /= 10;
#ifdef DEBUG_FILE
        dbgFile = fopen("learn_dbg.txt","a");
        fprintf(dbgFile,"   randomPos2: %.8f\n",randomPos2);
        fclose(dbgFile);
#endif

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
#ifdef DEBUG_FILE
                    dbgFile = fopen("learn_dbg.txt","a");
                    fprintf(dbgFile,"       randomSelection2: %i\n",randomSelection2);
                    fprintf(dbgFile,"       gesFitnessF: %.8f +fitness[%i]: %.8f = %.8f\n",gesFitnessF,a,fitness[a],gesFitnessF+fitness[a]);
                    fclose(dbgFile);
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
#ifdef DEBUG_FILE
                dbgFile = fopen("learn_dbg.txt","a");
                fprintf(dbgFile,"randomPos2: %.8f\n",randomPos2);
                fclose(dbgFile);
#endif
				randomPos2 /= 10;
#ifdef DEBUG_FILE
                dbgFile = fopen("learn_dbg.txt","a");
                fprintf(dbgFile,"/=10 -> randomPos2: %.8f\n---------------------------------\n",randomPos2);
                fclose(dbgFile);
#endif
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
		int randomCrossoverPoint = 1+((randEngine())%(_weightSize-1));	//Crossover Break Position
#ifdef DEBUG_FILE
                dbgFile = fopen("learn_dbg.txt","a");
                fprintf(dbgFile,"---crossover---\n");
                fprintf(dbgFile,"randomCrossoverPoint: %i\n",randomCrossoverPoint);
                fprintf(dbgFile,"randomSelection1: %i\n",randomSelection1);
                fprintf(dbgFile,"randomSelection2: %i\n",randomSelection2);
                fclose(dbgFile);
#endif
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
		vector<float>	tmpGenom1(_weightSize,3);
		vector<float>	tmpGenom2(_weightSize,3);
		#ifdef DEBUG2
		printf("Net::learn->Crossover -> randomCrossoverPoint: %i randomSelection1: %i randomSelection2: %i\n",randomCrossoverPoint,randomSelection1,randomSelection2);
		#endif
#ifdef DEBUG_FILE
                dbgFile = fopen("learn_dbg.txt","a");
                fprintf(dbgFile,"select1: %i\t->",randomSelection1);
                for(int a=0; a<_weightSize; a++)
                {
                   fprintf(dbgFile,"%.5f\t",_genom[randomSelection1][a]);
                }
                fprintf(dbgFile,"\select2: %i\t->",randomSelection2);
                for(int a=0; a<_weightSize; a++)
                {
                   fprintf(dbgFile,"%.5f\t",_genom[randomSelection2][a]);
                }
                fprintf(dbgFile,"\n          \t");
                //fclose(dbgFile);
#endif
		for(int a=0; a<_weightSize-randomCrossoverPoint; a++)
		{
			tmpGenom1[a] = _genom[randomSelection1][a];
			tmpGenom2[a] = _genom[randomSelection2][a];
#ifdef DEBUG_FILE
			//dbgFile = fopen("learn_dbg.txt","a");
			fprintf(dbgFile,"%.5f\t",tmpGenom1[a]);
#endif
		}
#ifdef DEBUG_FILE
		fprintf(dbgFile,"\n          \t");
		for(int a=0; a<_weightSize-randomCrossoverPoint; a++)
		{
		    fprintf(dbgFile,"%.5f\t",tmpGenom2[a]);
		}
		fprintf(dbgFile,"\n\n          \t");
#endif
		for(int a=_weightSize-randomCrossoverPoint; a<_weightSize; a++)
		{
			tmpGenom1[a] = _genom[randomSelection2][a];
			tmpGenom2[a] = _genom[randomSelection1][a];
#ifdef DEBUG_FILE
			//dbgFile = fopen("learn_dbg.txt","a");
			fprintf(dbgFile,"%.5f\t",tmpGenom1[a]);
#endif
		}
#ifdef DEBUG_FILE
		fprintf(dbgFile,"\n          \t");
		for(int a=0; a<_weightSize-randomCrossoverPoint; a++)
		{
		    fprintf(dbgFile,"%.5f\t",tmpGenom2[a]);
		}
		fprintf(dbgFile,"\n");
		fprintf(dbgFile,"fill it to %i and %i\n",counter,counter+1);
		fprintf(dbgFile,"---end crossover---\n");
		fclose(dbgFile);
#endif
        //tmpGenetic[randomSelection1] = tmpGenom1;
        //tmpGenetic[randomSelection2] = tmpGenom2;

        tmpGenetic[counter] = tmpGenom1;
        counter++;
        tmpGenetic[counter] = tmpGenom2;
        counter++;
		#ifdef DEBUG2
		printf("Net::learn->Crossover end\n");
		#endif
		//--------------------------------------------------------------------------------------------	
	}
	_genom = tmpGenetic;

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
				
				
				
				Je gr�sser der Faktor "mutFactor" ist desto �fters ist ein bestimmtes Geen betroffen.
				Zu hoher "mutFactor" bedeutet, dass das Netzwerk nicht lernen kann da es mehr Brute force w�re.
				Zu kleiner "mutFactor" bedeutet, dass das Netzwerk sz langsam lernt und darum l�nger ben�tigt.
		
		*/
	#ifdef DEBUG2
	printf("Net::learn->Mutation\n");
	#endif
	if(mutFactor != 0)
	{
		int doMutate;
		for(int a=0; a<animals; a++)
		{
			for(int b=0; b<_weightSize; b++)
			{
				doMutate = randEngine() % mutFactor;
				if(doMutate == 0)
				{
					float tmp = randEngine()%100;
					_genom[a][b] += (tmp-50)/mutationChangeDivisor;
				}
			}
		}
	}
	#ifdef DEBUG2
	printf("Net::learn->Mutation end\n");
	#endif
		//--------------------------------------------------------------------------------------------
}
void			geneticNet::genom(int animal,vector<float> _Genom){
	#ifdef DEBUG2
	printf("geneticNet::setGenomOfAnimal\n");
	#endif
	if(animal<0 || animal>=animals)
	{
		#ifdef DEBUG 
		handleError(6,animal);
		#endif 
		return;
	}
	if(_Genom.size() != _genom[animal].size())
	{
		#ifdef DEBUG 
		handleError(7,_Genom.size());
		#endif 
		return;
	}
	_genom[animal] = _Genom;
	if(animal == 0)
	{
		loadGenomOfAnimal();
	}
}
void			geneticNet::genom(vector<vector<float>	> _Genom){
	#ifdef DEBUG2
	printf("geneticNet::setGenom\n");
	#endif
	if(animals != _Genom.size())
	{
		#ifdef DEBUG 
		handleError(8,_Genom.size());
		#endif 
		return;
	}
	if(_genom[0].size() != _Genom[0].size())
	{
		#ifdef DEBUG 
		handleError(9,_Genom[0].size());
		#endif 
		return;
	}
	_genom = _Genom;
	loadGenomOfAnimal();
}
vector<float>	geneticNet::genom(int ani){
	#ifdef DEBUG2
	printf("geneticNet::getGenom(%i)\n",ani);
	#endif
	
	if(ani<0 || ani>=animals)
	{
		#ifdef DEBUG 
		handleError(10,ani);
		#endif 
		return _genom[0];;
	}
	//printf("\n\n\n\nNet::getGenomOfAnimal(%i)  genom.size() = %i %i\n",ani,genom[1].size(),genom[99].size());
	return _genom[ani];
}
vector<vector<float>	>geneticNet::genom(){
	#ifdef DEBUG2
	printf("geneticNet::getGenom\n");
	#endif
	return _genom;
}
void 			geneticNet::loadGenomOfAnimal(){
	#ifdef DEBUG2
	printf("geneticNet::loadGenomOfAnimal\n");
	#endif
	weightOfNet(_genom[currentAnimal]);
}
bool 			geneticNet::checkForWrongParam(){
	#ifdef DEBUG2
	printf("geneticNet::checkForWrongParam\n");
	#endif
	bool err = 0;
	if(animals <= 0)
	{
		#ifdef DEBUG 
		handleError(5);
		#endif 
		err = 1;
	}
	return err;
}
void 			geneticNet::mutationDivisor(float val){
	if(val > 0)
	{
		mutationChangeDivisor = val;
	}
}
float 			geneticNet::mutationDivisor()
{
  return mutationChangeDivisor;
}

void 			geneticNet::animal(unsigned int animalNr)
{
	if(animalNr>= animals)
	{
		animalNr = animals-1;
	}
	currentAnimal = animalNr;
	loadGenomOfAnimal();
}
unsigned int	geneticNet::animal()
{
	return currentAnimal;
}
string 			geneticNet::networkConfiguration()
{
	return "genetic_V"+_GENETIC_NET_VERSION+"_V"+_NET_VERSION+"_"+to_string(inputs)+"_"+to_string(hiddenX)+"_"+to_string(hiddenY)+"_"+to_string(outputs)+"_"+to_string(animals)+"_"+to_string(bias);
}
#ifdef DEBUG
void 			geneticNet::handleError(int _ERROR,int zusatz){
	#ifdef DEBUG2
	printf("geneticNet::handleError\n");
	#endif
	printf("NET:\tERROR:\tcode: %i\t",_ERROR);
	if(_ERROR >= 0 && _ERROR <= 5)
	{
		printf("geneticNet::geneticNet(int in,int hidX,int hidY,int out,int ani,float fac,bool _bias,bool enaAver)\n    \t      \tParameter:\t");
	}
	switch(_ERROR)
	{
		case 5:	{ printf("ani ist zu klein: %i",animals);break;}
		case 6:	{ printf("setGenom(int animal,vector<float> _genom) animal out of range: %i",zusatz);break;}
		case 7: { printf("setGenom(int animal,vector<float> _genom) _genom.size() != genom.size() %i",zusatz);break;}
		case 8:	{ printf("setGenom(vector<vector<float>	> _genom) _genom.size() out of range: %i",zusatz);break;}
		case 9: { printf("setGenom(vector<vector<float>	> _genom) _genom[0].size() out of range: %i",zusatz);break;}
		case 10:{ printf("getGenomOfAnimal(int ani) ani out of range: %i",zusatz);break;}
		case 11:{ printf("saveData(char *_file) Die Datei konnte nicht geoeffnet werden");break;}
		case 12:{ printf("loadData(char *_file) Die Datei konnte nicht geoeffnet werden. Sie muss zuerst erstellt werden");break;}
		case 13:{ printf("loadData(char *_file) Die Datei enthaelt falsche Netzwerk Konfiguration");break;}
		case 14:{ printf("learn(vector<float> fitness) fitness.size() out of range: %i",zusatz);break;}
	
		default:{ printf("UNKNOWN ERROR: %i",_ERROR);break;}
	}
	printf("\n");
}
#endif

