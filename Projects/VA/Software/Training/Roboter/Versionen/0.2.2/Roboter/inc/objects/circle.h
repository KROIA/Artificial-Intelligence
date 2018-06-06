#ifndef CIRCLE
#define CIRCLE
#include "draw.h"

class Circle
{
    public:
        Circle();
        ~Circle();
        void set(QPoint _pos,int _size,QColor _color);
        void size(unsigned int _size);
        unsigned int size();
        void pos(QPoint _pos);
        QPoint pos();
        void color(QColor _color);
        QColor color();
        void draw(QPainter *painter);
        void draw(QPainter *painter,QPoint offset);
        std::vector<QPoint> collision(QPoint pos1,QPoint pos2);//collision to a line
        std::vector<float> collisionFactor(QPoint pos1, QPoint pos2);//collision to a line
        float collisionDistance(QPoint _pos,unsigned int _radius);//to a cricle
        bool collision(QPoint _pos,unsigned int _radius);//to a cricle
private:

        Draw draw_obj;
        QColor __color;
        QPoint __pos;
        QSize __size;
        int radius;
        int farbabstufung;

};

#endif
