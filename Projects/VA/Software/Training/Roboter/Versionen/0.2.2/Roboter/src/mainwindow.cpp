#include "ui_mainwindow.h"
#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->version_label->setText("Copyright © 2018, Alex Krieg\nAll rights reserved\n6.6.2018\nv0.2.2");

  char cwd[MAX_PATH+1];
  _getcwd(cwd,MAX_PATH);
  qDebug("pfad %s", cwd);
  ui->startPath_label->setText(QString(cwd));

  globalScale = 0.25;
//------------------------------------------Net---------------------------------------------------
  net_inputs                = 6;
  net_hiddenX               = 2;
  net_hiddenY               = 12;
  net_outputs               = 2;
  net_animals               = 10;
  net_mutationFactor        = 0.01;
  net_enableBias            = true;
  net_enableAverage         = false;

  net_draw_neuronRadius     = ui->drawNeuronSize_slider->value();
  net_draw_abstandX         = ui->drawNetXDistance_slider->value();
  net_draw_abstandY         = ui->drawNetYDistance_slider->value();
  net_draw_connectionSize   = ui->drawConnectionSize_slider->value();





  net        = new QtGeneticNet(net_inputs,net_hiddenX,net_hiddenY,net_outputs,
                                net_animals,net_mutationFactor,net_enableBias,
                                net_enableAverage,"robotConfig.txt","gen.net",this);
  net_animals = net->animals();
 // qDebug("animals: %i",net_animals);
  readConfig();
  net->drawSetup(net_draw_neuronRadius,net_draw_abstandX,net_draw_abstandY,net_draw_connectionSize);
  if(atoi(net->config->parameter("displayInputValue").c_str()) == 1)
  {
      ui->displayInputValue_checkBox->setChecked(true);
  }else{net->config->parameter("displayInputValue","0");}
  if(atoi(net->config->parameter("displayHiddenValue").c_str()) == 1)
  {
      ui->displayHiddenValue_checkBox->setChecked(true);
  }else{net->config->parameter("displayHiddenValue","0");}
  if(atoi(net->config->parameter("displayOutputValue").c_str()) == 1)
  {
      ui->displayOutputValue_checkBox->setChecked(true);
  }else{net->config->parameter("displayOutputValue","0");}

/*  net->drawInputValue(ui->displayInputValue_checkBox->isChecked());
  net->drawHiddenValue(ui->displayHiddenValue_checkBox->isChecked());
  net->drawOutputValue(ui->displayOutputValue_checkBox->isChecked());*/

  net_score                 = vector<float>(net_animals,0.0);
  net_activeAnimal          = 0;
  ui->activeAnimal_label->setText(QString::fromStdString(to_string(net_activeAnimal)));
  net_deathAnimal           = vector<bool>(net_animals,false);
  net_robot_turns           = vector<int>(net_animals,0);
  net_walkDistance          = vector<float>(net_animals,0);
  net_robot_Steps           = vector<unsigned int>(net_animals,0);
  net_robot_lastPos         = vector<QPointF>(net_animals,QPointF(-1,-1));


  net_mutationFactor        = net->mutationFactor();
//------------------------------------------------------------------------------------------------

  gesScore                    = 0;
  gesAverageScore             = 0;
  gesAverageScoreOfFirst      = 0;
  bestScore                   = 0;

  //net_lastPosSize = 5;
  //net_robot_lastPos = QPointF(-1,-1);
  //net_lastPos = vector<QPointF>(net_lastPosSize);
  //net_robot_Steps = 0;
  keyEvent = false;
  _paintEvent = false;
  sliderControlEvent = false;
  tmpGeneration = 0;
  netControlToggle  = false;
  //enviromentSize = 2400;
  enviromentDrawPos.setX(10);
  enviromentDrawPos.setY(10);
  enviroment = new Enviroment(enviromentSize,enviromentSize,enviroment__obsticleAmount,net_animals,globalScale);
  for(int a=0; a<enviroment->roboter.size(); a++)
  {
    enviroment->roboter[a].beamAngleOffset(robot_beamAngleOffset);
  }

  timer = new QTimer(this);
  connect(timer,SIGNAL(timeout()),this,SLOT(timerFunction()));
  timer->start(0);
  timerRand = new QTimer(this);
  connect(timerRand,SIGNAL(timeout()),this,SLOT(timerFunctionRandGen()));
  timerRand->start(enviroment_randPosTimeIntervall);
  timer1s = new QTimer(this);
  connect(timer1s,SIGNAL(timeout()),this,SLOT(timerFunction1s()));
  timer1s->start(1000);
  timerUpdate = new QTimer(this);
  connect(timerUpdate,SIGNAL(timeout()),this,SLOT(timerFunctionUpdate()));
  timerUpdate->start(33);//30Hz
  timer5s = new QTimer(this);
  connect(timer5s,SIGNAL(timeout()),this,SLOT(timerFunction5s()));
  timer5s->start(5000);

  connect(ui->drawNetXDistance_slider,SIGNAL(valueChanged(int)),this,SLOT(on_drawNetXDistance_slider_valueChanged()));
  connect(ui->drawNetYDistance_slider,SIGNAL(valueChanged(int)),this,SLOT(on_drawNetYDistance_slider_valueChanged()));
  connect(ui->drawNeuronSize_slider,SIGNAL(valueChanged(int)),this,SLOT(on_drawNeuronSize_slider_valueChanged()));
  connect(ui->drawConnectionSize_slider,SIGNAL(valueChanged(int)),this,SLOT(on_drawConnectionSize_slider_valueChanged()));
  connect(ui->drawAnimal_slider,SIGNAL(valueChanged(int)),this,SLOT(on_drawAnimal_slider_valueChanged()));
  connect(ui->net_control_beamLength_slider,SIGNAL(valueChanged(int)),this,SLOT(on_net_control_beamLength_slider_valueChanged()));
  connect(ui->net_control_obsticleAmount_slider,SIGNAL(valueChanged(int)),this,SLOT(on_net_control_obsticleAmount_slider_valueChanged()));
  connect(ui->net_control_addSpeed_slider,SIGNAL(valueChanged(int)),this,SLOT(on_net_control_addSpeed_slider_valueChanged()));
  connect(ui->MutationDivisor_Slider,SIGNAL(valueChanged(int)),this,SLOT(on_MutationDivisor_Slider_valueChanged()));


  counter =0;
  enviroment->beamStandardLength((float)ui->net_control_beamLength_slider->value());
  enviroment->checkForCollision();
  keys = std::vector<bool>(12);//w a s d + up left down right y,x c,v
  robotLeft = 0;
  robotRight = 0;
  ui->generation_label->setText(QString::fromStdString(to_string(generation)));
  ui->MutationFactor_label->setText(QString::fromStdString(to_string(net_mutationFactor)));
  ui->MutationFactor_Slider->setValue(net_mutationFactor*10000);
  ui->MutationDivisor_Slider->setValue(net->mutationDivisor());

  graph = new Graph(500,200);
  graph->scale(1,50);
  graph->width(2);
  enviroment->roboter[0].enableBeamDraw();
  robotPathSize          = ui->robotPathSize_slider->value();
 // qDebug("robotPath new");
  robotPath              = vector<vector<Line>  >(net_animals);

  ui->drawAnimal_slider->setMaximum(net_animals-1);
  ui->net_control_beamLength_slider->setValue(enviroment->beamStandardLength());
  ui->net_control_beamLength_label->setText(QString::fromStdString(to_string(ui->net_control_beamLength_slider->value())));
  ui->net_control_obsticleAmount_slider->setValue(enviroment->obsticleAmount());
  ui->net_control_obsticleAmount_label->setText(QString::fromStdString(to_string(ui->net_control_obsticleAmount_slider->value())));
  addSpeed = (float)ui->net_control_addSpeed_slider->value()/100;
  ui->net_control_addSpeed_label->setText(QString::fromStdString(to_string(addSpeed)));
  ui->drawAnimal_label->setText(QString::fromStdString(to_string(net_activeAnimal)));
  net->mutationDivisor((float)ui->MutationDivisor_Slider->value());
  ui->MutationDivisor_label->setText(QString::fromStdString(to_string((int)net->mutationDivisor())));
  robotUnselectedColor = QColor(255,150,0);
  robotSelectedColor   = QColor(0,150,255);
  enviroment->roboter[ui->drawAnimal_slider->value()].bodyColor(robotSelectedColor);

  ticksPerSecondTimer = new QTimer(this);
  connect(ticksPerSecondTimer,SIGNAL(timeout()),this,SLOT(ticksPerSecondTimerFunction()));
  ticksPerSecondTimer->start(500);
  ticksPerSecondCounter = 0;
  ticksPerSecond = 0;
  ticksPerSecondBufferSize = 10;
  ticksPerSecondTimerFunction();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{

  QPainter painter(this);
  for(int a=0; a<robotPath.size(); a++)
  {
    for(int b=0; b<robotPath[a].size(); b++)
    {
      if(a == net_activeAnimal)
      {
        robotPath[a][b].color(robotSelectedColor);
      }
      else
      {
        robotPath[a][b].color(robotUnselectedColor);
        robotPath[a][b].draw(&painter,enviromentDrawPos);
      }

    }
  }
  for(int b=0; b<robotPath[net_activeAnimal].size(); b++)
  {
      robotPath[net_activeAnimal][b].draw(&painter,enviromentDrawPos);
  }
  enviroment->draw(&painter,enviromentDrawPos);
  float colorMulti = ui->net_draw_colorMultipliyer_slider->value();
  colorMulti/=10;
  net->draw(&painter,QPoint(enviromentDrawPos.x()+20+enviromentSize*globalScale,enviromentDrawPos.y()),colorMulti,net_activeAnimal);
  drawScore(&painter,QPoint(enviromentDrawPos.x(),enviromentDrawPos.y() + enviromentSize*globalScale + 20));
  graph->draw(&painter,QPoint(enviromentDrawPos.x()+enviromentSize*globalScale + 20,enviromentDrawPos.y() + enviromentSize*globalScale ));

  //painter.begin(widget);

  painter.setRenderHint(QPainter::Antialiasing);
  //qDebug(to_string(colorMulti).c_str());
  painter.setRenderHints(QPainter::RenderHints(0x04),true);
}
void MainWindow::timerFunctionUpdate()
{
    handleKeys();
    if(_paintEvent)
    {
        update();
        _paintEvent = false;
    }
}
void MainWindow::timerFunction()
{
    if(keyEvent || netControlToggle || sliderControlEvent)
    {
        if(timer->interval() != 0)
        timer->setInterval(0);
    }
    else
    {
        if(timer->interval() != 100)
        timer->setInterval(100);
    }

    handleNet();
    if(netControlToggle)
    {
        ticksPerSecondCounter++;
    }
}
void MainWindow::timerFunction1s()
{
    ui->tod_label->setText("");
}
void MainWindow::timerFunction5s()
{
    int alive = 0;
    for(int a=0; a<net_animals; a++)
    {
        if(net_deathAnimal[a]==false)
        {
            alive++;
        }
    }
    if(alive == 1)
    {
        for(int a=0; a<net_animals; a++)
        {
            net_deathAnimal[a] = true;
        }
    }
}
void MainWindow::timerFunctionRandGen()
{
   // enviroment->randomGenObsticle();
}
void MainWindow::ticksPerSecondTimerFunction()
{
    ticksPerSecond = 0;
    ticksPerSecondList.push_back(ticksPerSecondCounter*1000/(float)ticksPerSecondTimer->interval());
    if(ticksPerSecondList.size() > ticksPerSecondBufferSize)
    {
        ticksPerSecondList.erase(ticksPerSecondList.begin());
    }
    for(int a=0; a<ticksPerSecondList.size(); a++)
    {
        ticksPerSecond+=ticksPerSecondList[a];
    }
    ticksPerSecondCounter = 0;
    ticksPerSecond /= (float)ticksPerSecondList.size();
    ui->ticksPerSecond_label->setText(QString::number(ticksPerSecond));
}
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(char(e->key()))
    {
        case 'P'://up
        {
            qDebug("roboterPos --> x: %i y: %i",enviroment->roboter[0].pos().x(),enviroment->roboter[0].pos().y());
            break;
        }
        case 19://up
        {
            keys[4] = 1;
            break;
        }
        case 18://left
        {
            keys[5] = 1;
            break;
        }
        case 21://down
        {
            keys[6] = 1;
            break;
        }
        case 20://right
        {
            keys[7] = 1;
            break;
        }

        case 'W':
        {
            if(netControlToggle)
            enviroment->roboter[net_activeAnimal].enableBeamDraw();
            _paintEvent = true;
            keys[0] = 1;
            break;
        }
        case 'A':
        {
            if(netControlToggle)
            enviroment->roboter[net_activeAnimal].enableBeamDraw();
            _paintEvent = true;
            keys[1] = 1;
            break;
        }
        case 'S':
        {
            if(netControlToggle)
            enviroment->roboter[net_activeAnimal].enableBeamDraw();
            _paintEvent = true;
            keys[2] = 1;
            break;
        }
        case 'D':
        {
            if(netControlToggle)
            enviroment->roboter[net_activeAnimal].enableBeamDraw();
            _paintEvent = true;
            keys[3] = 1;
            break;
        }

        case 'Y':
        {
            if(keys[9] == 1 && keys[8] == 1)
            {
              keys[8] = 0;
              keys[9] = 0;
            }
            else
            {
              keys[8] = 1;
              keys[9] = 0;
            }

            break;
        }
        case 'X':
        {
           // testVec.clear();
/*
            qDebug("size: %i",testVec.size());
            testInt = 1;
        int x= testVec.size();
            for(int a=0; a<x; a++)
            {
              testVec.erase(testVec.begin());
            }
             testVec.shrink_to_fit();*/
            break;
        }
        case 'C':
        {
            keys[10] = 1;
            break;
        }
        case 'V':
        {
            keys[11] = 1;
            break;
        }
        case 'B':
        {
            for(int a=0; a<net_animals; a++)
            {
              enviroment->roboter[a].enableBeamDraw();
            }
            _paintEvent = true;
            break;
        }
        case 'N':
        {
            enviroment->roboter[net_activeAnimal].enableBeamDraw();
            _paintEvent = true;
            break;
        }
    }

    //qDebug("Key: %c %i",char(e->key()),char(e->key()));
}
void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    switch(char(e->key()))
    {
        case 19://up
        {
            keys[4] = 0;
            break;
        }
        case 18://left
        {
            keys[5] = 0;
            break;
        }
        case 21://down
        {
            keys[6] = 0;
            break;
        }
        case 20://right
        {
            keys[7] = 0;
            break;
        }

        case 'W':
        {
            if(netControlToggle)
            enviroment->roboter[net_activeAnimal].disableBeamDraw();
            _paintEvent = true;
            keys[0] = 0;
            break;
        }
        case 'A':
        {
            if(netControlToggle)
            enviroment->roboter[net_activeAnimal].disableBeamDraw();
            _paintEvent = true;
            keys[1] = 0;
            break;
        }
        case 'S':
        {
            if(netControlToggle)
            enviroment->roboter[net_activeAnimal].disableBeamDraw();
            _paintEvent = true;
            keys[2] = 0;
            break;
        }
        case 'D':
        {
            if(netControlToggle)
            enviroment->roboter[net_activeAnimal].disableBeamDraw();
            _paintEvent = true;
            keys[3] = 0;
            break;
        }

        case 'Y':
        {
             if(keys[9] == 0 && keys[8] == 1)
            {
              keys[8] = 0;
              keys[9] = 1;
            }
            else
            {
              keys[8] = 0;
              keys[9] = 0;
            }
            break;
        }
        case 'X':
        {
       // testInt = 0;
            //keys[9] = 0;
            break;
        }
        case 'C':
        {
            keys[10] = 0;
            break;
        }
        case 'V':
        {
            keys[11] = 0;
            break;
        }
        case 'B':
        {
            for(int a=0; a<net_animals; a++)
            {
              enviroment->roboter[a].disableBeamDraw();
            }
            _paintEvent = true;
            break;
        }
        case 'N':
        {
            enviroment->roboter[net_activeAnimal].disableBeamDraw();
            _paintEvent = true;
            break;
        }
    }

   // qDebug("Key: %c %i",char(e->key()),char(e->key()));
}
void MainWindow::handleKeys()
{
   float moveSpeed = (float)ui->net_control_stepMultiplayer->value()/10;
   float rawLeft = 0;
   float rawRight = 0;
   float rawSteps = 1;
   bool rawData = false;
   bool slider = true;
   keyEvent = false;
   if(keys[8])
   {
     /*float randL = rand()%100;
     randL/=100;
     float randR = rand()%100;
     randR/=100;*/
     float divisor = 1000;
     float left = enviroment->roboter[0].beamLength(2)/divisor+enviroment->roboter[0].beamLength(3)/divisor;
     float right= enviroment->roboter[0].beamLength(5)/divisor+enviroment->roboter[0].beamLength(0)/divisor;

     left+= enviroment->roboter[0].beamLength(1)/divisor/2 - enviroment->roboter[0].beamLength(4)/divisor;
     right+= enviroment->roboter[0].beamLength(1)/divisor/2 - enviroment->roboter[0].beamLength(4)/divisor;

     //qDebug("l %.8f r %.8f",left,right);
       enviroment->roboter[0].rawControl(left,right,ui->net_control_stepMultiplayer->value()/10);
       //rawData = true;
       //rawLeft = rawSteps;
   }
   if(keys[9])
   {
       rawLeft *= (-1);
   }
   if(keys[10])
   {
       rawData = true;
       rawRight = rawSteps;
   }
   if(keys[11])
   {
       rawRight *= (-1);
   }
   if(!netControlToggle)
   {
       if(keys[0] || keys[4])//W or up
       {
           //qDebug("up");
           rawData = false;
           slider = false;
           keyEvent = true;
           _paintEvent = true;
           enviroment->roboter[net_activeAnimal].forward(moveSpeed);
       }
       if(keys[1] || keys[5])//A or left
       {
          // qDebug("left");
           rawData = false;
           slider = false;
           keyEvent = true;
           _paintEvent = true;
           enviroment->roboter[net_activeAnimal].turnLeft(moveSpeed);
       }
       if(keys[2] || keys[6])//S or down
       {
           //qDebug("down");
           rawData = false;
           slider = false;
           keyEvent = true;
           _paintEvent = true;
           enviroment->roboter[net_activeAnimal].backward(moveSpeed);
       }
       if(keys[3] || keys[7])//D or right
       {
           //qDebug("right");
           rawData = false;
           slider = false;
           keyEvent = true;
           _paintEvent = true;
           enviroment->roboter[net_activeAnimal].turnRight(moveSpeed);
       }

     if(rawData)
     {
         slider = false;
         _paintEvent = true;
         enviroment->roboter[net_activeAnimal].rawControl(rawLeft,rawRight,1);
     }
     if(slider)
     {
         if(robotRight  != 0 || robotLeft != 0)
         {
            enviroment->roboter[net_activeAnimal].rawControl(robotLeft,robotRight,ui->net_control_stepMultiplayer->value()/10);
            //enviroment->checkForCollision();
            _paintEvent = true;
            sliderControlEvent = true;
         }
     }
  }
}
void MainWindow::on_RightSpeedSlder_valueChanged(int value)
{
    robotRight = (float)value/100;
    if(!netControlToggle)
    _paintEvent = true;

    ui->net_control_right_label->setText(QString::fromStdString(to_string(robotRight)));

    //qDebug("right: %.5f",robotRight);
}
void MainWindow::on_LeftSpeedSlider_destroyed()
{

}
void MainWindow::on_LeftSpeedSlider_valueChanged(int value)
{
    robotLeft = (float)value/100;
    if(!netControlToggle)
    _paintEvent = true;

    ui->net_control_left_label->setText(QString::fromStdString(to_string(robotLeft)));

  //  qDebug("left: %.5f",robotLeft);
}
void MainWindow::handleNet()
{
     //qDebug("handleNet1");
    if(netControlToggle)
    {
      for(int a=0; a<net_animals; a++)
      {
        if(net_deathAnimal[a] == false)
        {
          vector<float> inputs = enviroment->roboter[a].beamLength();
          for(int b=0; b<net_inputs; b++)
          {

              inputs[b] /= (1000*globalScale);
              float _rand = rand()%100;
              _rand = (_rand-50)/1000;
              inputs[b] += _rand;
              if(inputs[b] > 1){inputs[b] = 1;}
              inputs[b] = 1-inputs[b];
          }
          net->gohstNetInput(a,inputs);
        }
      }
      net->run();
      _paintEvent = true;
      for(int a=0; a<net_animals; a++)
      {
        if(net_deathAnimal[a] == false)
        {
          float left  = net->gohstNetOutput(a,0)+addSpeed;//     get outputs
          float right = net->gohstNetOutput(a,1)+addSpeed;//

         // qDebug("net: %i left: %.8f right: %.8f",a,left,right);
          if(a==net_activeAnimal)
          {
            ui->RightSpeedSlder->setValue(left*100);
            ui->LeftSpeedSlider->setValue(right*100);
          }
          float firstAngle = enviroment->roboter[a].angle();
          enviroment->roboter[a].rawControl(left,right,ui->net_control_stepMultiplayer->value()/10);
          float divAngle = enviroment->roboter[a].angle()-firstAngle;
          if(divAngle<0){divAngle*=(-1);}


          float radDiv = left-right;
          if(radDiv<0){radDiv*=(-1);}
          //radDiv = (radDiv)/2;
          //radDiv = 1/(1+radDiv*radDiv*radDiv*radDiv);
          //=1/(1+A21*A21*A21*A21)
          net_robot_turns[a] = enviroment->roboter[a].turns();
          if(net_robot_lastPos[a].x()==-1 && net_robot_lastPos[a].y() == -1)
          {
              net_robot_lastPos[a] = enviroment->roboter[a].posF();
          }

          QPointF resultat = enviroment->roboter[a].posF();

         // resultat.setX(net_robot_lastPos[a].x()-resultat.x());
         // resultat.setY(net_robot_lastPos[a].y()-resultat.y());

          if(resultat.x() != net_robot_lastPos[net_activeAnimal].x() || resultat.y() != net_robot_lastPos[net_activeAnimal].y())
          {
           //resultat = enviroment->roboter[net_activeAnimal].posF();
            if(robotPath[a].size() >= robotPathSize)
            {
              for(int b=0; b<robotPath[a].size()-robotPathSize; b++)
              {
                robotPath[a].erase(robotPath[a].begin());
              }
            }
            robotPath[a].push_back(Line());
            if(robotPath[a].size() == 1)
            {
              robotPath[a][robotPath[a].size()-1].startPos(QPoint((int)resultat.x(),(int)resultat.y()));
            }
            else
            {
              robotPath[a][robotPath[a].size()-1].startPos(robotPath[a][robotPath[a].size()-2].endPos());
            }
            robotPath[a][robotPath[a].size()-1].endPos(QPoint((int)resultat.x(),(int)resultat.y()));
           // robotPath[a][robotPath[a].size()-1].color(robotUnselectedColor);
            robotPath[a][robotPath[a].size()-1].width(2);
          }
        //  qDebug("makeLine");

          resultat.setX(net_robot_lastPos[a].x()-resultat.x());
          resultat.setY(net_robot_lastPos[a].y()-resultat.y());
          net_robot_lastPos[a] = enviroment->roboter[a].posF();
          float tmpDistance = sqrt(resultat.x()*resultat.x()+resultat.y()*resultat.y());


          if(left+right<0)
          {
              tmpDistance*=(-1);
          }
          net_walkDistance[a]            += tmpDistance;
          float averageSensorDistance = 0;
          for(int b=0; b<net->gohstNetInput(a).size(); b++)
          {
            averageSensorDistance += net->gohstNetInput(a,b);
          }
          averageSensorDistance/= net->gohstNetInput(a).size();
          averageSensorDistance/=10;
         /* if(net_robot_turns[a] == 0)
          {
              //qDebug("score: %.8f \t+= %.8f * radDiv: %.8f                              \tdistance: %.3f\tradL: %.8f radR: %.8f",net_score[net_activeAnimal],tmpDistance,radDiv,net_walkDistance,left,right);
              net_score[a] += tmpDistance * 0.01;
          }
          else*/
          {
              //qDebug("score: %.8f \t+= %.8f * radDiv: %.8f / (1+net_robot_turns: %i ) \tdistance: %.3f\tradL: %.8f radR: %.8f",net_score[net_activeAnimal],tmpDistance,radDiv,net_robot_turns,net_walkDistance,left,right);


              //qDebug(("netScore "+to_string(net_score[a])+"\t add: "+to_string(left+right+(tmpDistance * 0.01 )/ ((1+divAngle/*+((float)net_robot_turns[a]/10)*/)))+"\t"+to_string(left)+" + "+to_string(right)+" + ("+to_string(tmpDistance) + " * 0.01)/(1+"+to_string(divAngle)+")").c_str());

            net_score[a] += ((left+right)/100+(tmpDistance * 0.01 ))/ ((1+divAngle+((float)net_robot_turns[a]/10)));

          }
          if(net_robot_turns[a] >= net_robot_maxTurns)
          {
              net_deathAnimal[a] = true;
          }
          net_robot_Steps[a]++;
          if(net_robot_Steps[a] >= net_robot_maxSteps)
          {
              net_deathAnimal[a] = true;
          }
          if(net_score[a] <= -1)
          {
              net_deathAnimal[a] = true;
          }
          if(a==0)
          {
            //ui->net_score_label->setText(QString::fromStdString(to_string(net_score[net_activeAnimal])));
          }
        }
      }

      //--------------------------------------------------------
     // qDebug("checkForCollision1");
      enviroment->checkForCollision();
     // qDebug("checkForCollision2");
      for(int a=0; a<net_deathAnimal.size(); a++)
      {
        if(enviroment->roboterCollieded[a] == true)
        {
          net_deathAnimal[a] = true;
        }
      }
      for(int a=0; a<net_animals; a++)
      {
        if(net_deathAnimal[a])//collision
        {
            if(robotPath[a].size() != 0)
            {
              robotPath[a].clear();
              robotPath[a].shrink_to_fit();
            }
            if(enviroment->roboter[a].pos() != QPoint(-10,-10))
            {
                enviroment->roboter[a].pos(QPoint(-10,-10));
                enviroment->roboter[a].pos(QPoint(-10,-10));
            }

        }
      }

        bool check = true;
        for(int a=0; a<net_animals; a++)
        {
          if(net_deathAnimal[a]==false)
          {
            check = false;
          }
        }
        if(check)//reset Net
        {
     //     qDebug("check == true");



          gesScore                    = 0;
          gesAverageScore             = 0;
          gesAverageScoreOfFirst      = 0;
          for(int a=0; a<net_animals; a++)
          {
            net_deathAnimal[a]=0;
            net_robot_lastPos[a] = QPointF(-1,-1);
            net_robot_turns[a]=0;
            net_robot_Steps[a]=0;
            enviroment->roboter[a].resetTurns();
            if(net_score[a]<0)
            {
                net_score[a] = 0;
            }
            net_score[a] += 1;
            gesScore += net_score[a];
          }
          gesScore/=net_animals;
          if(gesScore > bestScore)
          {
            bestScore = gesScore;
          }

 //qDebug("net learn");
          if(ui->net_control_improve_checkBox->isChecked())
          {
            net->learn(net_score);
          }
 //qDebug("--1");
          if(averageScore.size() > averageSize)
          {
              averageScore.erase(averageScore.begin());
              averageScore.shrink_to_fit();
          }
          // qDebug("--2");
          averageScore.push_back(gesScore);
          gesAverageScoreOfFirst = net_score[0];
          for(int b=0; b<averageScore.size();b++)
          {
              gesAverageScore         += averageScore[b];
          }
          gesAverageScore /=averageScore.size();

 //qDebug("--5");

          tmpGeneration++;
          generation++;
          if(saveIntervall <= tmpGeneration)
          {
              tmpGeneration = 0;
              if(ui->net_control_improve_checkBox->isChecked())
              {
                saveData();
              }
          }
         //  qDebug("--6");

          graph->scale(2,(float)1000/bestScore);
          graph->push_back(gesScore*10);
          ui->generation_label->setText(QString::fromStdString(to_string(generation)));
          ui->net_score_label->setText(QString::fromStdString(to_string(gesScore)));
          for(int a=0; a<net_animals; a++)
          {
              net_score[a] = 0;
          }
          for(int a=0; a<net_deathAnimal.size(); a++)
          {
            enviroment->roboterCollieded[a] = false;
          }
      //     qDebug("random");
          enviroment->randomGenObsticle();
          enviroment->randomGenRobots();
          enviroment->checkForCollision();
// qDebug("end");
        }
    }
    else
    {
        if(keyEvent || sliderControlEvent)
        {
            enviroment->checkForCollision();
            for(int a=0; a<net_deathAnimal.size(); a++)
            {
              enviroment->roboterCollieded[a] = false;
            }
            vector<float> inputs = enviroment->roboter[net_activeAnimal].beamLength();
            for(int b=0; b<net_inputs; b++)
            {

                inputs[b] /= (1000*globalScale);
                if(inputs[b] > 1){inputs[b] = 1;}
                inputs[b] = 1-inputs[b];
            }
           // qDebug("signal: %.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t",inputs[0],inputs[1],inputs[2],inputs[3],inputs[4],inputs[5]);
            QPointF resultat = enviroment->roboter[net_activeAnimal].posF();
          //  resultat.setX(net_robot_lastPos[net_activeAnimal].x()-resultat.x());
          //  resultat.setY(net_robot_lastPos[net_activeAnimal].y()-resultat.y());
            //qDebug("size: %i",robotPath[net_activeAnimal].size());
            if(resultat.x() != net_robot_lastPos[net_activeAnimal].x() || resultat.y() != net_robot_lastPos[net_activeAnimal].y())
            {
              //resultat = enviroment->roboter[net_activeAnimal].posF();
              if(robotPath[net_activeAnimal].size() >= robotPathSize)
              {
                robotPath[net_activeAnimal].erase(robotPath[net_activeAnimal].begin());
                //qDebug("erase: %i",robotPath[net_activeAnimal].size());
              }
            // qDebug("robotPath new Line");
              robotPath[net_activeAnimal].push_back(Line());
              if(robotPath[net_activeAnimal].size() == 1)
              {
                robotPath[net_activeAnimal][robotPath[net_activeAnimal].size()-1].startPos(QPoint((int)resultat.x(),(int)resultat.y()));
              }
              else
              {
                robotPath[net_activeAnimal][robotPath[net_activeAnimal].size()-1].startPos(robotPath[net_activeAnimal][robotPath[net_activeAnimal].size()-2].endPos());
              }
              robotPath[net_activeAnimal][robotPath[net_activeAnimal].size()-1].endPos(QPoint((int)resultat.x(),(int)resultat.y()));
             // robotPath[net_activeAnimal][robotPath[net_activeAnimal].size()-1].color(robotUnselectedColor);
              robotPath[net_activeAnimal][robotPath[net_activeAnimal].size()-1].width(2);
            }

            resultat.setX(net_robot_lastPos[net_activeAnimal].x()-resultat.x());
            resultat.setY(net_robot_lastPos[net_activeAnimal].y()-resultat.y());
            net_robot_lastPos[net_activeAnimal] = enviroment->roboter[net_activeAnimal].posF();
            net->input(inputs);
            net->gohstNetInput(net_activeAnimal,inputs);
            net->run();
        }
    }
    //qDebug("handleNet2");
}
int  MainWindow::MAP(int input,int von1,int bis1,int von2,int bis2)
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
float  MainWindow::MAPF(float input,float von1,float bis1,float von2,float bis2)
{
  if(input == von1)
    {
      return von2;
    }
  float resultat;
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
void MainWindow::on_net_control_toggle_button_clicked()
{
    if(netControlToggle)
    {
        netControlToggle = false;
        ui->RightSpeedSlder->setValue(0);
        ui->LeftSpeedSlider->setValue(0);
        enviroment->roboter[net_activeAnimal].enableBeamDraw();
    }
    else
    {
        netControlToggle = true;
        enviroment->roboter[net_activeAnimal].disableBeamDraw();
    }
}
void MainWindow::on_net_control_kill_button_clicked()
{
  for(int a=0; a<net_deathAnimal.size(); a++)
  {
    net_deathAnimal[a] = true;
  }
}
void MainWindow::on_pushButton_clicked()
{
    //saveData();
    net->config->parameter("obsticleAmount",to_string(enviroment__obsticleAmount));
    net->config->parameter("drawNetXSize",to_string(net_draw_abstandX));
    net->config->parameter("drawNetYSize",to_string(net_draw_abstandY));
    net->config->parameter("drawNetNeuronRadius",to_string(net_draw_neuronRadius));
    net->config->parameter("drawNetConnectionSize",to_string(net_draw_connectionSize));

    net->netInfoToConfig();
    net->save();
}
void MainWindow::saveData()
{
    //qDebug("net->save();");
    net->save();
    //qDebug("netLog->parameter(\"generation\",to_string(generation));");
    netLog->parameter("generation",to_string(generation));
    //qDebug("netLog->save();");
    netLog->save();
    //qDebug("logFile = fopen(\"learn.csv\",\"a\");");
    logFile = fopen("learn.csv","a");
    if(logFile)
    {
        fprintf(logFile,"%.8f;%.8f;%.8f\n",gesAverageScoreOfFirst,gesScore,gesAverageScore);
        fclose(logFile);
    }
    //qDebug("fclose(logFile);");
}

void MainWindow::readConfig()
{
  if(net->config->parameter("averageSize") != net->config->noparam())
  {
      averageSize = atoi(net->config->parameter("averageSize").c_str());
      if(averageSize <=0)
      {
          averageSize = 1;
      }
      qDebug("averageSize: %i",averageSize);
  }
  else
  {
      averageSize = 20;
      net->config->parameter("averageSize",to_string(averageSize));
      qDebug("net->config-> averageSize not found");
       qDebug("averageSize: %i",averageSize);
  }
  if(net->config->parameter("saveIntervall") != net->config->noparam())
  {
      saveIntervall = atoi(net->config->parameter("saveIntervall").c_str());
      if(saveIntervall <=0)
      {
          saveIntervall = 1;
      }
       qDebug("saveIntervall: %i",saveIntervall);
  }
  else
  {
      saveIntervall = 1;
      net->config->parameter("saveIntervall",to_string(saveIntervall));
      qDebug("net->config-> saveIntervall not found");
      qDebug("saveIntervall: %i",saveIntervall);

  }
  if(net->config->parameter("robot_maxTurns") != net->config->noparam())
  {
      net_robot_maxTurns = atoi(net->config->parameter("robot_maxTurns").c_str());
      if(net_robot_maxTurns <=0)
      {
          net_robot_maxTurns = 1;
      }
      qDebug("robot_maxTurns: %i",net_robot_maxTurns);

  }
  else
  {
      net_robot_maxTurns = 50;
      net->config->parameter("robot_maxTurns",to_string(net_robot_maxTurns));
      qDebug("net->config-> robot_maxTurns not found");
      qDebug("robot_maxTurns: %i",net_robot_maxTurns);


  }
  if(net->config->parameter("robot_maxSteps") != net->config->noparam())
  {
      net_robot_maxSteps = atoi(net->config->parameter("robot_maxSteps").c_str());
      if(net_robot_maxSteps <=0)
      {
          net_robot_maxSteps = 1;
      }
      qDebug("robot_maxSteps: %i",net_robot_maxSteps);

  }
  else
  {
      net_robot_maxSteps = 5000;
      net->config->parameter("robot_maxSteps",to_string(net_robot_maxSteps));
      qDebug("net->config-> robot_maxSteps not found");
      qDebug("robot_maxSteps: %i",net_robot_maxSteps);

  }
  if(net->config->parameter("obsticleAmount") != net->config->noparam())
  {
      enviroment__obsticleAmount = atoi(net->config->parameter("obsticleAmount").c_str());
      if(enviroment__obsticleAmount <0)
      {
          enviroment__obsticleAmount = 0;
      }
       qDebug("obsticleAmount: %i",enviroment__obsticleAmount);
  }
  else
  {
      enviroment__obsticleAmount = 10;
      net->config->parameter("obsticleAmount",to_string(enviroment__obsticleAmount));
      qDebug("net->config-> obsticleAmount not found");
      qDebug("obsticleAmount: %i",enviroment__obsticleAmount);

  }
  if(net->config->parameter("globalScale") != net->config->noparam())
  {
      globalScale = stof(net->config->parameter("globalScale").c_str());
      if(globalScale <0)
      {
          globalScale = 1;
      }
      qDebug("globalScale: %.8f",globalScale);
  }
  else
  {
      globalScale = 1;
      net->config->parameter("globalScale",to_string(globalScale));
      qDebug("net->config-> globalScale not found");
      qDebug("globalScale: %.8f",globalScale);
  }
  if(net->config->parameter("obsticleRandTime") != net->config->noparam())
  {
      enviroment_randPosTimeIntervall = atoi(net->config->parameter("obsticleRandTime").c_str());
      if(enviroment_randPosTimeIntervall <10)
      {
          enviroment_randPosTimeIntervall = 10;
      }
      qDebug("obsticleRandTime: %i",enviroment_randPosTimeIntervall);
  }
  else
  {
      enviroment_randPosTimeIntervall = 3000;
      net->config->parameter("obsticleRandTime",to_string(enviroment_randPosTimeIntervall));
      qDebug("net->config-> obsticleRandTime not found");
      qDebug("obsticleRandTime: %i",enviroment_randPosTimeIntervall);
  }
  if(net->config->parameter("enviromentSize") != net->config->noparam())
  {
      enviromentSize = atoi(net->config->parameter("enviromentSize").c_str());
      if(enviromentSize <100)
      {
          enviromentSize = 100;
      }
      qDebug("enviromentSize: %i",enviromentSize);
  }
  else
  {
      enviromentSize = 600;
      net->config->parameter("enviromentSize",to_string(enviromentSize));
      qDebug("net->config-> enviromentSize not found");
      qDebug("enviromentSize: %i",enviromentSize);
  }
  if(net->config->parameter("robot_beamAngleOffset") != net->config->noparam())
  {
      robot_beamAngleOffset = stof(net->config->parameter("robot_beamAngleOffset").c_str());
      qDebug("robot_beamAngleOffset: %.3f",robot_beamAngleOffset);
  }
  else
  {
      robot_beamAngleOffset = 0;
      net->config->parameter("robot_beamAngleOffset",to_string(robot_beamAngleOffset));
      qDebug("net->config-> robot_beamAngleOffset not found");
      qDebug("robot_beamAngleOffset: %.3f",robot_beamAngleOffset);
  }
  if(net->config->parameter("drawNetXSize") != net->config->noparam())
  {
      net_draw_abstandX = atoi(net->config->parameter("drawNetXSize").c_str());
      ui->drawNetXDistance_slider->setValue(net_draw_abstandX);
      qDebug("drawNetXSize: %i",net_draw_abstandX);
  }
  else
  {
      net->config->parameter("drawNetXSize",to_string(net_draw_abstandX));
      qDebug("net->config-> drawNetXSize not found");
      qDebug("drawNetXSize: %i",net_draw_abstandX);
  }
  if(net->config->parameter("drawNetYSize") != net->config->noparam())
  {
      net_draw_abstandY = atoi(net->config->parameter("drawNetYSize").c_str());
      ui->drawNetYDistance_slider->setValue(net_draw_abstandY);
      qDebug("drawNetYSize: %i",net_draw_abstandY);
  }
  else
  {
      net->config->parameter("drawNetYSize",to_string(net_draw_abstandY));
      qDebug("net->config-> drawNetYSize not found");
      qDebug("drawNetYSize: %i",net_draw_abstandY);
  }
  if(net->config->parameter("drawNetNeuronRadius") != net->config->noparam())
  {
      net_draw_neuronRadius = atoi(net->config->parameter("drawNetNeuronRadius").c_str());
      ui->drawNeuronSize_slider->setValue(net_draw_neuronRadius);
      qDebug("drawNetNeuronRadius: %i",net_draw_neuronRadius);
  }
  else
  {
      net->config->parameter("drawNetNeuronRadius",to_string(net_draw_neuronRadius));
      qDebug("net->config-> drawNetNeuronRadius not found");
      qDebug("drawNetNeuronRadius: %i",net_draw_neuronRadius);
  }
  if(net->config->parameter("drawNetConnectionSize") != net->config->noparam())
  {
      net_draw_connectionSize = atoi(net->config->parameter("drawNetConnectionSize").c_str());
      ui->drawConnectionSize_slider->setValue(net_draw_connectionSize);
      qDebug("drawNetConnectionSize: %i",net_draw_connectionSize);
  }
  else
  {
      net->config->parameter("drawNetConnectionSize",to_string(net_draw_connectionSize));
      qDebug("net->config-> drawNetConnectionSize not found");
      qDebug("drawNetConnectionSize: %i",net_draw_connectionSize);
  }
  if(net->config->parameter("stepMultiplayer") != net->config->noparam())
  {
      ui->net_control_stepMultiplayer->setValue(atoi(net->config->parameter("stepMultiplayer").c_str())*10);
      qDebug("stepMultiplayer: %i",ui->net_control_stepMultiplayer->value());
  }
  else
  {
      net->config->parameter("stepMultiplayer",to_string(ui->net_control_stepMultiplayer->value()));
      qDebug("net->config-> stepMultiplayer not found");
      qDebug("stepMultiplayer: %i",ui->net_control_stepMultiplayer->value());
  }



 // net->drawSetup(net_draw_neuronRadius,net_draw_abstandX,net_draw_abstandY,net_draw_connectionSize);
  net->config->save();

  netLog = new Config("netLog.txt");
  if(!netLog->load())
  {
      generation = atoi(netLog->parameter("generation").c_str());
  }
  else
  {
      generation = 0;
      netLog->parameter("generation",to_string(generation));

  }
  netLog->save();
}
void MainWindow::drawScore(QPainter *painter,QPoint drawPos)
{
  vector<Line> scoreLine(net_animals,Line());
  int breite = 5;
  int yOffset = 100;
  int bestPos = 0;
  float bigest = getBigest(net_score,&bestPos);
  if(ui->drawAnimal_checkBox->isChecked())
  {
   // net_activeAnimal = bestPos;
    ui->drawAnimal_slider->setValue(bestPos);
  }
  //scoreDivisor = net_score[bigest]/100;

  for(int a=0; a<net_animals; a++)
  {
    if(net_score[a] <0)
    {
      scoreLine[a].set(QPoint(a*breite,yOffset),QPoint(0,1),(-1)*MAPF(net_score[a],0,bigest,0,100),breite,QColor(255,100,0));
    }
    else
    {
      scoreLine[a].set(QPoint(a*breite,yOffset),QPoint(0,-1),MAPF(net_score[a],0,bigest,0,100),breite,QColor(100,255,0));
    }
    if(net_deathAnimal[a]==true)
    {
      scoreLine[a].color(QColor(255,0,0));
    }
    if(a == net_activeAnimal)
    {
      scoreLine[a].color(enviroment->roboter[net_activeAnimal].bodyColor());
    }

  }
  for(int a=0; a<net_animals; a++)
  {
    scoreLine[a].draw(painter,drawPos);
  }
}
float MainWindow::getBigest(std::vector<float> data,int *_pos)
{
    float bigest = data[0];
    int counter = 0;
    while(counter < data.size())
    {
        counter = 0;
        for(int a=0; a<data.size(); a++)
        {
            if(bigest < data[a] && data[a]>=0)
            {
                bigest = data[a];
                if(_pos != NULL)
                {
                  *_pos = a;
                }
            }
            else
            {
                counter++;
            }
        }
    }
    return bigest;
}

void MainWindow::on_MutationFactor_Slider_valueChanged(int value)
{
    net_mutationFactor = (float)value/10000;
    ui->MutationFactor_label->setText(QString::fromStdString(to_string(net_mutationFactor)));
    net->mutationFactor(net_mutationFactor);
}
void MainWindow::resizeEvent(QResizeEvent* event)
{
  QSize windowSize;
  windowSize.setHeight(ui->centralWidget->geometry().height());
  windowSize.setWidth(ui->centralWidget->geometry().width());

  ui->NetControlFrame->setGeometry(windowSize.width()-ui->NetControlFrame->geometry().width(),ui->NetControlFrame->geometry().y(),ui->NetControlFrame->geometry().width(),ui->NetControlFrame->geometry().height());
  ui->NetAdjustFrame->setGeometry(windowSize.width()-ui->NetAdjustFrame->geometry().width(),ui->NetAdjustFrame->geometry().y(),ui->NetAdjustFrame->geometry().width(),ui->NetAdjustFrame->geometry().height());
  ui->version_label->setGeometry(windowSize.width()-ui->version_label->geometry().width(),ui->version_label->geometry().y(),ui->version_label->geometry().width(),ui->version_label->geometry().height());
  ui->startPath_label->setGeometry(windowSize.width()-ui->startPath_label->geometry().width(),ui->startPath_label->geometry().y(),ui->startPath_label->geometry().width(),ui->startPath_label->geometry().height());
}
void MainWindow::closeEvent(QCloseEvent *e)
{
	on_pushButton_clicked();
	e->accept();
	qDebug("EXIT");
}
void MainWindow::on_drawNetXDistance_slider_valueChanged(int value)
{
  net_draw_abstandX = value;
  net->drawSetup(net_draw_neuronRadius,net_draw_abstandX,net_draw_abstandY,net_draw_connectionSize);
  _paintEvent = true;
}
void MainWindow::on_drawNetYDistance_slider_valueChanged(int value)
{
  net_draw_abstandY = value;
  net->drawSetup(net_draw_neuronRadius,net_draw_abstandX,net_draw_abstandY,net_draw_connectionSize);
  _paintEvent = true;
}
void MainWindow::on_drawNeuronSize_slider_valueChanged(int value)
{
  net_draw_neuronRadius = value;
  net->drawSetup(net_draw_neuronRadius,net_draw_abstandX,net_draw_abstandY,net_draw_connectionSize);
  _paintEvent = true;
}
void MainWindow::on_drawConnectionSize_slider_valueChanged(int value)
{
  net_draw_connectionSize = value;
  net->drawSetup(net_draw_neuronRadius,net_draw_abstandX,net_draw_abstandY,net_draw_connectionSize);
  _paintEvent = true;
}
void MainWindow::on_drawAnimal_slider_valueChanged(int value)
{
  enviroment->roboter[net_activeAnimal].bodyColor(enviroment->roboter[net_activeAnimal].standardBodyColor());

  if(!netControlToggle)
  enviroment->roboter[net_activeAnimal].disableBeamDraw();

  //net->drawHideValues();
  net_activeAnimal = value;
  /*net->drawInputValue(true);
  net->drawOutputValue(true);*/

  if(!netControlToggle)
  enviroment->roboter[net_activeAnimal].enableBeamDraw();

  ui->activeAnimal_label->setText(QString::fromStdString(to_string(net_activeAnimal)));
  ui->drawAnimal_label->setText(QString::fromStdString(to_string(net_activeAnimal)));
  enviroment->roboter[net_activeAnimal].bodyColor(robotSelectedColor);
  _paintEvent = true;
}
void MainWindow::on_robotPathSize_slider_valueChanged(int value)
{
  robotPathSize = value;
  _paintEvent = true;
}
void MainWindow::on_net_control_beamLength_slider_valueChanged(int value)
{
  enviroment->beamStandardLength((float)value);
  ui->net_control_beamLength_label->setText(QString::fromStdString(to_string(value)));
  _paintEvent = true;
}
void MainWindow::on_net_control_obsticleAmount_slider_valueChanged(int value)
{
  enviroment__obsticleAmount = value;
  enviroment->obsticleAmount(enviroment__obsticleAmount);
  ui->net_control_obsticleAmount_label->setText(QString::fromStdString(to_string(value)));
  enviroment->checkForCollision();
  _paintEvent = true;
}
void MainWindow::on_net_control_addSpeed_slider_valueChanged(int value)
{
  addSpeed = (float)value/100;
  ui->net_control_addSpeed_label->setText(QString::fromStdString(to_string(addSpeed)));
  _paintEvent = true;
}
void MainWindow::on_MutationDivisor_Slider_valueChanged(int value)
{
  net->mutationDivisor((float)value);
  ui->MutationDivisor_label->setText(QString::fromStdString(to_string((int)net->mutationDivisor())));
}

void MainWindow::on_net_control_speedMultiplayerToOne_button_clicked()
{
    ui->net_control_stepMultiplayer->setValue(10);
}
void MainWindow::on_net_control_speedMultiplayerTo10_button_clicked()
{
  ui->net_control_stepMultiplayer->setValue(100);
}
void MainWindow::on_net_control_speedMultiplayerTo30_button_clicked()
{
  ui->net_control_stepMultiplayer->setValue(300);
}
void MainWindow::on_net_control_speedMultiplayerTo60_button_clicked()
{
  ui->net_control_stepMultiplayer->setValue(600);
}
void MainWindow::on_net_control_speedMultiplayerTo100_button_clicked()
{
  ui->net_control_stepMultiplayer->setValue(1000);
}

void MainWindow::on_displayInputValue_checkBox_toggled(bool checked)
{
    net->drawInputValue(checked);
    net->config->parameter("displayInputValue",to_string(checked));
}
void MainWindow::on_displayHiddenValue_checkBox_toggled(bool checked)
{
    net->drawHiddenValue(checked);
    net->config->parameter("displayHiddenValue",to_string(checked));
}
void MainWindow::on_displayOutputValue_checkBox_toggled(bool checked)
{
    net->drawOutputValue(checked);
    net->config->parameter("displayOutputValue",to_string(checked));
}
