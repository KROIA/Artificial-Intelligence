#include "graph.h"


Graph::Graph(unsigned int sizeX,unsigned int sizeY)
{
  _sizeX = sizeX;
  _sizeY = sizeY;
  lineWidth = 3;
  graphColor = QColor(0,150,150);
 // qDebug("graph xaxis new");
  xAxis.set(QPoint(-5,_sizeY+5),QPoint(1,0),_sizeX,5,QColor(0,0,0));
  //qDebug("graph xaxis new");
  yAxis.set(QPoint(-5,0),QPoint(0,1),_sizeY,5,QColor(0,0,0));
  _scaleX = 5;
  _scaleY = 5;
}
Graph::~Graph()
{

}

void Graph::color(QColor color)
{
  graphColor = color;
}
QColor Graph::color()
{
  return graphColor;
}
void Graph::width(unsigned int width)
{
  lineWidth = width;
}
void Graph::scale(unsigned int scaleX,unsigned int scaleY)
{
  unsigned int oldScaleX = _scaleX;
  unsigned int oldScaleY = _scaleY;
  _scaleX = scaleX;
  _scaleY = scaleY;


  for(int a=0; a<dataLine.size(); a++)
  {
   /* if(a == dataLine.size()-1)
    {
      qDebug("pos1: %i pos2: %i",dataLine[dataLine.size()-1].endPos().x(),_sizeX);
      dataLine[a].startPos(QPoint(MAP(dataLine[a].startPos().x(),0,dataLine[dataLine.size()-1].endPos().x(),0,_sizeX),dataLine[a].startPos().y()));
      dataLine[a].endPos(QPoint(MAP(dataLine[a].endPos().x(),0,dataLine[dataLine.size()-1].endPos().x(),0,_sizeX),dataLine[a].endPos().y()));

      //dataLine[a].startPos(QPoint(MAP(dataLine[a].startPos().x(),0,oldScaleX*dataLine.size(),0,scaleX*dataLine.size()),dataLine[a].startPos().y()));
      //dataLine[a].endPos(QPoint(MAP(dataLine[a].endPos().x(),0,oldScaleX*dataLine.size(),0,scaleX*dataLine.size()),dataLine[a].endPos().y()));
    }
    else*/
    {
      dataLine[a].startPos(QPoint(MAP(dataLine[a].startPos().x(),0,oldScaleX*dataLine.size(),0,scaleX*dataLine.size()),_sizeY-MAP(_sizeY-dataLine[a].startPos().y(),0,oldScaleY,0,_scaleY)));
      dataLine[a].endPos(QPoint(MAP(dataLine[a].endPos().x(),0,oldScaleX*dataLine.size(),0,scaleX*dataLine.size()),_sizeY-MAP(_sizeY-dataLine[a].endPos().y(),0,oldScaleY,0,_scaleY)));
    }

  }
}
unsigned int Graph::width()
{
  return lineWidth;
}
void Graph::pobBack(int pops)
{
  if(dataLine.size() > 0)
  {

    for(int a=dataLine.size()-1; a>0; a--)
    {
      dataLine[a].startPos(QPoint(dataLine[a-1].startPos().x(),dataLine[a].startPos().y()));
      dataLine[a].endPos(QPoint(dataLine[a-1].endPos().x(),dataLine[a].endPos().y()));
    }
//qDebug("graph erase line");
    dataLine.erase(dataLine.begin());
    dataLine.shrink_to_fit();
    dataLine[0].startPos(dataLine[0].endPos());
  }
}
void Graph::push_back(int pos)
{
  //qDebug("graph new line");
  dataLine.push_back(Line());
  if(dataLine.size() <= 1)
  {
    dataLine[dataLine.size()-1].startPos(QPoint(0,_sizeY-MAP(pos,0,_sizeY,0,_scaleY)));
    dataLine[dataLine.size()-1].endPos  (QPoint(0,_sizeY-MAP(pos,0,_sizeY,0,_scaleY)));
  }
  else
  {
    dataLine[dataLine.size()-1].startPos(dataLine[dataLine.size()-2].endPos());
    dataLine[dataLine.size()-1].endPos  (QPoint(dataLine.size()*_scaleX,_sizeY-MAP(pos,0,_sizeY,0,_scaleY)));
  }
  dataLine[dataLine.size()-1].color(graphColor);
  dataLine[dataLine.size()-1].width(lineWidth);
  if(dataLine[dataLine.size()-1].endPos().x() >= _sizeX)
  {
    //scale(-1,0);
    pobBack();
  }
  qDebug("newLine: x: %i y: %i pos %i",dataLine[dataLine.size()-1].endPos().x(),dataLine[dataLine.size()-1].endPos().y(),pos);
}
void Graph::draw(QPainter *painter,QPoint drawPos)
{
  for(int a=0; a<dataLine.size(); a++)
  {
    //qDebug("draw");
    dataLine[a].draw(painter,drawPos);
  }
  xAxis.draw(painter,drawPos);
  yAxis.draw(painter,drawPos);
}
int  Graph::MAP(int input,int von1,int bis1,int von2,int bis2)
{
  if(input == von1)
    {
      return von2;
    }
  int resultat;
  float tmp;
  float VON1 = (float)von1;
  float VON2 = (float)von2;
  float BIS1 = (float)bis1;
  float BIS2 = (float)bis2;

  tmp = (float)input;
 // printf("RES1: %.3f\n",tmp);
 // printf("calc ((%i-%i)*(%")
  tmp = ((BIS2-VON2)*(tmp-VON1)/(BIS1-VON1))+VON2;
  //printf("RES2: %.3f\n",tmp);
  resultat = tmp;
   //printf("RES3: %i\n",resultat);
  return (int)resultat;
}
