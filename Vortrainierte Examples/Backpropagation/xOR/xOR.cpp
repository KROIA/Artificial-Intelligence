//Autor Alex Krieg
//V1.0
//18.5.2017



#include <stdio.h>
#include <stdlib.h>
#include "E:\Users\Alex\Documents\C++\libraries\Net\Versionen\2.0\Net.h"
#include "E:\Users\Alex\Documents\C++\libraries\Net\Versionen\2.0\Net.cpp"



//****NETWORK********************************
const unsigned int inputUnits 		= 2;
const unsigned int hiddenX 			= 2;
const unsigned int hiddenY			= 2;
const unsigned int outputUnits		= 1;
const  float 	   learingFactor 	= 0.1;
//*******************************************

float error							= 1.0;
//****LEARN**********************************
const unsigned int Sets				= 8;
const unsigned int testSets			= 8;
//*******************************************


//****LEARN*DATA*****************************
float DATA[Sets][inputUnits]={	//XOR Input
{0,0},
{0,1},
{1,0},
{1,1}
};
float DATASoll[Sets][outputUnits]={	//XOR Output
{0},
{1},
{1},
{0}
};

//****TEST*DATA******************************
float DATA_TEST[testSets][inputUnits]={
{0,0},
{0,1},
{1,0},
{1,1}
};
float DATA_Test_Soll[testSets][outputUnits]={
{0},
{1},
{1},
{0}
};
//*******************************************


Net net(inputUnits,hiddenX,hiddenY,outputUnits,learingFactor);

float Data[Sets][outputUnits];	//Netzwerk Ausgang
const unsigned int debugIntervall	= 3000;
char xxa[10] = {'a','.','t','x','t'};	//Netzwerk Konfiguration
int countsteps		 = 0;
const int MAX_LENGTH = 1;

//für die for() loops
int a = 0; 
int b = 0;
int i = 0;

void end()
{
	COORD cord;
	net.saveData(xxa);	//Speichert die Gewichtungen 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cord.X = 0;	cord.Y = 15+(5*hiddenY); //Start pos
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	printf("\n\nFinish steps:\t%d\n",net.steps);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	while(1)
	{
		//----------------------------------------------Ein Durchlauf mit allen Inputs und den gegebenen Outputs
		for( i= 0; i<testSets; i++)
		{
			net.setInputUnits(DATA_TEST[i]);	//Setzt die Inputs von Trainings-durchgang i
			net.learn(DATA_Test_Soll[i],0);		//Gibt die lösung zu den inputs i
												//Das Netzwerk verbessert sich nicht weil der letzte Par. = 0 ist
			for( a= 0; a<outputUnits; a++)
			{
				Data[i][a] = net.getOutput(a);	//Speichert die Outputs i um sie auch auserhalb der Klasse verwenden zu können
			}
			
			net.debug();						//Giebt jegliche Informationen über das Netzwerk in der Konsole aus
			Sleep(1000);
		}
		//-------------------------------------------------------------------------------------------------------
	}
}
int main()
{
	FILE *Myfile;
	net.loadData(xxa);
	while(1)
	{
		if(error < 0.0001)
		{
			end();
		}
		error = 0.0;
		for( i= 0; i<Sets; i++)
		{
			 net.setInputUnits(DATA[i]);		//Setzt die Inputs von Trainings-durchgang i
			 net.learn(DATASoll[i]);            //Gibt die lösung zu den inputs i und
			                                    //das Netzwerk verbessert seine Gewichtungen
			 for( a= 0; a<outputUnits; a++)     
			 {                                  
				Data[i][a] = net.getOutput(a);  //Speichert die Outputs i um sie auch auserhalb der Klasse verwenden zu können
			 }                                  
			 error = error + net.netError;    	  
		}                                      
		error = error / Sets;					//Rechnet den Gesamten Error aus
		if(countsteps == debugIntervall)		//Giebt wärend der Lernphase nur alle "debugIntervall" etwas an die Konsole und ins Log
		{
			net.saveData(xxa);					//Speichert die Gewichtungen 
			net.debug();						//Giebt jegliche Informationen über das Netzwerk in der Konsole aus
			
			Myfile = fopen ("Error.csv","a");	//Error Verlauf
			fprintf(Myfile,"%.8f\n",error);		//Im  excel die ganze Spalte markieren und eine Tabelle
			fclose(Myfile);						//einfügen.
												//Je tiefer der Error desto besser
			countsteps = 0;
		}
		else
		{
		   countsteps++;
		}
		
	}
	return 0;
}