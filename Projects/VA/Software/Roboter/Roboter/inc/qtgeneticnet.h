#ifndef QTGENETICNET_H
#define QTGENETICNET_H


#include <geneticNet.h>
#include "objects/circle.h"
#include "objects/line.h"
#include <config.h>
#include <QtCore>
#include <QtGui>
#include "worker.h"

const std::string QtGeneticNetVersion = "0.0.0";

class QtGeneticNet
{
    public:
    QtGeneticNet(unsigned int inputs,   unsigned int hiddenX,
                 unsigned int hiddenY,  unsigned int outputs,
                 unsigned int animals,  float mutationFactor,
                 bool enableBias,       bool enableAverage,
                 std::string confName,std::string netDataFileName);
    ~QtGeneticNet();

    Config       *config;
  /*  std::string configParameter(std::string paramName);
    void configParameter(std::string paramName,std::string value);*/

    unsigned int inputs();
    unsigned int hiddenX();
    unsigned int hiddenY();
    unsigned int outputs();
    unsigned int genomSize();

    void animal(unsigned int animalNr);
    unsigned int animal();
    unsigned int animals();
    void input(std::vector<float> signal);
    void run();
    std::vector<float> output();
    float output(int pos);
    void learn(std::vector<float> score);

    void draw(QPainter *painter,QPoint drawPos,float colorMultiplayer,unsigned int animal);
    void drawSetup(unsigned int neuronRadius,   unsigned int abstandX,
                   unsigned int abstandY,       unsigned int connectionSize);
    void saveBest(std::string fileName);
    std::vector<float>                genom(unsigned int animal);
    std::vector<std::vector<float>  > genom();
    void netInfoToConfig();

    void load();
    void load(std::string fileName);
    void save();
    void save(std::string fileName);

    std::vector<float>  gohstNetOutput(unsigned int animal);
    float               gohstNetOutput(unsigned int animal,unsigned int output);
    void                gohstNetInput(unsigned int animal,std::vector<float> signal);
    void                gohstNetInput(unsigned int animal,unsigned int input,float signal);
    std::vector<float>  gohstNetInput(unsigned int animal);
    float               gohstNetInput(unsigned int animal,unsigned int input);

    void mutationFactor(float fac);
    float mutationFactor();
    void mutationDivisor(float divisor);
    float mutationDivisor();

private:
    int MAP(int input,int von1,int bis1,int von2,int bis2);
    int configToNetInfo();
    QColor weightColor(float signal,float weight,float colorMultiplayer);
    void runThreadNet(unsigned int animal);
    unsigned int _inputs;
    unsigned int _hiddenX;
    unsigned int _hiddenY;
    unsigned int _outputs;
    bool _enableBias;
    bool _enableAverage;
    unsigned int _animals;
    float _mutationFactor;
    float _mutationDivisor;
    std::vector<float> _score;



    geneticNet   *net;

    std::vector<Net> gohstNet;//nur die hülle für die berechnungen

    //-----draw
    unsigned int _draw_neuronRadius;
    unsigned int _draw_abstandX;
    unsigned int _draw_abstandY;
    unsigned int _draw_connectionSize;
    //---------

    unsigned int avtiveAnimal;
    bool lockForWrongData;
    std::string netDataFileName;

    bool wrongNetConfiguration;

    std::vector<Worker*> worker;
};

#endif // QTGENETICNET_H
