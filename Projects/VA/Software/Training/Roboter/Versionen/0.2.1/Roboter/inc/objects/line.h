#ifndef LINE_H
#define LINE_H
#include "draw.h"
#include "matrix.h"

class Line
{
    public:
        Line();
        ~Line();

        void set(QPoint start,QPoint _angle,float _length,int _width,QColor _color);


        void width(unsigned int _width);
        unsigned int width();

        void startPos(QPoint start);
        QPoint startPos();

        void endPos(QPoint end);
        QPoint endPos();

        void pos(std::vector<QPoint> _pos);
        std::vector<QPoint> pos();

        void angle(QPoint _angle);
        QPoint angle();
        float length();

        void color(QColor _color);
        QColor color();

        void draw(QPainter *painter);
        void draw(QPainter *painter,QPoint offset);

        QPoint collision(QPoint pos1,QPoint pos2);//collision to a line
        float collisionFactor(QPoint pos1,QPoint pos2);//collision to a line
        void rotate(float angle);
        void rotate(QPoint rotPos,float angle);
    private:

        //Draw *draw_obj;
        Draw draw_obj;
        QColor __color;
        std::vector<QPoint> __pos;
        QPoint __angle;
        float __length;
        int __width;

};
#endif // LINE_H
