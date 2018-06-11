#ifndef ROBOTER_H
#define ROBOTER_H
#include "objects/circle.h"
#include "objects/line.h"
#define M_PIl          3.141592653589793238462643383279502884L
class Roboter
{
    public:
    Roboter(unsigned int beamAmount,float beamAngle);
    ~Roboter();

    void set(QPoint _pos,float _angle,QColor _bodyColor,QColor _beamColor,unsigned int _radius,float _beamLength);

    QPoint pos();

    QPointF posF();
    void pos(QPoint _pos);

    float angle();
    void angle(float _angle);
    void turnRight(float _angle = 1.0);
    void turnLeft(float _angle = 1.0);
    void backward(float steps = 1);
    void forward(float steps = 1);
    void rawControl(float left,float right,float stepMultipliyer);

    QColor bodyColor();
    void bodyColor(QColor _bodyColor);
    QColor standardBodyColor();
    void standardBodyColor(QColor color);

    unsigned int   beamWidth();
    void  beamWidth(unsigned int width);

    QColor beamColor(int beamNr);
    std::vector<QColor> beamColor();
    void beamColor(QColor _beamColor);
    void beamColor(QColor _beamColor,int beamNr);
    void beamColor(std::vector<QColor> _beamColor);

    unsigned int radius();
    void radius(unsigned int _radius);

    float beamLength(int beamNr);
    float beamLength(int beamNr1,int beamNr2);
    std::vector<float> beamLength();
    void beamLength(float _beamLength);
    void beamLength(float _beamLength,int beamNr);
    void beamLength(std::vector<float> _beamLength);
    void beamLength(std::vector<float> _beamLength,int beamNr);
    void beamLength(std::vector<std::vector<float>  > _beamLength);

    void draw(QPainter *painter);
    void draw(QPainter *painter,QPoint drawPos);
    void enableBeamDraw();
    void disableBeamDraw();

    std::vector<Line> collision(int lineNr);
    Circle collision();
    unsigned int beams();
    void setLastPos();
    void hit(QColor col = QColor(255,0,0));
    void unhit();
    int turns();
    int resetTurns();
    void beamAngleOffset(float offset);
    float beamAngleOffset();
    float absoluteAngle(float angle);

void update();
void setBeamPos();

    private:


    Circle body;
    Line pfeil1;
    Line pfeil2;
    Line pfeil3;
    //std::vector<Line>   beam;
    unsigned int beamAmount;
    float beamAngle;
    std::vector<std::vector<Line>   >   beam;
    std::vector<QColor> __beamColor;
    std::vector<std::vector<float>  >  __beamLength;
    unsigned int    __radius;

    QPoint          __pos;
    QPoint          __lastPos;
    QPointF         __fPos;
    QPointF         __lastFPos;
    /*float           __lastFPosX;
    float           __lastFPosY;
    float           __fPosX;
    float           __fPosY;*/
    float           __angle;
    QColor          __bodyColor;
    QColor          __standardBodyColor;
    bool            __hit;
    QColor          __hitBodyColor;

    bool            __enableBeamDraw;
    int             _turns;
    float           __beamAngleOffset;

};

#endif // ROBOTER_H
