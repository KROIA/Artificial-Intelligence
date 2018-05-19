****Mit Notepad++ öffnen****


Künstliche Intelligenz
//--------------
Autor Alex Krieg
Datum 6.6.2017
//--------------

//-----------------------------------SETUP--------------------------------
Downloaden und loslegen
	In "Vortrainierte Examples" gibt es Beispiele die man 
	direkt laufen lassen kann.
	Einfach Doppelklick auf die .exe und beobachten.
	Die gesamten Lernergebnisse sind auch in diesem Ordner.

//------------------------------------------------------------------------

//-----------------------------------CONFIGURATION------------------------
Datei: config.txt {
	START						
	animal_inputUnits 10				//v
	animal_hiddenUnitsX 8				//Neuronen siehe Bild
	animal_hiddenUnitsY 1				//^
	animal_outputUnits 4				//^
	animal_mutationRate 0.1000			//Wie gross die Wahrscheinlichkeit ist dass ein Gewicht in jedem gen random ändert (1 = ändert immer, 0 = ändert nie)
	animal_food 10					//Anzahl Essen das beim Start zur verfügung steht
	animals 100					//Mit wie vielen Lebewesen gelernt wird
	stopTimeLearn 500				//Zeit in ms wie lange ein Lebewesen zeit hat, wenn es nie stirbt bis es stirbt
	stopTimeTest 50000				//Das selbe, aber nur wärend der Testphase
	debug_pauseIntervallFile 50			//Das selbe, aber für die Speicherung der Daten
	debug_guiUpdate 1000				//Update der Konsole, ist nur in der Trainingsphase so
	debug_averageSize 100				//Auf wie viele Generationen der Durchschnitt zählt (Hoch -> sanfte Kurve Tief -> turbulente Kurve)
	debug_saveBiggestIntervall 10			//Wie oft der beste gespeichert wird
	environment_maxIllegalMoves 3			//Anzahl wie oft ein Lebewesen hin und her hüpfen darf bevor es dadurch stirbt
	environment_mapSize 20				//Grösse der Map x*x
	environment_foodAmount 10			//Anzahl Futter das auf der Map gefunden werden kann
	environment_feedAmount 10			//Anzahl Essen das dem Lebewesen gegeben wird wenn es ein Futter frisst
	environment_obsticleAmount 10			//Anzahl Hindernisse auf der Map
	startDirection 0				//Startrichtung die das Lebewesen hat, 0-3
	TestMode 0					//0 -> Trainings Phase 1 -> Testphase
	TestModeSpeed 100				//Wie schnell int ms die Simulation in der Testphase ist 
	ENDE
}
//------------------------------------------------------------------------
