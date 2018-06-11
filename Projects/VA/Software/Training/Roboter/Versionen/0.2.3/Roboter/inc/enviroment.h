#ifndef ENVIROMENT_H
#define ENVIROMENT_H
#include <QApplication>
#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <vector>


#include "objects/circle.h"
#include "objects/line.h"
#include "objects/roboter.h"
#include "draw.h"


struct coord
{
    QPoint pos;
    QSize size;
};
typedef struct coord coord;

class Enviroment
{
  public:
    Enviroment(int x,int y,int obstAm,int anzRobot,float globalScale);
    Enviroment(int x,int y,int obstAm,int anzRobot,float globalScale,unsigned int sensorAnz);
    Enviroment(int x,int y,int obstAm,int anzRobot,float globalScale,unsigned int sensorAnz,float sensorAngle);
    ~Enviroment();
    void randomGenObsticle();
    void randomGenRobots();
    void draw(QPainter *painter,QPoint drawPos);
    void setColor(QColor col);
    //void rotateRobot(float degree);
    //void turnLeftRobot(float degree = 1);
    //void turnRightRobot(float degree = 1);
    //void moveForwardRobot(float steps = 1);
    //void moveBckwardRobot(float steps = 1);
    //void rawControlRobot(float left,float right,float stepMultipliyer);
    bool checkForCollision();
   // float beamLengthRobot(int beamNr);

    std::vector<Roboter> roboter;
    std::vector<bool>    roboterCollieded;
    //Roboter *roboter;
    //Roboter *roboter2;
    std::vector<Circle>  circle;
    std::vector<Line>    frame;
    void beamStandardLength(float length);
    float beamStandardLength();
    void obsticleAmount(unsigned int amount);
    unsigned int obsticleAmount();

  private:
    float getShortest(std::vector<float> data);
   // void drawCircle(QPainter *painter,coord circ,QPoint drawPos);
   // void drawLine(QPainter *painter,QColor color,int size,QPoint pointA,QPoint pointB);
    int sizeX;  //-->
    int sizeY;  //  v
    int _obsticleAmount;
    int minObsticleSize;
    int maxObsticleSize;
    QColor obsticleColor;

    int farbabstufung;
    int frameSize;
    int frameWidth;
    QColor frameColor;

    float globalScale;
    float _beamStandardLength;
};

#endif // ENVIROMENT_H
