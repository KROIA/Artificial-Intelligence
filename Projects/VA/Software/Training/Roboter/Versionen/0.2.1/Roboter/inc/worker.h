#ifndef WORKER_H
#define WORKER_H
#include <QThread>
#include <QApplication>
#include <stdlib.h>


class Worker : public QThread
{
    Q_OBJECT
public:
    void setFunction(std::function<void(int)> func);
    void setParam(unsigned int _param);
    int getParam(){return param;}
    private:

        void run();
        std::function<void(int)> function;
        int param;

       // void setParam(string param);
};
#endif // WORKER_H


/*
void (*disconnectFunc)();
void D::setDisconnectFunc(void (*func)())
{
    disconnectFunc = func;
}
void D::disconnected()
{

    (*disconnectFunc)();
connected = false;
}
*/
