#ifndef MATRIX_H
#define MATRIX_H
#include <QtCore>
#define _pi          3.141592653589793238462643383279502884

namespace matrix
{
    QPoint rotate(QPoint point,QPoint rotationPoint,float angle);
    std::vector<QPoint> rotate(std::vector<QPoint> points ,QPoint rotationPoint,float angle);
    QPointF rotate(QPointF point,QPointF rotationPoint,float angle);
    std::vector<QPointF> rotate(std::vector<QPointF> points ,QPointF rotationPoint,float angle);
}

#endif // MATRIX_H
