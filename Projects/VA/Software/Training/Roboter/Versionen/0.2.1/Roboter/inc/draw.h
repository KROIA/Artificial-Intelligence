#ifndef DRAW_H
#define DRAW_H
#include <QApplication>
#include <QMainWindow>
#include <QtGui>
#include <QtCore>



class Draw
{
  public:
    Draw();
    ~Draw();
    void drawCircle(QPainter *painter,QColor color,QSize size,QPoint point,int abstufung);
    void drawLine(QPainter *painter,QColor color,int size,QPoint pointA,QPoint pointB);

  private:

};

#endif // DRAW_H
