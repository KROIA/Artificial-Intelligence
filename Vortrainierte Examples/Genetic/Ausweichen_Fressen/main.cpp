/*
 
Autor 	Alex Krieg
Datum  	27.6.2017
Version 5.42



*/
const float VERSION = 5.42;
#include "E:\Users\Alex\Documents\C++\libraries\Net\Net.h"
#include "E:\Users\Alex\Documents\C++\libraries\Net\Net.cpp"
#include "E:\Users\Alex\Documents\C++\libraries\timer\timer.h"
#include "E:\Users\Alex\Documents\C++\libraries\timer\timer.cpp"




#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


#define NETWORK
//#define CHECK
//#define DBUGALL

using namespace std;

//------------------MAP-------------------
unsigned int mapSize = 20;
int death = 0;
int steps = 0;
int food = 10;
int food_Config = 10;
int foodAmount = 10;
int feedAmount = 10;
int obsticleAmount = 10;
int direction = 0;
int direction_Config = 0;
vector<vector<unsigned int>	>	map;
vector<vector<unsigned int>	>	lastMap;
//----------------------------------------

//-----------------------NETWORTK-------GLOBAL------------------



unsigned int animals = 100;

unsigned int inputs 	= 10; //Window size
unsigned int hiddenX 	= 8;
unsigned int hiddenY 	= 1;
unsigned int outputs 	= 4; //Control
float mutation		 	= 0.1;

unsigned int stopTimeLearn 	= 1500;
unsigned int stopTimeTest 	= 120000;


//------------------------------------------------------------------

int a = 0;
int b = 0;
int c = 0;
int d = 0;
Timer T3;
Timer T1;
Timer genPerSecondtimer;
Timer timer;

FILE *file;
char xxa[10] = {'a','.','t','x','t'};	//Netzwerk Konfiguration
unsigned int generation 			= 0;
unsigned int pauseGen				= 0;
unsigned int pauseIntervallFile 	= 10;
unsigned int averageSize 			= 100;
float *durchschnitt;
float gesFitness 					= 0.0;
float lastBestFitness 				= 0.0;
int countIllegalMoves 				= 0;
unsigned int maxIllegalMoves 		= 3;
unsigned int guiUpdate	 			= 300;
unsigned int TestMode 				= 0; 
unsigned int TestModeSpeed 			= 100;
unsigned int saveBiggestIntervall 	= 100;
unsigned int lastSaveBiggest 		= 0;
vector<float> bestGen;
int updateBestGen 					= 0;
const int	animalViewMapSize		= 7;
int exitProg						= 0;
int testModeAnimal					= 0;
int loopsPerAnimal					= 1;
int loopsPerAnimalConfig			= 1;
int genPerSecond					= 0;
int genPerSecondCount				= 0;
int starved							= 0;
int skip							= 0;


int animalViewMap[animalViewMapSize][animalViewMapSize] = {
{0,0,0,1,0,0,0},
{0,0,0,1,0,0,0},
{0,0,1,1,1,0,0},	
{0,0,1,8,1,0,0},
{0,0,1,1,1,0,0},
{0,0,0,0,0,0,0},
{0,0,0,0,0,0,0}
};
float 	*animalMapView;
int   	*animalMapViewI;
int 	animalPos[2];
int 	lastAnimalPos[2][2];
//------------------------------------------------------------------

//----------------------------GAMES---------------------------------
float 	*fitness;
float 	*controls;
int geneticSize = ((inputs+1) * hiddenX)+(((hiddenX+1)* hiddenX) * (hiddenY-1))+((hiddenX+1)*outputs); //Alle Gewichtungen hintereinander
//------------------------------------------------------------------



COORD C_COORD;
COORD DE_COORD;

Net *calcNet;


void HandleNet(int animal);
void Control(float c1,float c2,float c3,float c4,int offsetX,int offsetY);
void getMapData();
void checkForCollision();
void drawMap(int offsetX,int offsetY);
void drawNet(int offsetX,int offsetY);
void setRandomStartPos();
void newFoodLocation();
void randomizeFoodLocation();
void writeConfig();
void readConfg();
void saveBest();
void setupMapView();
void saveFile();
void handleKeyBoeard(int whileForKey);

void startNet(int i)
{
	float tmpFitness = 0;
	skip = 0;
	int loopsPerAnimalCounter = 0;
	
	for(loopsPerAnimalCounter = 0; loopsPerAnimalCounter < loopsPerAnimal; loopsPerAnimalCounter++)
	{
		randomizeFoodLocation();
		for(a = 0; a<mapSize; a++)
		{
			for(b = 0; b<mapSize; b++)
			{
				lastMap[a][b] = -1;
			}
		}
		setRandomStartPos();
		countIllegalMoves = 0;
		direction = direction_Config;
		food = food_Config;
		death = 0;
		starved = 0;
		steps = 0;
		checkForCollision();
	
		if(TestMode >= 1)
		{
			while(death == 0)
			{
				if(timer.start(stopTimeTest))
				{
					death = 1;
				}
				HandleNet(i);
				handleKeyBoeard(0);
				if(TestMode == 0)
				{
					death = 1;
					timer.stop();
					return;
				}
				if(skip == 0)
				{
					Sleep(TestModeSpeed);
				}
			}
		}
		else
		{
			while(death == 0)
			{
				if(timer.start(stopTimeLearn))
				{
					death = 1;
				}
				HandleNet(i);
			}
		}
		HandleNet(i);
		timer.stop();
		tmpFitness += fitness[i];
	}
	fitness[i] = tmpFitness / loopsPerAnimal;
	if(fitness[i]==0)
	{
		fitness[i] = 0.01;
	}
	
}
void draw(){
	C_COORD.X = 38;
	C_COORD.Y = 6;
	
	
	DE_COORD.X = 0;
	DE_COORD.Y = 0;
	system("cls");
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),DE_COORD);
	printf("+-----------------------------NETWORK----VERSION: %.2f -----------------+\n",VERSION);
	printf("       Inputs:       %i\t         FileIntervall:     %i\n",inputs,pauseIntervallFile);
	printf("       Hidden X:     %i\t         Animals:           %i\n",hiddenX,animals);
	printf("       Hidden Y:     %i\t         MutationRate:      %.4f\n",hiddenY,mutation);
	printf("       Outputs:      %i\t  \n",outputs);
	printf("+-----------------------------------------------------------------------+");
	DE_COORD.Y = 6;
	#ifdef DE
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),DE_COORD);
	printf("Abschnitt:\n");
	printf("------------------------    |\n");
	printf("Run net-----------------    |\n");
	printf("Learn ------------------    |\n");
	printf("Debug ------------------    |\n");
	printf("PAUSE ------------------    |\n");
	printf("Write File -------------    |\n");
	printf("End --------------------    |\n");
	printf("----------------------------|\n");
	
	DE_COORD.X = 15;
	DE_COORD.Y = 6;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),DE_COORD);
	printf("Position:    |");
	DE_COORD.X = 25;
	#endif
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),C_COORD);
	printf("|Data:");
	for(a = 0; a<12; a++)
	{
		C_COORD.Y++;
		SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),C_COORD);
		printf("|");
	}
	C_COORD.X = 40;
}
int main()
{

	 
	
	file = new FILE();
	srand(time(NULL));
	//--------------SETUP
	readConfg();
	writeConfig();
	
	calcNet = new Net(inputs,hiddenX,hiddenY,outputs,animals,mutation);
	
	calcNet->loadData(xxa);
	calcNet->saveData(xxa);
	loopsPerAnimal = loopsPerAnimalConfig;
	//-------------------
	
	
	//-------------INIT---
	animalMapView	= new float[inputs];
 	animalMapViewI  = new int[inputs];
	vector<unsigned int>	tmpVec1(mapSize,0);
	controls		= new float[outputs];
	geneticSize 	= ((inputs+1) * hiddenX)+(((hiddenX+1)* hiddenX) * (hiddenY-1))+((hiddenX+1)*outputs);
	bestGen 		= vector<float> (geneticSize,0);
	fitness 		= new float[animals];
	durchschnitt 	= new float[averageSize];
	

	for(a = 0; a<animals; a++)
	{
		fitness[a] = 0;
	}
	for(a = 0; a<averageSize; a++)
	{
		durchschnitt[a] = 0;
	}
	for(a = 0; a<mapSize; a++)
	{
		map.push_back(tmpVec1);
		lastMap.push_back(tmpVec1);
	}
	file = fopen("gen.txt","r");
	if (file!=NULL)
	{
	   fscanf(file,"%i",&generation);
	   for(a = 0; a<averageSize; a++)
	   {
		   fscanf(file,"%f",&durchschnitt[a]);
	   }
	}
	fclose(file);
	file = fopen("best.txt","r");
	fscanf(file,"%f",&lastBestFitness);
	fclose(file);
	//--------------------
	
	b = 0;
	float tmpFitness = 0;
	int   abc = 0;
	int xs = 0;
	int as = 0;
	//system("cls");
	setupMapView();
	draw();
	while(exitProg == 0)
	{
		if(TestMode >= 1)
		{
			draw();
			
			startNet(testModeAnimal);
			if(TestMode >= 1)
			{
				handleKeyBoeard(1);	
			}
			testModeAnimal++;
			if(testModeAnimal == animals)
			{
				testModeAnimal = 0;
			}
		}
		else
		{
			for(xs = 0; xs < animals; xs++)
			{
				startNet(xs);
			}
			calcNet->learn(fitness);	
			generation++;
			genPerSecondCount++;
			gesFitness = 0;
			for(a = 0; a<animals; a++)
			{
					gesFitness+=fitness[a];
					
			}
			gesFitness/=animals;
			for(as = 0; as < averageSize-1; as++)
			{
				durchschnitt[as] = durchschnitt[as+1];
			}
			durchschnitt[averageSize-1] = gesFitness;
			for(as = 0; as < averageSize-1; as++)
			{
				durchschnitt[0] += durchschnitt[as];
			}
			durchschnitt[0] /=  averageSize;
			if(genPerSecondtimer.start(1000))
			{
				genPerSecond = genPerSecondCount;
				genPerSecondCount = 0;
			}
			if(T3.start(guiUpdate) && TestMode == 0)
			{
				C_COORD.Y = 8;
				SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),C_COORD);	C_COORD.Y ++;
				printf("Gen / sec:\t%i  ",genPerSecond);
				SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),C_COORD);	C_COORD.Y ++;
				printf("Generation:\t%i",generation);
				SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),C_COORD);	C_COORD.Y ++;
				printf("Score:\t\t%.4f \n",gesFitness);
				SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),C_COORD);	C_COORD.Y ++;
				printf("Durchschnitt:\t%.4f",durchschnitt[0]);
				SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),C_COORD);	C_COORD.Y ++;
				printf("Net Data:\t");
				for(a = 0; a<outputs; a++)
				{
						printf("%.3f\t",controls[a]);
				}
			}
			if((generation - pauseGen) >= pauseIntervallFile)
			{
					
				pauseGen = generation;			
				saveFile();
				
			}
			saveBest();
			handleKeyBoeard(0);
		}
	}
	return 0;
}

void HandleNet(int animal)
{
	if(death == 1)
	{
			fitness[animal] = steps+food;
			if(TestMode >= 1)
			{
				drawMap(0,20);
				drawNet(mapSize+15,20);
			}
	}
	else
	{
		getMapData();
	
		if(TestMode >= 1)
		{
			drawMap(0,20);
			drawNet(mapSize+15,20);
		}
		calcNet->setInputUnits(animalMapView,animal);
		for( a = 0; a < outputs; a++)
		{
			controls[a] = calcNet->getOutput(animal,a);
		}
		Control(controls[0],controls[1],controls[2],controls[3],mapSize+15,(inputs/10)+29);
		food-=1;
		if(food <= 0)
		{
			death = 1;
			starved = 1;
		}
		checkForCollision();
		if(TestMode >= 1)
		{
			drawMap(0,20);
			drawNet(mapSize+15,20);
		}
		for(a = 0; a<mapSize; a++)
		{
			for(b = 0; b<mapSize; b++)
			{
				lastMap[a][b] = map[a][b];
			}
		}
		//calcNet->debug();
	}
}
void Control(float c1,float c2,float c3,float c4,int offsetX,int offsetY)
{
	COORD coord;
	coord.X = offsetX;//X-->
	coord.Y = offsetY;//Yv
	char in = 0;
	if(TestMode != 2)
	{
		if((c1 + c2) > (c3 + c4))
		{
			if(c1 > c2)
			{
				in = KEY_UP;
			}
			else
			{
				in = KEY_DOWN;
			}
		}
		else
		{
			if(c3 > c4)
			{
				in = KEY_LEFT;
			}
			else
			{
				in = KEY_RIGHT;
			}
		}
	}
	else
	{
		while(in != KEY_UP && in != KEY_DOWN && in != KEY_LEFT && in != KEY_RIGHT)
		{
			in = getch();
		}
	}
	if(TestMode >= 1)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE ),coord);
		printf("KEY:\t\t");
	}
	lastAnimalPos[0][0] = lastAnimalPos[1][0];
	lastAnimalPos[0][1] = lastAnimalPos[1][1];
	lastAnimalPos[1][0] = animalPos[0];
	lastAnimalPos[1][1] = animalPos[1];
	switch(in)
	{
		case KEY_UP:
		{
			direction = direction;
			if(TestMode >= 1)
			{
				printf("  UP  ");
			}
            break;
		}
        case KEY_DOWN:
		{
			direction+=2;
			if(TestMode >= 1)
			{
				printf(" DOWN ");
			}
            break;
		}
        case KEY_LEFT:
		{
			direction += 1;
			if(TestMode >= 1)
			{
				printf(" LEFT ");
			}
            break;
		}
        case KEY_RIGHT:
		{
			
			direction -= 1;
			if(TestMode >= 1)
			{
				printf(" RIGHT ");
			}
            break;
		}
        default:
		{
			printf("ERROR \n");
            
            break;
		}
	}
	if(direction < 0)
	{
		direction = 4+direction;
	}
	if(direction > 3)
	{
		direction = direction-4;
	}
	switch(direction)
	{
		case 0:
		{
			animalPos[0]--;
			break;
		}
		case 1:
		{
			animalPos[1]--;
			break;
		}
		case 2:
		{
			animalPos[0]++;
			break;
		}
		case 3:
		{
			animalPos[1]++;
			break;
		}
		default:
		{
			
		}
	}
}
void getMapData()
{
	c = 0;
	
	switch(direction)
	{
		case 0:
		{
			for(a = 0; a<animalViewMapSize; a++)
			{
				for(b = 0; b<animalViewMapSize; b++)
				{
					if(animalViewMap[a][b] == 1)
					{
						animalMapView[c] = map[animalPos[0]-3 + a][animalPos[1]- 3 + b];
						c++;
					}
				}
			}
			break;
		}
		case 1:
		{
			for(a = 0; a<animalViewMapSize; a++)
			{
				for(b = 0; b<animalViewMapSize; b++)
				{
					if(animalViewMap[a][b] == 1)
					{
						animalMapView[c] = map[animalPos[0]-3 + 6-b][animalPos[1]- 3 + a];
						c++;
					}
				}
			}
			break;
		}
		case 2:
		{
			for(a = 0; a<animalViewMapSize; a++)
			{
				for(b = 0; b<animalViewMapSize; b++)
				{
					if(animalViewMap[a][b] == 1)
					{
						animalMapView[c] = map[animalPos[0]-3 + 6-a][animalPos[1]- 3 + 6-b];
						c++;
					}
				}
			}
			break;
		}
		case 3:
		{
			for(a = 0; a<animalViewMapSize; a++)
			{
				for(b = 0; b<animalViewMapSize; b++)
				{
					if(animalViewMap[a][b] == 1)
					{
						animalMapView[c] = map[animalPos[0]-3 + b][animalPos[1]- 3 + 6-a];
						c++;
					}
				}
			}
			break;
		}
	}
	
	
	
	/*
	switch(direction)
	{
		case 0:
		{
			animalMapView[0] = map[animalPos[0]+1]	[animalPos[1]-1];
			animalMapView[1] = map[animalPos[0]]	[animalPos[1]-1];
			animalMapView[2] = map[animalPos[0]-1]	[animalPos[1]-1];
			animalMapView[3] = map[animalPos[0]-1]	[animalPos[1]];
			animalMapView[4] = map[animalPos[0]-1]	[animalPos[1]+1];
			animalMapView[5] = map[animalPos[0]]	[animalPos[1]+1];
			animalMapView[6] = map[animalPos[0]+1]	[animalPos[1]+1];
			animalMapView[7] = map[animalPos[0]+1]	[animalPos[1]];	
			animalMapView[8] = map[animalPos[0]-2]	[animalPos[1]];	
			animalMapView[9] = map[animalPos[0]-3]	[animalPos[1]];	
			break;
		}
		case 1:
		{
			animalMapView[2] = map[animalPos[0]+1]	[animalPos[1]-1];
			animalMapView[3] = map[animalPos[0]]	[animalPos[1]-1];
			animalMapView[4] = map[animalPos[0]-1]	[animalPos[1]-1];
			animalMapView[5] = map[animalPos[0]-1]	[animalPos[1]];
			animalMapView[6] = map[animalPos[0]-1]	[animalPos[1]+1];
			animalMapView[7] = map[animalPos[0]]	[animalPos[1]+1];
			animalMapView[0] = map[animalPos[0]+1]	[animalPos[1]+1];
			animalMapView[1] = map[animalPos[0]+1]	[animalPos[1]];			
			animalMapView[8] = map[animalPos[0]]	[animalPos[1]-2];	
			animalMapView[9] = map[animalPos[0]]	[animalPos[1]-3];	
			
			break;
		}
		case 2:
		{
			animalMapView[4] = map[animalPos[0]+1]	[animalPos[1]-1];
			animalMapView[5] = map[animalPos[0]]	[animalPos[1]-1];
			animalMapView[6] = map[animalPos[0]-1]	[animalPos[1]-1];
			animalMapView[7] = map[animalPos[0]-1]	[animalPos[1]];
			animalMapView[0] = map[animalPos[0]-1]	[animalPos[1]+1];
			animalMapView[1] = map[animalPos[0]]	[animalPos[1]+1];
			animalMapView[2] = map[animalPos[0]+1]	[animalPos[1]+1];
			animalMapView[3] = map[animalPos[0]+1]	[animalPos[1]];		
			animalMapView[8] = map[animalPos[0]+2]	[animalPos[1]];	
			animalMapView[9] = map[animalPos[0]+3]	[animalPos[1]];	
			break;
		}
		case 3:
		{
			animalMapView[6] = map[animalPos[0]+1]	[animalPos[1]-1];
			animalMapView[7] = map[animalPos[0]]	[animalPos[1]-1];
			animalMapView[0] = map[animalPos[0]-1]	[animalPos[1]-1];
			animalMapView[1] = map[animalPos[0]-1]	[animalPos[1]];
			animalMapView[2] = map[animalPos[0]-1]	[animalPos[1]+1];
			animalMapView[3] = map[animalPos[0]]	[animalPos[1]+1];
			animalMapView[4] = map[animalPos[0]+1]	[animalPos[1]+1];
			animalMapView[5] = map[animalPos[0]+1]	[animalPos[1]];	
			animalMapView[8] = map[animalPos[0]]	[animalPos[1]+2];	
			animalMapView[9] = map[animalPos[0]]	[animalPos[1]+3];	
			break;
		}
	}
	*/
	
	for(a = 0; a < inputs; a++)
	{
		animalMapViewI[a] = animalMapView[a];
		
		if(animalMapView[a] == 2)
		{
			animalMapView[a] = -1;
		}
	}
}
void checkForCollision()
{

	if(map[animalPos[0]][animalPos[1]] == 1)
	{
		death = 1;
	}
	else
	{
		if(map[animalPos[0]][animalPos[1]] == 2)
		{
			food+=feedAmount;
			newFoodLocation();
		}
	}
	
	if(!death)
	{
		if(lastAnimalPos[0][0] == animalPos[0] && animalPos[1] == lastAnimalPos[0][1])
		{
			countIllegalMoves++;
			if(countIllegalMoves > maxIllegalMoves)
			{
				death = 1;
			}
			if(countIllegalMoves > 1)
			{
				steps--;
				if(steps<0)
				{
					steps = 0;
				}
			}
			else
			{
				steps++;
			}
		}
		else
		{
			steps++;
			countIllegalMoves = 0;
			
		}	
	}
}
void drawMap(int offsetX,int offsetY)
{
	COORD coord;
	coord.X = offsetX;//X-->
	coord.Y = offsetY;//Yv
	if(T3.start(guiUpdate))
	{
		coord.Y = offsetY-3;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);//YELLOW
		SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
		printf("starved   ");
		coord.Y = offsetY-2;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);//RED
		SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
		printf("collided   ");
	}
	coord.Y = offsetY;
	for(a = 0; a<mapSize; a++)
	{
		coord.X = offsetX;
		for(b = 0; b<mapSize; b++)
		{
			SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
			if(lastMap[a][b] != map[a][b])
			{
				SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
				switch(map[a][b])
				{
					case 0:
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//WHITE
						printf(" ");
						break;
					}
					case 1:
					{
						
						printf("H");
						break;
					}
					case 2:
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);//Light GREEN
						printf("O");
						break;
					}
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//WHITE	
			}				
			
			coord.X++;
		}
		coord.Y++;
	}
	
	coord.X = offsetX + lastAnimalPos[1][1];
	coord.Y = offsetY + lastAnimalPos[1][0];
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE ),coord);
	printf(" ");
	coord.X = offsetX + animalPos[1];
	coord.Y = offsetY + animalPos[0];
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE ),coord);
	if(death)
	{
		if(starved)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);//YELLOW
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);//RED
		}
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);//GREEN
	}
	printf("X");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//WHITE
	
	coord.X = offsetX + mapSize + 5;
	coord.Y = offsetY + 5;
	
	c = 0;
	
	for(a = 0; a<animalViewMapSize; a++)
	{
		for(b = 0; b<animalViewMapSize; b++)
		{
			if(animalViewMap[a][b] == 1)
			{
				SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
				printf("%i",animalMapViewI[c]);
				c++;
			}
			coord.X++;
		}
		coord.Y++;
		coord.X-=animalViewMapSize;
	}
	
	/*
	
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("%i",animalMapViewI[0]);
	coord.Y--;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("%i",animalMapViewI[1]);
	coord.Y--;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("%i",animalMapViewI[2]);
	coord.X++;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("%i",animalMapViewI[3]);
	coord.X++;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("%i",animalMapViewI[4]);
	coord.Y++;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("%i",animalMapViewI[5]);
	coord.Y++;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("%i",animalMapViewI[6]);
	coord.X--;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("%i",animalMapViewI[7]);

	coord.Y-=3;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("%i",animalMapViewI[8]);
	coord.Y--;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("%i",animalMapViewI[9]);
	*/

	
}
void drawNet(int offsetX,int offsetY)
{
	COORD coord;
	coord.X = offsetX;//X-->
	coord.Y = offsetY;//Yv
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("Inputs:");
	coord.X = offsetX + 10; 	
	c = 0; 
	for(b = 0; b < inputs/10; b++)
	{
		for(a = 0; a < 10; a++)
		{
			SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
			printf("%.1f  ",animalMapView[c]);
			c++;
			coord.X+=8;
		}
		coord.X = offsetX + 10; 
		coord.Y ++;
	}
	for(a = 0; a < inputs%10; a++)
	{
		SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
		printf("%.1f  ",animalMapView[c]);
		c++;
		coord.X+=8;
	}
	coord.X = offsetX;
	coord.Y += 2;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("Outputs:");
	coord.X = offsetX + 10; 
	for(a = 0; a < outputs; a++)
	{
		SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
		printf("%.1f  ",controls[a]);
		coord.X+=8;
	}
	coord.X = offsetX;
	coord.Y += 2;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);


	printf("Score:");
	coord.X = offsetX+10;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("%i  ",steps);
	
	coord.X = offsetX;
	coord.Y += 2;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	if(death == 0)
	{
		printf("Food:");
	}
	else
	{
		printf("Food_Left:");
	}
	coord.X = offsetX+10;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
	printf("%i  ",food);
    if(death == 1)
	{
		coord.Y += 1;
		coord.X = offsetX;

		//coord.X = offsetX+10;
		SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
		printf("Ges_Score: Score + Food_Left = %i",steps+food);
	}
}
void setRandomStartPos()
{
		animalPos[0] = (rand() % (mapSize-6))+3;
		animalPos[1] = (rand() % (mapSize-6))+3;
	while(map[animalPos[0]][animalPos[1]] == 1 || map[animalPos[0]][animalPos[1]] == 2)
	{
		animalPos[0] = (rand() % (mapSize-6))+3;
		animalPos[1] = (rand() % (mapSize-6))+3;
	}
	lastAnimalPos[1][0] = animalPos[0];
	lastAnimalPos[1][1] = animalPos[1];
	lastAnimalPos[0][0] = lastAnimalPos[1][0];
	lastAnimalPos[0][1] = lastAnimalPos[1][1];
	
}
void newFoodLocation()
{
	int x = animalPos[0];
	int y = animalPos[1];
	
	
	
	while(map[x][y] == 2 || map[x][y] == 1)
	{
		x = (rand()%(mapSize-6))+3;
		y = (rand()%(mapSize-6))+3;
	}
	map[x][y] = 2;
	map[animalPos[0]][animalPos[1]] = 0;
}
void randomizeFoodLocation()
{
	int x = 0;
	int y = 0;
	int count = 0;
	
	for(a = 3; a<mapSize-3; a++)
	{
		for(b = 3; b<mapSize-3; b++)
		{
			map[a][b] = 0;
		}
	}
	for(a = 0; a<mapSize; a++)
	{
		for(b = 0; b<3; b++)
		{
			map[a][mapSize-b-1] = 1;
			map[mapSize-a-1][b] = 1;
			map[mapSize-b-1][a] = 1;
			map[b][mapSize-a-1] = 1;
		}
	}
	while(count < foodAmount)
	{
		x = (rand()%(mapSize-6))+3;
		y = (rand()%(mapSize-6))+3;
		if(map[x][y] == 0)
		{
			map[x][y] = 2;
			count++;
		}
	}
	count = 0;
	while(count < obsticleAmount-1)
	{
		x = (rand()%(mapSize-6))+3;
		y = (rand()%(mapSize-6))+3;
		if(map[x][y] == 0)
		{
			map[x][y] = 1;
			count++;
		}
	}
	
}
void writeConfig()
{
	FILE *config;
	
	config = fopen("config.txt","w");
	if (config!=NULL)
	{
		
		fprintf(config,"START\n");
		fprintf(config,"animal_inputUnits %i\n"					,inputs);
		fprintf(config,"animal_hiddenUnitsX %i\n"				,hiddenX);
		fprintf(config,"animal_hiddenUnitsY %i\n"				,hiddenY);
		fprintf(config,"animal_outputUnits %i\n"				,outputs);
		fprintf(config,"animal_mutationRate %.4f\n"				,mutation);
		fprintf(config,"animal_food %i\n"						,food_Config);
		fprintf(config,"animals %i\n"							,animals);
		fprintf(config,"stopTimeLearn %i\n"						,stopTimeLearn);
		fprintf(config,"stopTimeTest %i\n"						,stopTimeTest);
		fprintf(config,"debug_pauseIntervallFile %i\n"			,pauseIntervallFile);
		fprintf(config,"debug_guiUpdate %i\n"					,guiUpdate);
		fprintf(config,"debug_averageSize %i\n"					,averageSize);
		fprintf(config,"debug_saveBiggestIntervall %i\n"		,saveBiggestIntervall);
		fprintf(config,"environment_maxIllegalMoves %i\n"		,maxIllegalMoves);
		fprintf(config,"environment_mapSize %i\n"				,mapSize);
		fprintf(config,"environment_foodAmount %i\n"			,foodAmount);
		fprintf(config,"environment_feedAmount %i\n"					,feedAmount);
		fprintf(config,"environment_obsticleAmount %i\n"		,obsticleAmount);
		fprintf(config,"startDirection %i\n"					,direction_Config);
		fprintf(config,"TestMode %i\n"							,TestMode);
		fprintf(config,"TestModeSpeed %i\n"						,TestModeSpeed);
		fprintf(config,"loopsPerAnimal %i\n"					,loopsPerAnimalConfig);
		fprintf(config,"ENDE");
	}
	fclose(config);
}
void readConfg()
{
	FILE *config;
	config = fopen("config.txt","r");
	if (config==NULL)
	{
		printf("\nConfig exestiert nicht. Sie wird erstellt.\n");
	}
	else
	{
		rewind (config);
		char Input[30];
		while(1)
		{
			fscanf(config,"%s",Input);
			if(strcmp(Input,"START\n")==0){
				printf("------START------\n");
			}
			if(strcmp(Input,"animal_inputUnits") == 0){
				fscanf(config,"%i",&inputs);
				if(inputs < 1){inputs = 1;}
				printf("animal_inputUnit: %i\n",inputs);
			}
			if(strcmp(Input,"animal_hiddenUnitsX") == 0){
				fscanf(config,"%i",&hiddenX);
				if(hiddenX < 1){hiddenX = 1;}
				printf("animal_hiddenUnitsX: %i\n",hiddenX);
			}
			if(strcmp(Input,"animal_hiddenUnitsY") == 0){
				fscanf(config,"%i",&hiddenY);
				if(hiddenY < 1){hiddenY = 1;}
				printf("animal_hiddenUnitsY: %i\n",hiddenY);
			}
			if(strcmp(Input,"animal_outputUnits") == 0){
				fscanf(config,"%i",&outputs);
				if(outputs < 1){outputs = 1;}
				printf("animal_outputUnits: %i\n",outputs);
			}
			if(strcmp(Input,"animal_mutationRate") == 0){
				fscanf(config,"%f",&mutation);
				if(mutation > 1){mutation = 1;}
				if(mutation < 0){mutation = 0;}
				printf("animal_mutationRate: %.4f\n",mutation);
			}
			if(strcmp(Input,"animal_food")==0){
				fscanf(config,"%i",&food_Config);
				if(food_Config < 1){food_Config = 1;}
				printf("animal_food: %i\n",food_Config);
			}
			if(strcmp(Input,"animals")==0){
				fscanf(config,"%i",&animals);
				if(animals < 1){animals = 1;}
				printf("animals: %i\n",animals);
			}
			if(strcmp(Input,"stopTimeLearn")==0){
				fscanf(config,"%i",&stopTimeLearn);
				if(stopTimeLearn < 1){stopTimeLearn = 1;}
				printf("stopTimeLearn: %i\n",stopTimeLearn);
			}
			if(strcmp(Input,"stopTimeTest")==0){
				fscanf(config,"%i",&stopTimeTest);
				if(stopTimeTest < 1){stopTimeTest = 1;}
				printf("stopTimeTest: %i\n",stopTimeTest);
			}
			if(strcmp(Input,"debug_pauseIntervallFile")==0){
				fscanf(config,"%i",&pauseIntervallFile);
				if(pauseIntervallFile < 1){pauseIntervallFile = 1;}
				printf("debug_pauseIntervallFile: %i\n",pauseIntervallFile);
			}
			if(strcmp(Input,"debug_guiUpdate")==0){
				fscanf(config,"%i",&guiUpdate);
				if(guiUpdate < 1){guiUpdate = 1;}
				printf("debug_guiUpdate: %i\n",guiUpdate);
			}
			if(strcmp(Input,"debug_averageSize")==0){
				fscanf(config,"%i",&averageSize);
				if(averageSize < 1){averageSize = 1;}
				printf("debug_averageSize: %i\n",averageSize);
			}
			if(strcmp(Input,"debug_saveBiggestIntervall")==0){
				fscanf(config,"%i",&saveBiggestIntervall);
				if(saveBiggestIntervall < 1){saveBiggestIntervall = 1;}
				printf("debug_saveBiggestIntervall: %i\n",saveBiggestIntervall);
			}
			if(strcmp(Input,"environment_maxIllegalMoves")==0){
				fscanf(config,"%i",&maxIllegalMoves);
				if(maxIllegalMoves < 0){maxIllegalMoves = 0;}
				printf("environment_maxIllegalMoves: %i\n",maxIllegalMoves);
			}
			if(strcmp(Input,"environment_mapSize")==0){
				fscanf(config,"%i",&mapSize);
				if(mapSize < 11){mapSize = 11;}
				if(mapSize > 100){mapSize = 100;}
				printf("environment_mapSize: %i\n",mapSize);
			}
			if(strcmp(Input,"environment_foodAmount")==0){
				fscanf(config,"%i",&foodAmount);
				if(foodAmount < 1){foodAmount = 1;}
				printf("environment_foodAmount: %i\n",foodAmount);
			}
			if(strcmp(Input,"environment_obsticleAmount")==0){
				fscanf(config,"%i",&obsticleAmount);
				if(obsticleAmount < 0){obsticleAmount = 0;}
				if(obsticleAmount > (mapSize-6)*(mapSize-6)-10)
				{obsticleAmount = (mapSize-6)*(mapSize-6)-10;}
				printf("environment_obsticleAmount: %i\n",obsticleAmount);
			}
			if(strcmp(Input,"environment_feedAmount")==0){
				fscanf(config,"%i",&feedAmount);
				if(feedAmount < 0){feedAmount = 0;}
				if(feedAmount > 1000)
				{feedAmount = 1000;}
				printf("environment_feedAmount: %i\n",feedAmount);
			}
			if(strcmp(Input,"startDirection")==0){
				fscanf(config,"%i",&direction_Config);
				if(direction_Config < 0){direction_Config = 0;}
				if(direction_Config > 3){direction_Config = 3;}
				printf("startDirection: %i\n",direction_Config);
			}
			if(strcmp(Input,"TestMode")==0){
				fscanf(config,"%i",&TestMode);
				if(TestMode < 0){TestMode = 0;}
				if(TestMode > 2){TestMode = 2;}
				printf("TestMode: %i\n",TestMode);
			}
			if(strcmp(Input,"TestModeSpeed")==0){
				fscanf(config,"%i",&TestModeSpeed);
				if(TestModeSpeed < 1){TestModeSpeed = 1;}
				printf("TestModeSpeed: %i\n",TestModeSpeed);
			}
			if(strcmp(Input,"loopsPerAnimal")==0){
				fscanf(config,"%i",&loopsPerAnimalConfig);
				if(loopsPerAnimalConfig < 1){loopsPerAnimalConfig = 1;}
				if(loopsPerAnimalConfig > 5000){loopsPerAnimalConfig = 5000;}
				printf("loopsPerAnimal: %i\n",loopsPerAnimalConfig);
			}
			
			if(strcmp(Input,"ENDE")==0){
				printf("------ENDE------\n");
				break;
			}
			
		}
	}
	fclose(config);
}
void saveBest()
{
	float 	rank[animals]; //
	int 	sort[animals]; //rank[0] = 3 ---> animal 3 ist auf Platz 1
	float 	tmp;		   //tmporäre Variable für Zwischenspeicher
	unsigned int cou = 0;
	
	//---------------SELECTION--------------
	for(a = 0; a < animals; a++)
	{
		rank[a] = fitness[a];	//Alle fitness Werte zwischenspeichern
		sort[a] = a;				//Init alle ranks: 0,1,2,3,4...
	}
	while(cou != animals-1)			//Erst aus dem while() wenn alle Werte sortiert sind
	{
		cou = 0;
		for(a = 0; a < animals-1; a++)
		{
			//Sortieren
			if(rank[a]>rank[a+1])
			{
				tmp 		= rank[a];		//vertauschen der fitness scores 
				rank[a]		= rank[a+1];	//um sie zu sortieren: 2,1 --> 1,2
				rank[a+1]	= tmp;			//
			
				tmp 		= sort[a];		//vertauschen der ranks  
				sort[a]		= sort[a+1];	//um sie zu sortieren: 0,1 --> 1,0
				sort[a+1]	= tmp;			//
			} 
			else
			{
				cou++;
			}
			//---------
		}
	}
	if(lastBestFitness < rank[animals-1])
	{
		lastBestFitness = rank[animals-1];
		
				
		
		bestGen = calcNet->getGen(sort[animals-1]);
		updateBestGen = 1;
	}
	if((generation - lastSaveBiggest) >= saveBiggestIntervall && updateBestGen == 1)
	{
		updateBestGen = 0;
		lastSaveBiggest = generation;
		file = fopen("best.txt","w");
		
		fprintf(file,"%.8f\n",fitness[sort[animals-1]]);
		for(a = 0; a < geneticSize; a++)
		{
			fprintf(file,"%.8f ",bestGen[a]);
		}
		fprintf(file,"\n");
		fclose(file);
	}
}
void setupMapView()
{
	char buffIn = 0;
	int error = 0; 
	d = 0;
	c = 0;
	file = fopen("animal.txt","r");
	if(file != NULL)
	{
		for(a = 0; a<animalViewMapSize; a++)
		{
			for(b = 0; b<animalViewMapSize; b++)
			{
				fscanf(file,"%c",&buffIn);
				if(buffIn == '\n')
				{
					fscanf(file,"%c",&buffIn);
				}
				switch(buffIn)
				{
					case '0':
					{
						animalViewMap[a][b] = 0;
						break;
					}
					case '1':
					{
						animalViewMap[a][b] = 1;
						c++;
						break;
					}
					case 'X':
					{
						if(a == 3 && b == 3)
						{
							d++;
							animalViewMap[a][b] = 8;
						}
						else
						{
							printf("ERROR:  Falsche animal.txt Konfiguration\n\tArraysize = 7\n");
							printf("\t'X' muss in der Mitte sein\n\t'X'ist bei x: %i y: %i",b,a);
							while(1)
							{}
						}
						break;
					}
					default:
					{
						printf("ERROR:  Falsche animal.txt Konfiguration\n\tNur die Zeichen: \n\t0 fuer kein Auge\n\t1 fuer Auge\n\tX fuer Lebewesen\n\tDas Lebewesen muss in der Mitte sein!");
						while(1)
						{}
					}
				}
			}
		}
		if(d != 1)
		{
			printf("ERROR:  Falsche animal.txt Konfiguration\n");
			printf("\tDas 'X' muss und darf nur 1 mal in der Mitte gesetzt werden");
			while(1)
			{}
		}
		if(c != inputs)
		{
			printf("ERROR:  Falsche animal.txt Konfiguration\n\tAugen: %i NetInputs: %i\n",c,inputs);
			printf("\tDie Anzahl muss die selbe sein");
			while(1)
			{}
		}
		fclose(file);
	}
	else
	{
		if(inputs != 10)
		{
			error = 1;
		}
	}
	
	file = fopen("animal.txt","w");
	for(a = 0; a<animalViewMapSize; a++)
	{
		for(b = 0; b<animalViewMapSize; b++)
		{
			if(a == 3 && b == 3)
			{
				fprintf(file,"X");
			}
			else
			{
				fprintf(file,"%i",animalViewMap[a][b]);
			}
		}
		fprintf(file,"\n");
	}
	fclose(file);
	if(error == 1)
	{
		printf("ERROR:  False Anzahl Inputs, Inputs: %i\n\tEs muessen '10' Inputs sein bei dieser animal.txt konfiguration",inputs);
		while(1)
		{}
	}
}
void saveFile()
{
//--------------FILE---------------
	calcNet->saveData(xxa);
	
	file = fopen("learn.csv","a");
	fprintf(file,"%.8f;%.8f;\n",gesFitness,durchschnitt[0]);
	fclose(file);	
	file = fopen("gen.txt","w");
	fprintf(file,"%i\n",generation);
	for(a = 0; a<averageSize; a++)
	{
		fprintf(file,"%.8f ",durchschnitt[a]);
	}
	fclose(file);
	
//---------------------------------
}
void handleKeyBoeard(int whileForKey)
{
	char key = 0;
	if (kbhit() || whileForKey == 1)
	{
		key = getch();
	}
	switch(key)
	{
		case 'q':
		{
			saveFile();
			exitProg = 1;
			break;
		}
		case 'd':
		{
			TestMode++;
			if(TestMode == 2)
			{
				TestMode = 0;
				T3.stop();
				loopsPerAnimal = loopsPerAnimalConfig;
				
			}
			else
			{
				loopsPerAnimal = 1;
				testModeAnimal = 0;
			}
			draw();
			break;
		}
		case 's':	//Speed/skip
		{
			if(skip)
			{
				skip = 0;
			}
			else
			{
				skip = 1;
			}
		}
		default:
		{
			
			break;
		}
	}
}



