#include "draw.h"




Draw::Draw()
{

}

Draw::~Draw()
{

}
void Draw::drawCircle(QPainter *painter,QColor color,QSize size,QPoint point,int abstufung)
{
  QBrush brush(color);
  if(color.red() < abstufung)
  {
    color.setRed(abstufung);
  }
  if(color.green() < abstufung)
  {
    color.setGreen(abstufung);
  }
  if(color.blue() < abstufung)
  {
    color.setBlue(abstufung);
  }
  QPen circlePen(QColor(color.red()-abstufung,color.green()-abstufung,color.blue()-abstufung));
  circlePen.setWidth(5);
  QPoint pRec;
  pRec.setX(point.x()-size.width()/2);
  pRec.setY(point.y()-size.height()/2);
  QRect rectangle(pRec,size);
  painter->setBrush(brush);
  painter->setPen(circlePen);
  painter->drawEllipse(rectangle);
}
void Draw::drawLine(QPainter *painter,QColor color,int size,QPoint pointA,QPoint pointB)
{
  QPen linepen(color);
  linepen.setWidth(size);
  painter->setPen(linepen);
  painter->drawLine(pointA,pointB);
}
