#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "enviroment.h"
#include <QKeyEvent>
#include "qtgeneticnet.h"
#include "config.h"
#include "graph.h"

#include <direct.h>
#include <windows.h>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void paintEvent(QPaintEvent *e);
private slots:
  void timerFunctionUpdate();
  void timerFunction();
  void timerFunction1s();
  void timerFunction5s();
  void timerFunctionRandGen();
  void on_RightSpeedSlder_valueChanged(int value);
  void on_LeftSpeedSlider_destroyed();
  void on_LeftSpeedSlider_valueChanged(int value);

  void on_net_control_toggle_button_clicked();

  void on_net_control_kill_button_clicked();

  void on_pushButton_clicked();


  void on_MutationFactor_Slider_valueChanged(int value);
  void on_drawNetXDistance_slider_valueChanged(int value);
  void on_drawNetYDistance_slider_valueChanged(int value);
  void on_drawNeuronSize_slider_valueChanged(int value);
  void on_drawConnectionSize_slider_valueChanged(int value);
  void on_drawAnimal_slider_valueChanged(int value);
  void on_robotPathSize_slider_valueChanged(int value);
  void on_net_control_beamLength_slider_valueChanged(int value);
  void on_net_control_obsticleAmount_slider_valueChanged(int value);
  void on_net_control_addSpeed_slider_valueChanged(int value);
  void on_MutationDivisor_Slider_valueChanged(int value);

 void resizeEvent(QResizeEvent* event);

 void on_net_control_speedMultiplayerToOne_button_clicked();
 void on_net_control_speedMultiplayerTo10_button_clicked();
 void on_net_control_speedMultiplayerTo30_button_clicked();
 void on_net_control_speedMultiplayerTo60_button_clicked();
 void on_net_control_speedMultiplayerTo100_button_clicked();

  protected:
  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
private:
  void handleKeys();
  void handleNet();
  int MAP(int input,int von1,int bis1,int von2,int bis2);
  float MAPF(float input,float von1,float bis1,float von2,float bis2);
  void saveData();
  void readConfig();
  void drawScore(QPainter *painter,QPoint drawPos);
  float getBigest(vector<float> data,int *_pos = NULL);


  std::vector<bool> keys;

  Ui::MainWindow *ui;

  Enviroment *enviroment;
  int enviromentSize;

  QPoint enviromentDrawPos;
  QTimer * timer;
  QTimer * timer1s;
  QTimer * timer5s;
  QTimer * timerRand;
  QTimer * timerUpdate;
  Config * netLog;

  
    float counter;

    float robotLeft;
    float robotRight;
    //-------------------------NET
    QtGeneticNet *net;
    
    unsigned int net_inputs;
    unsigned int net_hiddenX;
    unsigned int net_hiddenY;
    unsigned int net_outputs;
    unsigned int net_animals;
    float        net_mutationFactor;
    bool         net_enableBias;
    bool         net_enableAverage;

    bool         netControlToggle;



    vector<float>net_score;
    unsigned int net_activeAnimal;
    vector<bool> net_deathAnimal;     //------------
    unsigned int generation;
    unsigned int tmpGeneration;
    //-----------DRAW
    unsigned int net_draw_neuronRadius;
    unsigned int net_draw_abstandX;
    unsigned int net_draw_abstandY;
    unsigned int net_draw_connectionSize;
    //---------------
    //-----------scoring-----
    vector<float>        net_walkDistance;    //---------
    vector<QPointF>      net_robot_lastPos;   //---------
    vector<int>          net_robot_turns;     //---------
    vector<unsigned int> net_robot_Steps;     //---------
    //-----------------------
    //----------------------------
    //-----------config-----------
    unsigned int saveIntervall;
    unsigned int averageSize;
    int          net_robot_maxTurns;
    unsigned int net_robot_maxSteps;
    int          enviroment__obsticleAmount;
    int          enviroment_randPosTimeIntervall;
    float        robot_beamAngleOffset;
    //----------------------------
    float globalScale;


    FILE *logFile;


    vector<float> averageScore;

    float         gesScore;
    float         gesAverageScore;
    float         gesAverageScoreOfFirst;
    float         bestScore;
   //int           runtime


    //---------------GRAPH---------
    Graph *graph;
    //-----------------------------

    //---------------PATH----------
    vector<vector<Line> > robotPath;
    unsigned int robotPathSize;
    //-----------------------------
    unsigned int activeKeyControlAnimal;
    float addSpeed;

    QColor        robotSelectedColor;
    QColor        robotUnselectedColor;

    bool          keyEvent;
    bool          _paintEvent;
    bool          sliderControlEvent;

/*
    vector<Line>testVec;
    int testInt;*/
};

#endif // MAINWINDOW_H
