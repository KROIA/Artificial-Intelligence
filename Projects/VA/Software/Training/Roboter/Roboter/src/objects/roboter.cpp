#include "objects/roboter.h"

Roboter::Roboter(unsigned int beamAmount,float beamAngle)
{
    //body.Circle();
    int anzSensorStr = 2;
    this->beamAmount = beamAmount;
    this->beamAngle = beamAngle;

    beam  = std::vector<std::vector<Line>   >(this->beamAmount,std::vector<Line>(anzSensorStr,Line()));
    pfeil1.width(2);
    pfeil2.width(2);
    pfeil3.width(2);
    __radius    = 20;
    __beamLength= std::vector<std::vector<float>    >(beam.size(),std::vector<float>(beam[0].size(),300));
    __pos       = QPoint(100,300);
    __angle     = 180.0;
    __standardBodyColor = QColor(170,100,17);
    __bodyColor = __standardBodyColor;
    __beamColor = std::vector<QColor>(beam.size(),QColor(0,100,255));
    _turns      = 0;
    __enableBeamDraw = true;
    __beamAngleOffset = 0;

   // qDebug("Roboter();");
    update();
}
Roboter::~Roboter()
{

}
void        Roboter::set(QPoint _pos,float _angle,QColor _bodyColor,QColor _beamColor,unsigned int _radius,float _beamLength)
{
    __pos = _pos;
    __lastPos = __pos;
   // qDebug("set();");
    __angle = _angle;
    __bodyColor = _bodyColor;
    __beamColor = std::vector<QColor>(beam.size(),_beamColor);
    __radius = _radius;
    __beamLength= std::vector<std::vector<float>    >(beam.size(),std::vector<float>(beam[0].size(),_beamLength));
    update();
}
QPoint      Roboter::pos()
{
    return __pos;
}
QPointF     Roboter::posF()
{
    return __fPos;
}
void        Roboter::pos(QPoint _pos)
{
    __lastPos = __pos;
    __pos = _pos;
    //qDebug("pos(QPoint _pos)");
    __fPos.setX((float)__pos.x());
    __fPos.setY((float)__pos.y());

    update();
}
float       Roboter::angle()
{
    return __angle;
}
void        Roboter::angle(float _angle)
{
  if(_angle>=360 || _angle<0)
  {
    _turns++;
  }
  __angle = absoluteAngle(_angle);
  update();
}
void        Roboter::turnRight(float _angle)
{
    /*if(_angle <= 0)
    {
        return;
    }
    if(_angle>=360)
    {
        _angle = 0;
    }
    __angle += _angle;
    update();*/
    angle(__angle+_angle);
}
void        Roboter::turnLeft(float _angle)
{
    /*if(_angle <= 0)
    {
        return;
    }
    if(_angle>=360)
    {
        _angle = 0;
    }
    __angle -= _angle;
    update();*/
    angle(__angle-_angle);
}
void        Roboter::backward(float steps)
{

    if(steps <= 0 )
    {
        return;
    }
    __lastPos = __pos;
    __lastFPos = __fPos;

    __fPos.setX(__fPos.x() - sin(-__angle*_pi/180)*steps);
    __fPos.setY(__fPos.y() - cos(-__angle*_pi/180)*steps);
    __pos.setX((int)__fPos.x());
    __pos.setY((int)__fPos.y());
    update();
}
void        Roboter::forward(float steps)
{
    if(steps <= 0 )
    {
        return;
    }
    __lastPos = __pos;
    __lastFPos = __fPos;

    __fPos.setX(__fPos.x() + sin(-__angle*_pi/180)*steps);
    __fPos.setY(__fPos.y() + cos(-__angle*_pi/180)*steps);
    __pos.setX((int)__fPos.x());
    __pos.setY((int)__fPos.y());
    update();
}
void        Roboter::rawControl(float left,float right,float stepMultipliyer)
{
 if(left    <   -1){left    = -1;}
 if(left    >    1){left    =  1;}
 if(right   <   -1){right   = -1;}
 if(right   >    1){right   =  1;}

 left*=stepMultipliyer;
 right*=stepMultipliyer;

 if(left == right)  //gerade aus oder gerade zurück
 {
     if(left<0)
     {
         backward(left*(-1));
     }
     if(left>0)
     {
         forward(left);
     }
 }
 else
 {
     //qDebug("------------------------------------------");
     QPointF R; //rotationPoint
     double r; //radius to S1
     double S1 = (double)left*(-1);
     double S2 = (double)right*(-1);
     double S  = (double)__radius*(double)2;

     double alpha;
    // qDebug("S1: %lf S2: %lf S: %lf",S1,S2,S);

     alpha  = ((S2-S1)*180)/(S*_pi);
     r      = (180*S1)/(_pi*alpha);
    // qDebug("r: %lf = (360* %lf )/(2* %.8f * %lf )",r,S1,_pi,alpha);


     R      = QPointF(((double)__fPos.x()+(S/2)+r),(double)__fPos.y());
     if(__angle != 0)
     {
         S = cos(__angle*_pi/180)*S/2;
    //     qDebug("S: %lf",S);
     }
     __lastPos = __pos;
     __lastFPos= __fPos;
     R = matrix::rotate(R,__fPos,__angle);
     /*QPointF test(10,10);

     for(int a=0; a<360; a++)
     {
         test = matrix::rotate(test,QPointF(0,0),1);
         qDebug("test: X: %.3f Y: %.3f",test.x(),test.y());
     }*/


     __fPos = matrix::rotate(__fPos,R,alpha);
    // qDebug("alpha: %lf r: %lf Rx: %.3f Ry: %.3f pos1X: %.3f pos1Y: %.3f pos2X: %.3f pos2Y: %.3f",alpha,r,R.x(),R.y(),__lastFPos.x(),__lastFPos.y(),__fPos.x(),__fPos.y());
     __pos.setX(__fPos.x());
     __pos.setY(__fPos.y());
     angle(__angle+alpha);
    // qDebug("------------------------------------------");
     //update();
 }

}
QColor      Roboter::bodyColor()
{
    return __bodyColor;
}
void        Roboter::bodyColor(QColor _bodyColor)
{
    __bodyColor = _bodyColor;
    update();
}
QColor Roboter::standardBodyColor()
{
  return __standardBodyColor;
}
void Roboter::standardBodyColor(QColor color)
{
  __standardBodyColor = color;
}
unsigned int   Roboter::beamWidth()
{
  return beam[0][0].width();
}
void  Roboter::beamWidth(unsigned int width)
{
  if(width > 100)
  {
    width = 100;
  }
  for(int a=0; a<beam.size(); a++)
  {
    for(int b=0; b<beam[0].size(); b++)
    {
      beam[a][b].width(width);
     // qDebug("set width: %i",width);
    }
  }
  update();
}
QColor      Roboter::beamColor(int beamNr)
{
    if(beamNr<0){beamNr=0;}
    if(beamNr>__beamColor.size()-1){beamNr = __beamColor.size()-1;}
    return __beamColor[beamNr];
}
std::vector<QColor> Roboter::beamColor()
{
    return __beamColor;
}
void        Roboter::beamColor(QColor _beamColor)
{
    __beamColor = std::vector<QColor>(__beamColor.size(),_beamColor);
    update();
}
void        Roboter::beamColor(QColor _beamColor,int beamNr)
{
    if(beamNr<0){beamNr=0;}
    if(beamNr>__beamColor.size()-1){beamNr = __beamColor.size()-1;}
    __beamColor[beamNr]=_beamColor;
    update();
}
void        Roboter::beamColor(std::vector<QColor> _beamColor)
{
    if(__beamColor.size()==_beamColor.size())
    {
        __beamColor = _beamColor;
        update();
    }
}
unsigned int Roboter::radius()
{
    return __radius;
}
void        Roboter::radius(unsigned int _radius)
{
    __radius = _radius;
    update();
}
float       Roboter::beamLength(int beamNr)
{
    if(beamNr<0){beamNr=0;}
    if(beamNr>__beamLength.size()-1){beamNr = __beamLength.size()-1;}

    float shortest = __beamLength[beamNr][0];

    for(int a=0; a<__beamLength[beamNr].size(); a++)
    {
      if(__beamLength[beamNr][a] < shortest)
      {
        shortest = __beamLength[beamNr][a];
      }
    }


    return shortest;
}
float       Roboter::beamLength(int beamNr1,int beamNr2)
{
    if(beamNr1<0){beamNr1=0;}
    if(beamNr1>__beamLength.size()-1){beamNr1 = __beamLength.size()-1;}
    if(beamNr2<0){beamNr2=0;}
    if(beamNr2>__beamLength[0].size()-1){beamNr1 = __beamLength[0].size()-1;}
    return __beamLength[beamNr1][beamNr2];
}
std::vector<float> Roboter::beamLength()
{
    std::vector<float>  ret;
    float shortest;
    for(int a=0; a<__beamLength.size(); a++)
    {
      shortest = __beamLength[a][0];
      for(int b=0; b<__beamLength[a].size(); b++)
      {
        if(__beamLength[a][b] < shortest)
        {
          shortest = __beamLength[a][b];
        }
      }
        ret.push_back(shortest);
    }






    return ret;
}
void        Roboter::beamLength(float _beamLength)
{
    __beamLength = std::vector<std::vector<float>   >(__beamLength.size(),std::vector<float>(__beamLength[0].size(),_beamLength));
    update();
}
void        Roboter::beamLength(float _beamLength,int beamNr)
{
    if(beamNr<0){beamNr=0;}
    if(beamNr>__beamLength.size()-1){beamNr = __beamLength.size()-1;}
    __beamLength[beamNr] = std::vector<float>(__beamLength[beamNr].size(),_beamLength);
    update();
}
void        Roboter::beamLength(std::vector<float> _beamLength)
{
    if(__beamLength[0].size()==_beamLength.size())
    {
        __beamLength = std::vector<std::vector<float>   >(__beamLength.size(),_beamLength);
        update();
    }
}
void        Roboter::beamLength(std::vector<float> _beamLength,int beamNr)
{
    if(beamNr<0){beamNr=0;}
    if(beamNr>__beamLength.size()-1){beamNr = __beamLength.size()-1;}
  //  qDebug("x");
    if(__beamLength[beamNr].size()==_beamLength.size())
    {
  //    qDebug("y");
        __beamLength[beamNr] = _beamLength;
        //qDebug("update1");
        update();
        //qDebug("update2");
    }
}
void        Roboter::beamLength(std::vector<std::vector<float>  > _beamLength)
{
    if(__beamLength.size()==_beamLength.size() && __beamLength[0].size()==_beamLength[0].size())
    {
        __beamLength = _beamLength;
        update();
    }
}
void        Roboter::draw(QPainter *painter)
{
    draw(painter,QPoint(0,0));
}
void        Roboter::draw(QPainter *painter,QPoint drawPos)
{

    if(__enableBeamDraw)
    {
      for(int a=0; a<beam.size();a++)
      {
          for(int b=0; b<beam[a].size();b++)
          {
              beam[a][b].draw(painter,drawPos);
          }
         // beam[a][beam[a].size()/2].draw(painter,drawPos);
      }
    }

    body.draw(painter,drawPos);
    pfeil1.draw(painter,drawPos);
    pfeil2.draw(painter,drawPos);
    pfeil3.draw(painter,drawPos);
}
void        Roboter::enableBeamDraw()
{
  __enableBeamDraw = true;
}
void        Roboter::disableBeamDraw()
{
  __enableBeamDraw = false;
}
void        Roboter::setBeamPos()
{

    float _angle;
    for(int a=0; a<beam.size(); a++)
    {
        _angle = absoluteAngle((a*360)/this->beamAmount + __beamAngleOffset);
        /*switch(a)
        {
            case 0:
            {
                _angle = absoluteAngle(0 + __beamAngleOffset);
                break;
            }
            case 1:
            {
                _angle = absoluteAngle(360/this->beamAmount + __beamAngleOffset);
                break;
            }
            case 2:
            {
                _angle = absoluteAngle(2*360/this->beamAmount + __beamAngleOffset);
                break;
            }
            case 3:
            {
                _angle = absoluteAngle(180 + __beamAngleOffset);
                break;
            }
            case 4:
            {
                _angle = absoluteAngle(240 + __beamAngleOffset);
                break;
            }
            case 5:
            {
                _angle = absoluteAngle(300 + __beamAngleOffset);
                break;
            }
        }*/
        _angle = _angle-beamAngle/2;//7.5 weil der Sensor ein sichtfeld von 15grad hat
        for(int b=0; b<beam[a].size(); b++)
        {
            beam[a][b].set(QPoint(__pos.x(),__pos.y()+__radius),QPoint(0,1),__beamLength[a][b],beam[a][b].width(),__beamColor[a]);
            beam[a][b].rotate(__pos,__angle+_angle);
            _angle+=(float)beamAngle/(float)(beam[a].size()-1);
        }
    }
}
void        Roboter::update()
{
    if(__hit == true)
    {
        if(__hitBodyColor != body.color())
        body.color(__hitBodyColor);
    }
    else
    {
        if(__bodyColor != body.color())
        body.color(__bodyColor);
    }
    if(__pos != body.pos())
    {
        body.pos(__pos);
    }
    if(__radius != body.size())
    {
       body.size(__radius);
    }
    pfeil1.set(body.pos(),QPoint(0,1),__radius-(__radius/10),2,QColor(0,0,0));
    pfeil1.rotate(pfeil1.startPos(),__angle);

    pfeil2.set(pfeil1.endPos(),QPoint(0,1),__radius/2,2,QColor(0,0,0));
    pfeil3.set(pfeil1.endPos(),QPoint(0,1),__radius/2,2,QColor(0,0,0));

    pfeil2.rotate(pfeil2.startPos(),__angle+130);
    pfeil3.rotate(pfeil3.startPos(),__angle+220);
    setBeamPos();
}
std::vector<Line>        Roboter::collision(int lineNr)
{
    if(lineNr < 0)
    {
        lineNr = 0;
    }
    if(lineNr>beam.size()-1)
    {
        lineNr = beam.size()-1;
    }
    return beam[lineNr];
}
Circle      Roboter::collision()
{
    return body;
}
unsigned int Roboter::beams()
{
    return beam.size();
}
void        Roboter::setLastPos()
{
    __pos = __lastPos;
    //qDebug("setLastPos");
    __fPos = __lastFPos;
    update();
    //qDebug("setLastPos");
}
void        Roboter::hit(QColor col)
{
      __hit = true;
      __hitBodyColor = col;
      update();
}
void        Roboter::unhit()
{
  __hit = false;
  update();
}
int         Roboter::turns()
{
    return _turns;
}
int         Roboter::resetTurns()
{
    _turns = 0;
}
void        Roboter::beamAngleOffset(float offset)
{
  __beamAngleOffset = absoluteAngle(offset);
  update();
}

float       Roboter::beamAngleOffset()
{
  return __beamAngleOffset;
}
float       Roboter::absoluteAngle(float angle)
{
  if(angle>=360 || angle<0)
  {
      float tmp = angle / 360;
      tmp = tmp -(int)tmp;
      if(tmp <0)
      {
          angle = 360+(tmp *360);
      }
      else
      {
          angle = tmp *360;
      }
  }
  return angle;
}
