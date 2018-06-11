#include "objects/circle.h"

Circle::Circle()
{
    radius = 10;
    __size.setHeight(radius);
    __size.setWidth(radius);
    __color = QColor(0,255,0);
    farbabstufung = 30;
    //draw_obj = new Draw();
}
Circle::~Circle()
{

}
void Circle::set(QPoint _pos,int _size,QColor _color)
{
    pos(_pos);
    size(_size);
    color(_color);
}
void Circle::size(unsigned int _size)
{
    radius = _size;
    __size = QSize(_size*2,_size*2);
}
unsigned int Circle::size()
{
    return radius;
}
void Circle::pos(QPoint _pos)
{
    __pos = _pos;
}
QPoint Circle::pos()
{
    return __pos;
}
void Circle::color(QColor _color)
{
    __color = _color;
}
QColor Circle::color()
{
    return __color;
}
void Circle::draw(QPainter *painter)
{
    draw_obj.drawCircle(painter,__color,__size,__pos,farbabstufung);
}
void Circle::draw(QPainter *painter, QPoint offset)
{
    __pos.setX(__pos.x()+offset.x());
    __pos.setY(__pos.y()+offset.y());
    draw_obj.drawCircle(painter,__color,__size,__pos,farbabstufung);
    __pos.setX(__pos.x()-offset.x());
    __pos.setY(__pos.y()-offset.y());
    //qDebug("circle.draw()");
}
std::vector<QPoint> Circle::collision(QPoint pos1,QPoint pos2)
{
    std::vector<QPoint> results;
    std::vector<float> factors = collisionFactor(pos1,pos2);
    for(int a=0; a<factors.size(); a++)
    {
        results.push_back(QPoint(((int)(factors[a]*(pos2.x()-pos1.x())))+pos1.x()+__pos.x(),((int)(factors[a]*(pos2.y()-pos1.y())))+pos1.y()+__pos.y()));
    }
    return results;
}
std::vector<float> Circle::collisionFactor(QPoint pos1, QPoint pos2)
{
    std::vector<float> res(2,1.0);
    pos1 = QPoint(pos1.x()-__pos.x(),pos1.y()-__pos.y());//Linie um gleich viel versetzt
    pos2 = QPoint(pos2.x()-__pos.x(),pos2.y()-__pos.y());

    //http://www.matheplanet.com/default3.html?call=viewtopic.php?topic=86998&ref=https%3A%2F%2Fwww.google.ch%2F
    double r = (double)radius;
    double r2= r*r;
    //Line
    double a1 = (double)pos1.x();
    double a2 = (double)pos1.y();
    double b1 = (double)pos2.x();
    double b2 = (double)pos2.y();

    double D = r2*((b1-a1)*(b1-a1)+(b2-a2)*(b2-a2))-(a1*(b2-a2)-a2*(b1-a1))*(a1*(b2-a2)-a2*(b1-a1));
    if(D>=0)
    {
        double x = ((-a1*(b1-a1))-(a2*(b2-a2))+sqrt(D));
        double res1 = x/((b1-a1)*(b1-a1)+(b2-a2)*(b2-a2));
        if(res1<1&&res1>0)
        {
            res[0]=res1;
        }
        if(D>0)
        {
            x = ((-a1*(b1-a1))-(a2*(b2-a2))-sqrt(D));
            double res2 = x/((b1-a1)*(b1-a1)+(b2-a2)*(b2-a2));
            if(res2<1&&res2>0)
            {
                res[1]=res2;
            }
        }
    }
    return res;
}
float Circle::collisionDistance(QPoint _pos,unsigned int _radius)
{
    double S; //Strecke
    double _S;//Distanz zwischen Pos1 und Pos2
    double X = (double)__pos.x()-(double)_pos.x();
    double Y = (double)__pos.y()-(double)_pos.y();

    _S = sqrt(X*X + Y*Y);
    S = _S - (double)_radius - (double)radius;
    return (float)S;
}
bool Circle::collision(QPoint _pos,unsigned int _radius)
{
    float S = collisionDistance(_pos,_radius);
    if(S <= 0.01)
    {
        //qDebug("S: %.5f radius1 %i radius2 %i",S,radius,_radius);
        return true;
    }
    return false;
}
