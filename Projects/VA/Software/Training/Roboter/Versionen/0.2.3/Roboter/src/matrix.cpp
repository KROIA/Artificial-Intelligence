#include "matrix.h"

QPoint matrix::rotate(QPoint point,QPoint rotationPoint,float angle)
{
    return matrix::rotate(std::vector<QPoint>(1,point),rotationPoint,angle)[0];
}
std::vector<QPoint> matrix::rotate(std::vector<QPoint> points ,QPoint rotationPoint,float angle)
{
    double rad = (double)angle*_pi/180;
    double _cos = cos(rad);
    double _sin = sin(rad);

    for(int a=0; a<points.size(); a++)
    {
        QPoint tmpP = QPoint(points[a].x()-rotationPoint.x(),points[a].y()-rotationPoint.y());
        points[a].setX(_cos*tmpP.x()+-_sin*tmpP.y()+rotationPoint.x());
        points[a].setY(_sin*tmpP.x()+_cos*tmpP.y()+rotationPoint.y());
    }
    return points;
}
QPointF matrix::rotate(QPointF point,QPointF rotationPoint,float angle)
{
    return matrix::rotate(std::vector<QPointF>(1,point),rotationPoint,angle)[0];
}
std::vector<QPointF> matrix::rotate(std::vector<QPointF> points ,QPointF rotationPoint,float angle)
{
    double rad = (double)angle*_pi/180;
    double _cos = cos(rad);
    double _sin = sin(rad);

    for(int a=0; a<points.size(); a++)
    {
        QPointF tmpP = QPointF(points[a].x()-rotationPoint.x(),points[a].y()-rotationPoint.y());
        points[a].setX(_cos*tmpP.x()+-_sin*tmpP.y()+rotationPoint.x());
        points[a].setY(_sin*tmpP.x()+_cos*tmpP.y()+rotationPoint.y());
    }
    return points;
}
