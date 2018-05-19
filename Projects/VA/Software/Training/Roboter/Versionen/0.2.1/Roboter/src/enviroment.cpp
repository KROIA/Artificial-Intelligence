#include "enviroment.h"

Enviroment::Enviroment(int x,int y,int obstAm,int anzRobot,float globalScale)
{
  this->globalScale = globalScale;
    qDebug("globalScale: %.8f %.8f",globalScale,this->globalScale);
  sizeX             = x*this->globalScale;
  sizeY             = y;
  _obsticleAmount    = obstAm;
  obsticleColor     = QColor(0,255,0);//Green
  minObsticleSize   = 20*this->globalScale;
  maxObsticleSize   = 40*this->globalScale;
  //obsticle          = std::vector<coord>(_obsticleAmount);

  farbabstufung     = 30;
  frameSize         = sizeX;
  frameWidth        = 3;
  frameColor        = QColor(0,0,0);//Black
  _beamStandardLength = 100;
  
  circle = std::vector<Circle>(_obsticleAmount);
 // qDebug("frame new 4");
  frame  = std::vector<Line>(4,Line());
 // qDebug("end frame new Lines");
  frame[0].set(QPoint(0,0),QPoint(10,0),frameSize,frameWidth,frameColor);
  frame[1].set(QPoint(frameSize,0),QPoint(0,10),frameSize,frameWidth,frameColor);
  frame[2].set(QPoint(0,0),QPoint(0,10),frameSize,frameWidth,frameColor);
  frame[3].set(QPoint(0,frameSize),QPoint(10,0),frameSize,frameWidth,frameColor);
  roboter = std::vector<Roboter>  (anzRobot,Roboter());
  for(int a=0; a<anzRobot; a++)
  {
    roboter[a].beamLength((float)_beamStandardLength*this->globalScale);
    roboter[a].beamWidth(1);
    roboter[a].radius(20*this->globalScale);
    roboter[a].disableBeamDraw();
  }
  roboterCollieded = std::vector<bool>(anzRobot,false);


  randomGenRobots();
  randomGenObsticle();


}

Enviroment::~Enviroment()
{

}

void Enviroment::randomGenObsticle()
{
   // qDebug("randomGen");
  //std::srand(std::time(NULL));
  int size;
  bool _while = false;
  //bool collision = false;;
  //qDebug("");


  for(int a=0; a<_obsticleAmount; a++)
  {
    _while  = true;
    while(_while)
    {
      _while  = false;
      size = minObsticleSize+rand()%(maxObsticleSize-minObsticleSize+1);
      circle[a].size(size);
      circle[a].pos(QPoint(10+size+(rand()%(frameSize-20-2*size)),10+size+(rand()%(frameSize-20-2*size))));
      for(int b=0; b<a; b++)
      {
        if(circle[a].collisionDistance(circle[b].pos(),circle[b].size()) <= 10)
        {
            _while = true;
        }
        for(int c=0; c<roboter.size(); c++)
        {
          if(circle[a].collisionDistance(roboter[c].collision().pos(),roboter[c].collision().size()) <= 10)
          {
              _while = true;
          }
        }
      }
    }
  }

//if(circle[a].collision(robotBody2.pos(),robotBody2.size()))
 /* for(int a=0; a<_obsticleAmount; a++)
  {
      size = minObsticleSize+rand()%(maxObsticleSize-minObsticleSize+1);
      circle[a].size(size);
      circle[a].pos(QPoint(10+size+(rand()%(frameSize-20-size-size)),10+size+(rand()%(frameSize-20-size-size))));
      for(int b=0; b<a; b++)
      {
          if(circle[a].collisionDistance(circle[b].pos(),circle[b].size()) <= 10)
          {
              collision = true;
          }
          if(circle[a].collisionDistance(roboter->collision().pos(),roboter->radius()) <= 10)
          {
              collision = true;
          }
         if(circle[a].collisionDistance(roboter2->collision().pos(),roboter2->radius()) <= 10)
          {
              collision = true;
          }
          while(collision)
          {
              int counter = 0;
              //qDebug("-----------------BEGIN---------------------");
              for(int c=0; c<a; c++)
              {
                  if(counter == 0)
                  {
                    size = minObsticleSize+rand()%(maxObsticleSize-minObsticleSize+1);
                    circle[a].size(size);
                    circle[a].pos(QPoint(10+size+(rand()%(frameSize-20-size-size)),10+size+(rand()%(frameSize-20-size-size))));
                    //qDebug("collision???          a: %i posY: %i posY: %i c: %i posX: %i posY: %i distance: %.8f",a,circle[a].pos().x(),circle[a].pos().y(),c,circle[c].pos().x(),circle[c].pos().y(),circle[a].collisionDistance(circle[c].pos(),circle[c].size()));
                  }
                  if(circle[a].collisionDistance(circle[c].pos(),circle[c].size()) <= 10)
                  {
                      //collision = true;
                      //qDebug("collision = true;    a: %i posY: %i posY: %i c: %i posX: %i posY: %i distance: %.8f",a,circle[a].pos().x(),circle[a].pos().y(),c,circle[c].pos().x(),circle[c].pos().y(),circle[a].collisionDistance(circle[c].pos(),circle[c].size()));
                  }
                  else
                  {
                      if(circle[a].collisionDistance(roboter->collision().pos(),roboter->radius()) <= 10)
                      {}
                      else
                      {
                        if(circle[a].collisionDistance(roboter2->collision().pos(),roboter2->radius()) <= 10)
                        {}
                        else
                          {
                            counter++;

                            //qDebug("collision = false;    a: %i posY: %i posY: %i c: %i posX: %i posY: %i distance: %.8f",a,circle[a].pos().x(),circle[a].pos().y(),c,circle[c].pos().x(),circle[c].pos().y(),circle[a].collisionDistance(circle[c].pos(),circle[c].size()));
                            //c=a;
                            if(counter >= a)
                            {
                                //qDebug("collision = false; counter: %i a: %i",counter,a);
                                collision = false;
                            }
                         }
                      }
                  }
              }
               //qDebug("-----------------END---------------------");
          }
          if(circle[a].collisionDistance(circle[b].pos(),circle[b].size()) <= 10)
          {
                        qDebug("     collision   a: %i posY: %i posY: %i b: %i posX: %i posY: %i distance: %.8f",a,circle[a].pos().x(),circle[a].pos().y(),b,circle[b].pos().x(),circle[b].pos().y(),circle[a].collisionDistance(circle[b].pos(),circle[b].size()));
          }
      }

  }*/
}
void Enviroment::randomGenRobots()
{
  bool _while = false;
  for(int a=0; a<roboter.size(); a++)
  {
    _while  = true;
    while(_while)
    {
      _while  = false;
      roboter[a].pos(QPoint(roboter[a].radius()+20+rand()%(frameSize-20-2*roboter[a].radius()),roboter[a].radius()+20+rand()%(frameSize-20-2*roboter[a].radius())));
      for(int b=0; b<a; b++)
      {
        if(roboter[a].collision().collisionDistance(roboter[b].collision().pos(),roboter[b].collision().size()) <= 10)
        {
            _while = true;
        }
      }
    }
  }
}
void Enviroment::draw(QPainter *painter,QPoint drawPos)
{

    for(int a=0;a<_obsticleAmount;a++)
    {
        circle[a].draw(painter,drawPos);
    }
  frame[0].draw(painter,drawPos);
  frame[1].draw(painter,drawPos);
  frame[2].draw(painter,drawPos);
  frame[3].draw(painter,drawPos);
  for(int a=0; a<roboter.size(); a++)
  {
    if(roboter[a].pos().x() != -10 && roboter[a].pos().y() != -10)
    {
     roboter[a].draw(painter,drawPos);
    }
  }

 // roboter2->draw(painter,drawPos);
}
void Enviroment::setColor(QColor col)
{
  obsticleColor = col;
}
/*
void Enviroment::rotateRobot(float degree)
{
    roboter->angle(degree);
    roboter->forward();
}*/
bool Enviroment::checkForCollision()
{
    //qDebug("collision start");
        bool ret = false;
        for(int a=0; a<roboter.size(); a++)//Roboter
        {
          roboter[a].beamLength((float)_beamStandardLength*globalScale);
          roboter[a].unhit();
        }
                   // roboter2->beamLength((float)800.0);
                   // roboter2->unhit();
                    //Circle robotBody = roboter->collision();
     /*              // Circle robotBody2 = roboter2->collision();
        for(int a=0; a<roboter.size(); a++)
        {
          roboterCollieded[a]=false;
        }
    */
      //qDebug("1");

        for(int a=0; a<circle.size();a++)//Kreise
        {
            if(circle[a].color()!=obsticleColor)
            {
                circle[a].color(obsticleColor);
            }
            for(int b=0; b<roboter.size(); b++)//Roboter
            {
              if(roboterCollieded[b] == false)
              {
                if(circle[a].collision(roboter[b].collision().pos(),roboter[b].collision().size()))
                {
                    roboter[b].setLastPos();
                    roboter[b].hit();
                    ret = true;
                    roboterCollieded[b] = true;
                    circle[a].color(QColor(255,0,0));
                   // qDebug("animal %i circle %i ",)
                }
              }
           }
        }
       // qDebug("2");
        for(int a=0; a<frame.size();a++)           //Rahmen
        {
            if(frame[a].color()!=frameColor)
            {
                frame[a].color(frameColor);
            }
            for(int b=0; b<roboter.size(); b++)//Roboter
            {
              if(roboterCollieded[b] == false)
              {
                if(getShortest(roboter[b].collision().collisionFactor(frame[a].startPos(),frame[a].endPos())) != 1)
                {
                    roboter[b].setLastPos();
                    roboter[b].hit();
                    ret = true;
                    roboterCollieded[b] = true;
                    frame[a].color(QColor(255,0,0));
                }
              }
            }

        }
       // qDebug("3");
        for(int a=0; a<roboter.size(); a++)
        {
          for(int b=0; b<a; b++)
          {
            if(roboterCollieded[a] == false && roboterCollieded[b] == false)
            {
              if(roboter[a].collision().collision(roboter[b].collision().pos(),roboter[b].collision().size()))
              {
                  roboter[b].setLastPos();
                  roboter[b].hit();
                  roboter[a].setLastPos();
                  roboter[a].hit();
                  ret = true;
                  roboterCollieded[b] = true;
                  roboterCollieded[a] = true;
              }
            }
          }
        }


        std::vector<std::vector<std::vector<float>  >  > __roboterBeamCollisionFactor(roboter.size(),std::vector<std::vector<float> >(roboter[0].beams(),std::vector<float>(roboter[0].collision(0).size(),_beamStandardLength*globalScale)));

       // qDebug("4");
        for(int a=0; a<_obsticleAmount;a++)//Kreise
        {
          for(int d=0; d<roboter.size(); d++)
          {
            if(roboterCollieded[d] == false)
            {
              for(int b=0; b<roboter[d].beams();b++)   //Roboter Sensoren
              {
                  std::vector<float> _collisionfactor;
                  std::vector<float> __collisionfactor;
                 // float collisionfator;
                  std::vector<Line> sensor = roboter[d].collision(b);
                  for(int c=0; c<sensor.size(); c++)
                  {
                      _collisionfactor = circle[a].collisionFactor(sensor[c].startPos(),sensor[c].endPos());
                      __collisionfactor.push_back(getShortest(_collisionfactor));
                  }
                  for(int c=0;c<__collisionfactor.size();c++)
                  {
                      __collisionfactor[c] = roboter[d].beamLength(b,c)*__collisionfactor[c];
                      if(__collisionfactor[c] < __roboterBeamCollisionFactor[d][b][c])
                      {
                        __roboterBeamCollisionFactor[d][b][c] = __collisionfactor[c];
                      }
                  }
                  //roboter[d].beamLength(__collisionfactor,b);
                //  if(d>__roboterBeamCollisionFactor.size()-1){qDebug("d>");}
                //  if(b>__roboterBeamCollisionFactor[d].size()-1){qDebug("b>");}

              }
            }
          }
            //Roboter körper
        }
       // qDebug("5");
        for(int a=0; a<roboter.size();a++)//Roboter
        {
            //qDebug("a");
          for(int d=0; d<roboter.size(); d++)
          {
            if(roboterCollieded[a] == false && roboterCollieded[d] == false && d!=a)
            {
              for(int b=0; b<roboter[d].beams();b++)   //Roboter Sensoren
              {
                  std::vector<float> _collisionfactor;
                  std::vector<float> __collisionfactor;
                 // float collisionfator;
                  std::vector<Line> sensor = roboter[d].collision(b);
                  for(int c=0; c<sensor.size(); c++)
                  {
                      _collisionfactor = roboter[a].collision().collisionFactor(sensor[c].startPos(),sensor[c].endPos());
                      __collisionfactor.push_back(getShortest(_collisionfactor));
                  }
                  for(int c=0;c<__collisionfactor.size();c++)
                  {
                      __collisionfactor[c] = roboter[d].beamLength(b,c)*__collisionfactor[c];
                      if(__collisionfactor[c] < __roboterBeamCollisionFactor[d][b][c])
                      {
                         __roboterBeamCollisionFactor[d][b][c] = __collisionfactor[c];
                      }
                  }
                 // roboter[d].beamLength(__collisionfactor,b);
                  //roboter[d].setBeamPos();

                  //__roboterBeamCollisionFactor[d][b] = __collisionfactor;
              }
            }
          }
        }
        //qDebug("6");
        for(int a=0; a<frame.size();a++)           //Rahmen
        {
          for(int d=0; d<roboter.size(); d++)
          {
            if(roboterCollieded[d] == false)
            {
              for(int b=0; b<roboter[d].beams();b++)   //Roboter Sensoren
              {
                  std::vector<float> __collisionfactor;
                  float collisionfator;
                  std::vector<Line> sensor = roboter[d].collision(b);
                  for(int c=0; c<sensor.size(); c++)
                  {
                      collisionfator = frame[a].collisionFactor(sensor[c].startPos(),sensor[c].endPos());
                  //    qDebug("a: %i d: %i b: %i c: %i %.8f",a,d,b,c,collisionfator);
                      __collisionfactor.push_back(collisionfator);
                  }
                  for(int c=0;c<__collisionfactor.size();c++)
                  {
                      __collisionfactor[c] = roboter[d].beamLength(b,c)*__collisionfactor[c];
                      if(__collisionfactor[c] < __roboterBeamCollisionFactor[d][b][c])
                      {
                         __roboterBeamCollisionFactor[d][b][c] = __collisionfactor[c];
                      }
                  }
                  //roboter[d].beamLength(__collisionfactor,b);

              }
            }
          }
        }
        //qDebug("beamLength1_");
       //qDebug("beam: %.8f",__roboterBeamCollisionFactor[0][0][0]);
        for(int a=0; a<roboter.size(); a++)
        {
            roboter[a].beamLength(__roboterBeamCollisionFactor[a]);
        }
        //qDebug("beamLength2_");
        /*if(robotBody.collisionDistance(robotBody2.pos(),robotBody2.size()) <= 1)
        {
          ret = true;
          roboter->hit();
          roboter2->hit();
          roboter->setLastPos();
          roboter2->setLastPos();
        }*/


      //qDebug("collision ende");
        return ret;
}
/*
float Enviroment::beamLengthRobot(int beamNr)
{
    return roboter->beamLength(beamNr);
}
*/
float Enviroment::getShortest(std::vector<float> data)
{
    float shortest = data[0];
    int counter = 0;
    while(counter < data.size())
    {
        counter = 0;
        for(int a=0; a<data.size(); a++)
        {
            if(shortest > data[a] && data[a]>=0)
            {
                shortest = data[a];
            }
            else
            {
                counter++;
            }
        }
    }
    return shortest;
}
void Enviroment::beamStandardLength(float length)
{
  if(length > 0)
  {
    _beamStandardLength = length;
  }
}
float Enviroment::beamStandardLength()
{
  return _beamStandardLength;
}
void Enviroment::obsticleAmount(unsigned int amount)
{
  _obsticleAmount = amount;
  circle = std::vector<Circle>(_obsticleAmount);
  randomGenObsticle();
}
unsigned int Enviroment::obsticleAmount()
{
  return _obsticleAmount;
}

/*
void Enviroment::turnLeftRobot(float degree)
{
    roboter->turnLeft(degree);
}
void Enviroment::turnRightRobot(float degree)
{
    roboter->turnRight(degree);
}
void Enviroment::moveForwardRobot(float steps)
{
    roboter->forward(steps);
}
void Enviroment::moveBckwardRobot(float steps)
{
    roboter->backward(steps);
}
void Enviroment::rawControlRobot(float left,float right,float stepMultipliyer)
{
   roboter->rawControl(left,right,stepMultipliyer);
}*/





