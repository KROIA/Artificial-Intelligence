#include "objects/line.h"

Line::Line()
{
    __color = QColor(0,0,0);//black
    __width = 5;
    __pos   = std::vector<QPoint>(2);
    __angleDeg = 0;
    set(QPoint(0,0),QPoint(1,1),1,__width,__color);


   // draw_obj = new Draw();
    //qDebug("newPtr: %i",&draw_obj);
}
Line::~Line()
{
  //qDebug("delete ptr: %i",draw_obj);
 // delete draw_obj;
  //qDebug("delete");
}


void Line::set(QPoint start,QPoint _angle,float _length,int _width,QColor _color)
{


    __pos[0]=start;

    __angle = _angle;
    __width = _width;
    __color = _color;
    length(_length);
}
void Line::width(unsigned int _width)
{
    __width = _width;
}
unsigned int Line::width()
{
    return __width;
}
void Line::startPos(QPoint start)
{
    __pos[0] = start;
    __angle  = QPoint(__pos[1].x()-__pos[0].x(),__pos[1].y()-__pos[0].y());
    __length = __length = sqrt((__pos[0].x()-__pos[1].x())*(__pos[0].x()-__pos[1].x())+(__pos[0].y()-__pos[1].y())*(__pos[0].y()-__pos[1].y()));
}
QPoint Line::startPos()
{
    return __pos[0];
}
void Line::endPos(QPoint end)
{
    __pos[1] = end;
    __angle  = QPoint(__pos[1].x()-__pos[0].x(),__pos[1].y()-__pos[0].y());
    __length = __length = sqrt((__pos[0].x()-__pos[1].x())*(__pos[0].x()-__pos[1].x())+(__pos[0].y()-__pos[1].y())*(__pos[0].y()-__pos[1].y()));
}
QPoint Line::endPos()
{
    return __pos[1];
}
void Line::pos(std::vector<QPoint> _pos)
{
    if(_pos.size()==2)
    {
        __pos = _pos;
        __angle  = QPoint(__pos[1].x()-__pos[0].x(),__pos[1].y()-__pos[0].y());
        __length = __length = sqrt((__pos[0].x()-__pos[1].x())*(__pos[0].x()-__pos[1].x())+(__pos[0].y()-__pos[1].y())*(__pos[0].y()-__pos[1].y()));
    }
}
std::vector<QPoint> Line::pos()
{
    return __pos;
}
void Line::angle(QPoint _angle)
{
    __angle = _angle;
    float ratio = __length/sqrt(__angle.x()*__angle.x()+__angle.y()*__angle.y());
    __pos[1]=QPoint(ratio*__angle.x()+__pos[0].x(),ratio*__angle.y()+__pos[0].y());
}
QPoint Line::angle()
{
    return __angle;
}
float Line::length()
{
    return __length;
}
void Line::length(float lenght)
{
    float xEnd;
    float yEnd;
    float ratio; //Seitenverhältnis

    ratio = lenght/sqrt(__angle.x()*__angle.x()+__angle.y()*__angle.y());

    xEnd = ratio*__angle.x()+__pos[0].x();
    yEnd = ratio*__angle.y()+__pos[0].y();
    __pos[1]=QPoint(xEnd,yEnd);
    __length = sqrt((__pos[0].x()-__pos[1].x())*(__pos[0].x()-__pos[1].x())+(__pos[0].y()-__pos[1].y())*(__pos[0].y()-__pos[1].y()));
    //rotate(__angleDeg);
    angle(angle());
}
void Line::color(QColor _color)
{
    __color = _color;
}
QColor Line::color()
{
    return __color;
}
void Line::draw(QPainter *painter)
{
    draw_obj.drawLine(painter,__color,__width,__pos[0],__pos[1]);
}
void Line::draw(QPainter *painter,QPoint offset)
{
    __pos[0].setX(__pos[0].x()+offset.x());
    __pos[0].setY(__pos[0].y()+offset.y());
    __pos[1].setX(__pos[1].x()+offset.x());
    __pos[1].setY(__pos[1].y()+offset.y());
    draw_obj.drawLine(painter,__color,__width,__pos[0],__pos[1]);
    __pos[0].setX(__pos[0].x()-offset.x());
    __pos[0].setY(__pos[0].y()-offset.y());
    __pos[1].setX(__pos[1].x()-offset.x());
    __pos[1].setY(__pos[1].y()-offset.y());
}
//QPoint Line::collision(QPoint line,QPoint angle)//collision to a line
QPoint Line::collision(QPoint pos1,QPoint pos2)//collision to a line
{
    /*qDebug("collision start");
    qDebug("line1(%i/%i)to(%i/%i)",pos1.x(),pos1.y(),pos2.x(),pos2.y());
    qDebug("line2(%i/%i)to(%i/%i)",__pos[0].x(),__pos[0].y(),__pos[1].x(),__pos[1].y());


    //http://fed.matheplanet.com/mpr.php?stringid=27580045
    double a1 = (double)pos1.x();
    double a2 = (double)pos1.y();
    double b1 = (double)pos2.x();
    double b2 = (double)pos2.y();

    double c1 = (double)__pos[0].x();
    double c2 = (double)__pos[0].y();
    double d1 = (double)__pos[1].x();
    double d2 = (double)__pos[1].y();

    double N = ((b1-a1)*(d2-c2))-((b2-a2)*(d1-c1));
    qDebug("N: %lf",N);
    if(N == 0)
    {
        //no collision
        return point;
    }
    double S = ((c1-a1)*(d2-c2)-(c2-a2)*(d1-c1))/N;
    double T = (a1-c1+S*(b1-a1))/(d1-c1);*/
    float S = collisionFactor(pos1,pos2);
    QPoint point(0,0);
    if(S < 1 && S > 0)
    {
    // qDebug("%lf von strecke : (%i/%i) to (%i/%i)",S,pos1.x(),pos1.y(),pos2.x(),pos2.y());
     point = QPoint(((int)(S*(pos2.x()-pos1.x())))+pos1.x(),((int)(S*(pos2.y()-pos1.y())))+pos1.y());
    }
    else
    {
       // qDebug("%lf",S);
    }
    /*   if(angle.y()/angle.x()==__angle.y()/__angle.x())
    {
        //same angle, no collision
        return point;
    }
    if(angle.y() == 0)
    {
        point.setX();
    }
    double x = (((double)__angle.y()+(double)angle.y())/((double)__angle.x()+(double)angle.x()));
    x = ((double)__pos[0].y()-(double)line.y())/x;
    if(x>1000000)
    {
        x=1000000;
    }
    if(x<-1000000)
    {
        x=-1000000;
    }
    point.setX((int)x);
    qDebug("point x: %i",point.x());
    point.setY((__angle.y()/__angle.x()*point.x()+__pos[0].y()));
    qDebug("point y: %i",point.y()a);*/
    return point;
}
float Line::collisionFactor(QPoint pos1,QPoint pos2)
{
    //http://fed.matheplanet.com/mpr.php?stringid=27580045
    double a1 = (double)pos1.x();
    double a2 = (double)pos1.y();
    double b1 = (double)pos2.x();
    double b2 = (double)pos2.y();

    double c1 = (double)__pos[0].x();
    double c2 = (double)__pos[0].y();
    double d1 = (double)__pos[1].x();
    double d2 = (double)__pos[1].y();
    int calcMode =0;
    if((d1-c1) == 0) // Line B |
    {
        calcMode = 1;
        if((b2-a2) == 0)//Line A -
        {
            calcMode = 2;
        }
    }

    double S;//faktor von Angreifer
    double T;//faktor vom angegriffenen vom S
    switch(calcMode)
    {
        case 0:
        {
            double N = ((b1-a1)*(d2-c2))-((b2-a2)*(d1-c1));
            //qDebug("N: %lf",N);
            if(N == 0)
            {
                //no collision
                break;
                qDebug("no break;");
            }
            S = ((c1-a1)*(d2-c2)-(c2-a2)*(d1-c1))/N;
            T = (a1-c1+S*(b1-a1))/(d1-c1);
            if(S < 1 && S > 0 && T < 1 && T > 0)
            {
             //qDebug("%lf von strecke : (%i/%i) to (%i/%i)",S,pos1.x(),pos1.y(),pos2.x(),pos2.y());
             //point = QPoint(((int)(S*(b1-a1)))+pos1.x(),((int)(S*(b2-a2)))+pos1.y());
                return (float)S;
            }
            /*qDebug("calcMode: %i",calcMode);
            qDebug("no Collision factor: S: %lf T: %lf N: %lf",S,T,N);
            qDebug("a1: %lf a2: %lf",a1,a2);
            qDebug("b1: %lf b2: %lf",b1,b2);
            qDebug("c1: %lf c2: %lf",c1,c2);
            qDebug("d1: %lf d2: %lf",d1,d2);
            qDebug("-------------------------");*/
            break;
        }
        case 1:
        {
            double alpha = atan((b2-a2)/(b1-a1));
            //alpha = sqrt(alpha*alpha);
            double c = /*sqrt((b1-a1)*(b1-a1)+(b2-a2)*(b2-a2))*/(b1-a1)/cos(alpha);
            double x = (d1-a1);
           // c = sqrt(c*c);


            S = (x/(cos(alpha)))/c;
            T = ((a2-d2)+(d1-a1)*tan(alpha))/(c2-d2);
/*

            qDebug("calcMode: %i",calcMode);
            qDebug("atan(((%lf-%lf)->%lf/(%lf-%lf)->%lf)",b2,a2,b2-a2,b1,a1,b1-a1);
            qDebug("alpha: %lf",alpha);
            qDebug("S: %lf",S);
            qDebug("T: %lf",T);
            qDebug("a1: %lf a2: %lf",a1,a2);
            qDebug("b1: %lf b2: %lf",b1,b2);
            qDebug("c1: %lf c2: %lf",c1,c2);
            qDebug("d1: %lf d2: %lf",d1,d2);
            qDebug("-------------------------");
*/
            if(S < 1 && S > 0 && T < 1 && T > 0)
            {

                return S;

            }
           // qDebug("no collision");
            break;
        }
        case 2:
        {
            //qDebug("calcMode: %i",calcMode);
            //if(((a2-d2)>=0 && (c2-a2)>=0) && ((d1-a1)>=0 && (c1-a1)>=0))
            {

                S = (d1-a1)/(b1-a1);
                T = (a2-d2)/(c2-d2);
               /* qDebug("a1: %lf a2: %lf",a1,a2);
                qDebug("b1: %lf b2: %lf",b1,b2);
                qDebug("c1: %lf c2: %lf",c1,c2);
                qDebug("d1: %lf d2: %lf",d1,d2);
                qDebug("S: %lf T: %lf",S,T);*/
                if(S < 1 && S > 0 && T < 1 && T > 0)
                {
                    return S;
                }
            }
            break;
        }

    }
    return 1.0;//no collision
}

void Line::rotate(float angle)
{
    this->rotate(__pos[0],angle);
}
void Line::rotate(QPoint rotPos,float angle)
{
    __pos = matrix::rotate(__pos,rotPos,angle);
    __angleDeg = angle;
}

