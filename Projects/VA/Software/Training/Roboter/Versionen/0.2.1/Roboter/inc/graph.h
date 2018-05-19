#ifndef GRAPH_H
#define GRAPH_H
#include <QtGui>
#include <QtCore>
#include <vector>
#include <QApplication>
#include "objects/line.h"


class Graph
{
  public:
    Graph(unsigned int sizeX,unsigned int sizeY);
    ~Graph();

    void color(QColor color);
    QColor color();

    void width(unsigned int width);
    unsigned int width();

    void scale(unsigned int scaleX,unsigned int scaleY);

    void pobBack(int pops = 1);
    void push_back(int pos);

    void draw(QPainter *painter,QPoint drawPos);
  private:
    int MAP(int input,int von1,int bis1,int von2,int bis2);
  std::vector<Line> dataLine;
  QColor graphColor;
  Line xAxis;
  Line yAxis;
  unsigned int lineWidth;
  unsigned int _sizeX;
  unsigned int _sizeY;
  unsigned int _scaleX;
  unsigned int _scaleY;
};

#endif // GRAPH_H
