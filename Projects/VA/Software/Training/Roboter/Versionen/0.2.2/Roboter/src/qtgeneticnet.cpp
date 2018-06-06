#include "inc/qtgeneticnet.h"



QtGeneticNet::QtGeneticNet(unsigned int inputs,   unsigned int hiddenX,
                           unsigned int hiddenY,  unsigned int outputs,
                           unsigned int animals,  float mutationFactor,
                           bool enableBias,       bool enableAverage,
                           std::string confName,std::string netDataFileName,QWidget *parent)
{
    config                              = new Config(confName);
    this->parent                        = parent;
    _inputs                             = inputs;
    _hiddenX                            = hiddenX;
    _hiddenY                            = hiddenY;
    _outputs                            = outputs;
    _animals                            = animals;
    _mutationFactor                     = mutationFactor;
    _enableBias                         = enableBias;
    _enableAverage                      = enableAverage;
    lockForWrongData                    = false;
    avtiveAnimal                        = 0;
    this->netDataFileName               = netDataFileName;
    _mutationDivisor                    = 10000;
    if(!config->load())
    {
        if(configToNetInfo()!=0)
        {
            lockForWrongData = true;
            std::vector<std::string>configData = config->text();
            qDebug("|------------------------------------------------------------------------------|");
            qDebug("|------------------------------------------------------------------------------|");
            qDebug("|----  ERROR: QtGeneticNet::QtGeneticNet() DIE PARAMETER STIMMEN NICHT MIT ----|");
            qDebug("|----  ERROR:                   DEM CONFIG ÜBEREIN                         ----|");
            qDebug("|------------------------------------------------------------------------------|");
            qDebug("|------------------------------------CONFIG------------------------------------|");
            qDebug("|--                                                                          --|");
            for(int a=0; a<configData.size(); a++)
            {
                for(int b=0; b<configData.size(); b++)
                {
                    if(configData[b].find("\n") != -1)
                    {
                        configData[b] = configData[b].substr(0,configData[b].find("\n"));
                    }
                }
                std::string x = "|-- "+configData[a];
                for(int b=0; b<72-configData[a].size(); b++)
                {
                    x+= " ";
                }
                x+= " --|";
                qDebug(x.c_str());

            }
            qDebug("|--                                                                          --|");
            qDebug("|------------------------------------------------------------------------------|");
        }
    }

    netInfoToConfig();
    //config->save();


    _draw_neuronRadius                  = 5;
    _draw_abstandX                      = 20;
    _draw_abstandY                      = 50;
    _draw_connectionSize                = 2;
    _ValueLabelFontSize                 = 8;

    _score                              = std::vector<float>(_animals,0);
    net             = new geneticNet(_inputs,_hiddenX,_hiddenY,_outputs,_animals,_mutationFactor,_enableBias,_enableAverage);

    gohstNet        = std::vector<Net>(_animals,Net(_inputs,_hiddenX,_hiddenY,_outputs,_enableBias,_enableAverage));
    if(net->loadData(netDataFileName) == 1)
    {
      wrongNetConfiguration = true;
      lockForWrongData      = true;
    }
    else
    {
      wrongNetConfiguration=false;
      net->saveData(netDataFileName);
      for(int a=0; a<_animals; a++)
      {
        gohstNet[a].weightOfNet(net->genom(a));
      }
    }
    net->mutationDivisor(_mutationDivisor);

    worker = std::vector<Worker*>(_animals);

    _displayInputValue = false;
    _displayHiddenValue = false;
    _displayOutputValue = false;
    for(int a=0; a<_animals; a++)
    {
        worker[a] = new Worker();
        worker[a]->setParam(a);
        using std::placeholders::_1;
        std::function<void(int)>function = std::bind( &QtGeneticNet::runThreadNet, this, _1 );
        worker[a]->setFunction(function);
        qDebug("worker: %i param: %i",a,worker[a]->getParam());


    }
    QFont font;
    font.setPointSize(8);
    hiddenLabel.push_back(std::vector<QLabel*>());
    for(int b=0; b<_inputs; b++)
    {
        //label[a]->setGeometry(10,10,_draw_neuronRadius*2,30);


        inputLabel.push_back(new QLabel(parent));

        inputLabel[b]->setFont(font);
    }

    for(int b=0; b<_hiddenX; b++)
    {
        hiddenLabel.push_back(std::vector<QLabel*>());
        for(int c=0; c<_hiddenY; c++)
        {
            hiddenLabel[b].push_back(new QLabel(parent));
            hiddenLabel[b][c]->setFont(font);
        }
    }
    for(int b=0; b<_outputs; b++)
    {
        outputLabel.push_back(new QLabel(parent));
        outputLabel[b]->setFont(font);
    }
}
QtGeneticNet::~QtGeneticNet()
{

}
unsigned int QtGeneticNet::inputs()
{
    return _inputs;
}
unsigned int QtGeneticNet::hiddenX()
{
    return _hiddenX;
}
unsigned int QtGeneticNet::hiddenY()
{
    return _hiddenY;
}
unsigned int QtGeneticNet::outputs()
{
    return _outputs;
}
unsigned int QtGeneticNet::genomSize()
{
    return net->genomSize();
}
bool QtGeneticNet::enableBias()
{
	return _enableBias;
}
bool QtGeneticNet::enableAverage()
{
	return _enableAverage;
}
void QtGeneticNet::animal(unsigned int animalNr)
{
  if(!wrongNetConfiguration)
  {
    avtiveAnimal = animalNr;
    net->animal(avtiveAnimal);
  }
}
unsigned int QtGeneticNet::animal()
{
    return net->animal();
}
unsigned int QtGeneticNet::animals()
{
    return _animals;
}
void QtGeneticNet::input(std::vector<float> signal)
{
    if(!lockForWrongData)
    net->input(signal);
}
void QtGeneticNet::run()
{
    if(!lockForWrongData)
    {
        for(int a=0; a<_animals; a++)
        {
            worker[a]->start();
        }
        bool allTreadStopded = false;
        while(!allTreadStopded)
        {
            allTreadStopded = true;
            for(int a=0; a<_animals; a++)
            {
                if(worker[a]->isRunning() == true)
                    allTreadStopded = false;
            }
        }
    }
}
void QtGeneticNet::runThreadNet(unsigned int animal)
{
     gohstNet[animal].run();
}
std::vector<float> QtGeneticNet::output()
{
    if(!lockForWrongData)
    return net->output();
}
float QtGeneticNet::output(int pos)
{
    if(!lockForWrongData)
    return net->output(pos);
}
void QtGeneticNet::learn(std::vector<float> score)
{
    if(!lockForWrongData)
    {
        if(score.size() != _animals)
            qDebug("score.size() != animals : %i != %i QtGeneticNet::learn(std::vector<float> score)",score.size(),_animals);
        else
        {
            net->learn(score);
            for(int a=0; a<_animals; a++)
            {
              gohstNet[a].weightOfNet(net->genom(a));
            }
        }
    }
}
void QtGeneticNet::draw(QPainter *painter,QPoint drawPos,float colorMultiplayer,unsigned int animal)
{
    if(!lockForWrongData)
    {
        int gohstNet_Net = animal;
        int biasXoffset = _draw_abstandX/20;

        std::vector<Circle>                 inputNeuron         (_inputs,Circle());
        std::vector<std::vector<Circle> >   hiddenNeuron        (_hiddenX,std::vector<Circle>(_hiddenY,Circle()));
        std::vector<Circle>                 outputNeuron         (_outputs,Circle());
        std::vector<Circle>                 biasNeuron;

        if(_enableBias)
        {
            biasNeuron = std::vector<Circle>(_hiddenX+1,Circle());
        }
        std::vector<std::vector<Line>   >   inputConnection     (_inputs+_enableBias,std::vector<Line>(_hiddenY,Line()));
        std::vector<std::vector<std::vector<Line>   >   >   hiddenConnection    (_hiddenX-1,std::vector<std::vector<Line>   >(_hiddenY+_enableBias,std::vector<Line>(_hiddenY,Line())));
        std::vector<std::vector<Line>   >   outputConnection     (_hiddenY+_enableBias,std::vector<Line>(_outputs,Line()));

        float R = _draw_neuronRadius;
        float D = _draw_neuronRadius*2;

        float inputYoffset;
        float hiddenYoffset;
        float outputYoffset;

        unsigned int labelWidth = D+R;
        unsigned int labelHeight= D;

        //------------------------set offsetPos
        if(_inputs >= _hiddenY && _inputs > _outputs)
          {
            inputYoffset  = 0;
            hiddenYoffset = (_inputs - _hiddenY) *(_draw_abstandY/*+D*/)/2;
            outputYoffset = (_inputs - _outputs) *(_draw_abstandY/*+D*/)/2;
          }
        if(_hiddenY > _inputs && _hiddenY >= _outputs)
          {
            inputYoffset  = (_hiddenY - _inputs)  *(_draw_abstandY/*+D*/)/2;
            hiddenYoffset = 0;
            outputYoffset = (_hiddenY - _outputs) *(_draw_abstandY/*+D*/)/2;
          }
        if(_outputs >= _inputs && _outputs > _hiddenY)
          {
            inputYoffset  = (_outputs - _inputs)  *(_draw_abstandY/*+D*/)/2;
            hiddenYoffset = (_outputs - _hiddenY) *(_draw_abstandY/*+D*/)/2;
            outputYoffset = 0;
          }
        //-------------------------------------
        //-----------------------setPosition---
        for(int a=0; a<_inputs; a++)
        {
            inputNeuron[a].pos(QPoint(R,(a+1)*(_draw_abstandY)+inputYoffset));
            inputNeuron[a].size(R);
            inputNeuron[a].color(weightColor(gohstNet[gohstNet_Net].input(a),1,1));
            if(_displayInputValue)
            {
                inputLabel[a]->setGeometry(drawPos.x()+R-labelWidth/2,drawPos.y()+(a+1)*_draw_abstandY+inputYoffset-labelHeight/2,labelWidth+R,labelHeight);
                inputLabel[a]->setText(QString::number(gohstNet[gohstNet_Net].input(a),'f',2));
            }
        }
        for(int a=0; a<_hiddenX; a++)
        {
            for(int b=0; b<_hiddenY; b++)
            {
                hiddenNeuron[a][b].pos(QPoint((a+1)*(_draw_abstandX),(b+1)*(_draw_abstandY)+hiddenYoffset));
                hiddenNeuron[a][b].size(R);
                hiddenNeuron[a][b].color(weightColor(gohstNet[gohstNet_Net].hiddenLayer[a][b].output(),1,1));
                if(_displayHiddenValue)
                {
                    hiddenLabel[a][b]->setGeometry(drawPos.x()+(a+1)*_draw_abstandX-labelWidth/2,drawPos.y()+(b+1)*_draw_abstandY+hiddenYoffset-labelHeight/2,labelWidth+R,labelHeight);
                    hiddenLabel[a][b]->setText(QString::number(gohstNet[gohstNet_Net].hiddenLayer[a][b].output(),'f',2));
                }
            }
        }
        for(int a=0; a<_outputs; a++)
        {
            outputNeuron[a].pos(QPoint(_draw_abstandX+hiddenNeuron[hiddenNeuron.size()-1][0].pos().x(),(a+1)*(_draw_abstandY)+outputYoffset));
            outputNeuron[a].size(R);
            outputNeuron[a].color(weightColor(gohstNet[gohstNet_Net].outputLayer[a].output(),1,1));
            if(_displayOutputValue)
            {
                outputLabel[a]->setGeometry(drawPos.x()+_draw_abstandX+hiddenNeuron[hiddenNeuron.size()-1][0].pos().x()-labelWidth/2,drawPos.y()+(a+1)*_draw_abstandY+outputYoffset-labelHeight/2,labelWidth+R,labelHeight);
                outputLabel[a]->setText(QString::number(gohstNet[gohstNet_Net].outputLayer[a].output(),'f',2));
            }
        }
        if(_enableBias)
        {
            for(int a=0; a<biasNeuron.size(); a++)
            {
                if(a == 0)//Input Bias
                    biasNeuron[a].pos(QPoint(inputNeuron[inputNeuron.size()-1].pos().x()+biasXoffset,inputNeuron[inputNeuron.size()-1].pos().y()+D+_draw_abstandY));
                else//Die anderen
                    biasNeuron[a].pos(QPoint(hiddenNeuron[a-1][hiddenNeuron[0].size()-1].pos().x()+biasXoffset,hiddenNeuron[a-1][hiddenNeuron[0].size()-1].pos().y()+D+_draw_abstandY));
                biasNeuron[a].size(R);
            }
        }
        for(int a=0; a<inputConnection.size(); a++)//Alle input Seiten
        {
            for(int b=0; b<inputConnection[0].size(); b++)//Alle hiddenY seiten von hiddenX=0
            {
                if(a == _inputs)//Beim Bias ist die Position anderst
                {
                    inputConnection[a][b].startPos(QPoint(biasNeuron[0].pos().x()+R,biasNeuron[0].pos().y()));
                    if(gohstNet_Net <0)
                      inputConnection[a][b].color(weightColor(1,net->hiddenLayer[0][b].weight(a),colorMultiplayer));
                    else
                      inputConnection[a][b].color(weightColor(1,gohstNet[gohstNet_Net].hiddenLayer[0][b].weight(a),colorMultiplayer));
                }
                else
                {
                    inputConnection[a][b].startPos(QPoint(inputNeuron[a].pos().x()+R,inputNeuron[a].pos().y()));
                    inputConnection[a][b].color(weightColor(gohstNet[gohstNet_Net].input(a),gohstNet[gohstNet_Net].hiddenLayer[0][b].weight(a),colorMultiplayer));
                }
                inputConnection[a][b].endPos(QPoint(hiddenNeuron[0][b].pos().x()-R,hiddenNeuron[0][b].pos().y()));
                inputConnection[a][b].width(_draw_connectionSize);
            }
        }
        for(int a=0; a<hiddenConnection.size(); a++)//Alle hidden Layer Y
        {
            for(int b=0; b<hiddenConnection[0].size(); b++)//alle x+bias davon
            {
                for(int c=0; c<hiddenConnection[0][0].size(); c++)//alle nächsten
                {
                    if(b == _hiddenY)
                    {
                        hiddenConnection[a][b][c].startPos(QPoint(biasNeuron[a+1].pos().x()+R,biasNeuron[a+1].pos().y()));
                        hiddenConnection[a][b][c].color(weightColor(1,gohstNet[gohstNet_Net].hiddenLayer[a+1][c].weight(b),colorMultiplayer));
                    }
                    else
                    {
                        hiddenConnection[a][b][c].startPos(QPoint(hiddenNeuron[a][b].pos().x()+R,hiddenNeuron[a][b].pos().y()));
                        hiddenConnection[a][b][c].color(weightColor(gohstNet[gohstNet_Net].hiddenLayer[a][b].output(),gohstNet[gohstNet_Net].hiddenLayer[a+1][c].weight(b),colorMultiplayer));
                    }
                    hiddenConnection[a][b][c].endPos(QPoint(hiddenNeuron[a+1][c].pos().x()-R,hiddenNeuron[a+1][c].pos().y()));
                    hiddenConnection[a][b][c].width(_draw_connectionSize);
                }
            }
        }
        for(int a=0; a<outputConnection.size(); a++)
        {
            for(int b=0; b<outputConnection[0].size(); b++)
            {
                if(a == _hiddenY)
                {
                    outputConnection[a][b].startPos(QPoint(biasNeuron[biasNeuron.size()-1].pos().x()+R,biasNeuron[biasNeuron.size()-1].pos().y()));
                    outputConnection[a][b].color(weightColor(1,gohstNet[gohstNet_Net].outputLayer[b].weight(a),colorMultiplayer));
                }
                else
                {
                    outputConnection[a][b].startPos(QPoint(hiddenNeuron[hiddenNeuron.size()-1][a].pos().x()+R,hiddenNeuron[hiddenNeuron.size()-1][a].pos().y()));
                    outputConnection[a][b].color(weightColor(gohstNet[gohstNet_Net].hiddenLayer[net->hiddenLayer.size()-1][a].output(),gohstNet[gohstNet_Net].outputLayer[b].weight(a),colorMultiplayer));
                }
                outputConnection[a][b].endPos(QPoint(outputNeuron[b].pos().x()-R,outputNeuron[b].pos().y()));
                outputConnection[a][b].width(_draw_connectionSize);
            }
        }
        //-----------------------------------------------
        //-----------------------draw--------------------
        for(int a=0; a<inputConnection.size(); a++)
        {
            for(int b=0; b<inputConnection[0].size(); b++)
            {
                inputConnection[a][b].draw(painter,drawPos);
            }
        }
        for(int a=0; a<hiddenConnection.size(); a++)
        {
            for(int b=0; b<hiddenConnection[0].size(); b++)
            {
                for(int c=0; c<hiddenConnection[0][0].size(); c++)
                {
                    hiddenConnection[a][b][c].draw(painter,drawPos);
                }
            }
        }
        for(int a=0; a<outputConnection.size(); a++)
        {
            for(int b=0; b<outputConnection[0].size(); b++)
            {
                outputConnection[a][b].draw(painter,drawPos);
            }
        }

        for(int a=0; a<_inputs; a++)
        {

            inputNeuron[a].draw(painter,drawPos);

        }
        for(int a=0; a<_hiddenX; a++)
        {
            for(int b=0; b<_hiddenY; b++)
            {
                hiddenNeuron[a][b].draw(painter,drawPos);
            }
        }
        for(int a=0; a<_outputs; a++)
        {
            outputNeuron[a].draw(painter,drawPos);
        }
        if(_enableBias)
        {
            for(int a=0; a<biasNeuron.size(); a++)
            {
                biasNeuron[a].draw(painter,drawPos);
            }
        }
        //-----------------------------------------------
    }
}
void QtGeneticNet::drawSetup(unsigned int neuronRadius,   unsigned int abstandX,
                             unsigned int abstandY,       unsigned int connectionSize)
{
    _draw_neuronRadius      = neuronRadius;
    _draw_abstandX          = abstandX;
    _draw_abstandY          = abstandY;
    _draw_connectionSize    = connectionSize;
    QFont font;
    font.setPointSize(_draw_neuronRadius);
    for(int b=0; b<_inputs; b++)
    {
        inputLabel[b]->setFont(font);
    }

    for(int b=0; b<_hiddenX; b++)
    {
        for(int c=0; c<_hiddenY; c++)
        {
            hiddenLabel[b][c]->setFont(font);
        }
    }
    for(int b=0; b<_outputs; b++)
    {
        outputLabel[b]->setFont(font);
    }
}
void QtGeneticNet::drawInputValue(bool displayInputValue)
{
    _displayInputValue = displayInputValue;
    for(int a=0; a<_inputs; a++)
    {
        if(_displayInputValue)
            inputLabel[a]->show();
        else
            inputLabel[a]->hide();
    }
}
void QtGeneticNet::drawHiddenValue(bool displayHiddenValue)
{
    _displayHiddenValue = displayHiddenValue;
    for(int a=0; a<_hiddenX; a++)
    {
        for(int b=0; b<_hiddenY; b++)
        {
            if(_displayHiddenValue)
                hiddenLabel[a][b]->show();
            else
                hiddenLabel[a][b]->hide();
        }
    }
}
void QtGeneticNet::drawOutputValue(bool displayOutputValue)
{
    _displayOutputValue = displayOutputValue;
    for(int a=0; a<_outputs; a++)
    {
        if(_displayOutputValue)
            outputLabel[a]->show();
        else
            outputLabel[a]->hide();
    }
}
void QtGeneticNet::drawHideValues()
{
    for(int b=0; b<_inputs; b++)
    {
        inputLabel[b]->hide();
    }

    for(int b=0; b<_hiddenX; b++)
    {
        for(int c=0; c<_hiddenY; c++)
        {
            hiddenLabel[b][c]->hide();
        }
    }
    for(int b=0; b<_outputs; b++)
    {
        outputLabel[b]->hide();;
    }
}
void QtGeneticNet::saveBest(std::string fileName)
{
    if(!lockForWrongData)
    {

    }

}
std::vector<float> QtGeneticNet::genom(unsigned int animal)
{
    if(!lockForWrongData)
    return net->genom(animal);
}
std::vector<std::vector<float>  > QtGeneticNet::genom()
{
    if(!lockForWrongData)
    return net->genom();
}
void QtGeneticNet::netInfoToConfig()
{
    config->parameter("--QT-GENETIC-NET-VERSSION--",QtGeneticNetVersion);
    config->parameter("NET_INPUTS",std::to_string(_inputs));
    config->parameter("NET_HIDDENX",std::to_string(_hiddenX));
    config->parameter("NET_HIDDENY",std::to_string(_hiddenY));
    config->parameter("NET_OUTPUTS",std::to_string(_outputs));
    config->parameter("NET_ANIMALS",std::to_string(_animals));
    config->parameter("NET_ENABLEBIAS",std::to_string(_enableBias));
    config->parameter("NET_ENABLEAVERAGE",std::to_string(_enableAverage));
    config->parameter("mutationFactor",std::to_string(_mutationFactor));
    config->parameter("mutationDivisor",std::to_string(_mutationDivisor));

    config->save();
}
int QtGeneticNet::configToNetInfo()
{
    int ret = 0;
    config->load();
    _inputs        = atoi(config->parameter("NET_INPUTS").c_str());
    _hiddenX       = atoi(config->parameter("NET_HIDDENX").c_str());
    _hiddenY       = atoi(config->parameter("NET_HIDDENY").c_str());
    _outputs       = atoi(config->parameter("NET_OUTPUTS").c_str());
    _animals       = atoi(config->parameter("NET_ANIMALS").c_str());
    _enableBias    = atoi(config->parameter("NET_ENABLEBIAS").c_str());
    _enableAverage = atoi(config->parameter("NET_ENABLEAVERAGE").c_str());
    if(config->parameter("mutationFactor").c_str() != config->noparam())
    {
        _mutationFactor = stof(config->parameter("mutationFactor").c_str());

    }
    if(config->parameter("mutationDivisor").c_str() != config->noparam())
    {
       _mutationDivisor = stof(config->parameter("mutationDivisor").c_str());
    }
    if(_inputs <1){ret = 1;}
    if(_hiddenX <1){ret = 1;}
    if(_hiddenY <1){ret = 1;}
    if(_outputs <1){ret = 1;}
    if(_animals <1){ret = 1;}
    if(_mutationFactor <0){_mutationFactor = 0;}
    if(_mutationFactor >1){_mutationFactor = 1;}

   /* if(config->parameter("--QT-GENETIC-NET-VERSSION--")      != QtGeneticNetVersion)   {ret=+1;qDebug(("--QT-GENETIC-NET-VERSSION-- \""+config->parameter("--QT-GENETIC-NET-VERSSION--")+"\"").c_str());}
    if(atoi(config->parameter("NET_INPUTS").c_str())         != _inputs         )               {ret=+1;qDebug(("NET_INPUTS \""+config->parameter("NET_INPUTS"                 )+"\"").c_str());}
    if(atoi(config->parameter("NET_HIDDENX").c_str())        != _hiddenX        )              {ret=+1;qDebug(("NET_HIDDENX \""+config->parameter("NET_HIDDENX"                )+"\"").c_str());}
    if(atoi(config->parameter("NET_HIDDENY").c_str())        != _hiddenY        )              {ret=+1;qDebug(("NET_HIDDENY \""+config->parameter("NET_HIDDENY"                )+"\"").c_str());}
    if(atoi(config->parameter("NET_OUTPUTS").c_str())        != _outputs        )              {ret=+1;qDebug(("NET_OUTPUTS \""+config->parameter("NET_OUTPUTS"                )+"\"").c_str());}
    if(atoi(config->parameter("NET_ANIMALS").c_str())        != _animals        )              {ret=+1;qDebug(("NET_ANIMALS \""+config->parameter("NET_ANIMALS"                )+"\"").c_str());}
    if(atoi(config->parameter("NET_ENABLEBIAS").c_str())     != _enableBias     )           {ret=+1;qDebug(("NET_ENABLEBIAS \""+config->parameter("NET_ENABLEBIAS"             )+"\"").c_str());}
    if(atoi(config->parameter("NET_ENABLEAVERAGE").c_str())  != _enableAverage  )        {ret=+1;qDebug(("NET_ENABLEAVERAGE \""+config->parameter("NET_ENABLEAVERAGE"          )+"\"").c_str());}
*/
   // qDebug("configReadEnd");
    return ret;
}
QColor QtGeneticNet::weightColor(float signal,float weight,float colorMultiplayer)
{
    int maxCol = 200;
    float factor = signal * weight*colorMultiplayer*maxCol;
    QColor col;
    int valuePositive;
    int valueNegative;


    if(factor<0)
    {
        valuePositive = 0;
        valueNegative = abs(factor);
    }
    else
    {
        valuePositive = factor;
        valueNegative = 0;
    }
    //valuePositive = MAP(valuePositive,0,maxMapAmount,0,200);
    //valueNegative = MAP(valueNegative,0,maxMapAmount,0,200);

    if(valuePositive<0)     {valuePositive=0;}
    if(valuePositive>maxCol)   {valuePositive=maxCol;}
    if(valueNegative<0)     {valueNegative=0;}
    if(valueNegative>maxCol)   {valueNegative=maxCol;}
    col = QColor(maxCol-valuePositive,maxCol-valueNegative,maxCol-valuePositive-valueNegative);


   return col;
}
std::vector<float>  QtGeneticNet::gohstNetOutput(unsigned int animal)
{
  if(!lockForWrongData)
  {
    if(animal >= _animals)
    {
      animal = _animals-1;
    }
    return gohstNet[animal].output();
  }
  return std::vector<float>(1,0);
}
float               QtGeneticNet::gohstNetOutput(unsigned int animal,unsigned int output)
{
  //qDebug("QtGeneticNet::gohstNetOutput()");
  if(!lockForWrongData)
  {
   // qDebug("animal: %i _animals: %i",animal,_animals);
    if(animal >= _animals)
    {
      animal = _animals-1;
    }
    if(output >= _outputs)
    {
      output = _outputs-1;
    }
    //qDebug("animal %i signal %i = %.8f",animal,output,gohstNet[animal].output(output));
    return gohstNet[animal].output(output);
  }
  return 0;
}
void                QtGeneticNet::gohstNetInput(unsigned int animal,std::vector<float> signal)
{
  if(!lockForWrongData)
  {
    if(animal >= _animals)
    {
      animal = _animals-1;
    }
    if(signal.size() == _inputs)
    {
      if(animal == 0)
      {
        input(signal);
      }
       gohstNet[animal].input(signal);
    }
  }
}
void                QtGeneticNet::gohstNetInput(unsigned int animal,unsigned int input,float signal)
{
  if(!lockForWrongData)
  {
    if(animal >= _animals)
    {
      animal = _animals-1;
    }
    if(input >= _inputs)
    {
      input = _inputs-1;
    }
    gohstNet[animal].input(input,signal);
    if(animal == 0)
    {
      net->input(input,signal);
    }
  }
}
std::vector<float>  QtGeneticNet::gohstNetInput(unsigned int animal)
{
  if(animal>_animals-1){animal = _animals-1;}
  return gohstNet[animal].input();
}
float               QtGeneticNet::gohstNetInput(unsigned int animal,unsigned int input)
{
  if(animal>_animals-1){animal = _animals-1;}
  if(input>_inputs){input=_inputs;}
  return gohstNet[animal].input(input);
}
int QtGeneticNet::MAP(int input,int von1,int bis1,int von2,int bis2)
{
  if(input == von1)
    {
      return von2;
    }
  int resultat;
  float tmp;
  float VON1 = von1;
  float VON2 = von2;
  float BIS1 = bis1;
  float BIS2 = bis2;

  tmp = input;
 // printf("RES1: %.3f\n",tmp);
 // printf("calc ((%i-%i)*(%")
  tmp = ((BIS2-VON2)*(tmp-VON1)/(BIS1-VON1))+VON2;
  //printf("RES2: %.3f\n",tmp);
  resultat = tmp;
   //printf("RES3: %i\n",resultat);
  return resultat;
}
void QtGeneticNet::load()
{
    net->loadData(netDataFileName);
}
void QtGeneticNet::load(std::string fileName)
{
    net->loadData(fileName);
}
void QtGeneticNet::save()
{
    net->saveData(netDataFileName);
}
void QtGeneticNet::save(std::string fileName)
{
    net->saveData(fileName);
}
void QtGeneticNet::mutationFactor(float fac)
{
    net->mutationFactor(fac);
    _mutationFactor = net->mutationFactor();
}
float QtGeneticNet::mutationFactor()
{
    return net->mutationFactor();
}
void QtGeneticNet::mutationDivisor(float divisor)
{
  net->mutationDivisor(divisor);
  _mutationDivisor = net->mutationDivisor();
}
float QtGeneticNet::mutationDivisor()
{
  return net->mutationDivisor();
}


