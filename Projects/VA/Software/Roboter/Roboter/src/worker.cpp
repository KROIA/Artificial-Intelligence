#include "worker.h"



void Worker::setFunction(std::function<void(int)> func)
{
    //p_func = func;
    function = func;
}
void Worker::run()
{
    //qDebug("Thread started %i", param);
    //if(p_func != NULL)
    {
     function(param);
    }

   // system (param.c_str());
    //qDebug("Thread stoped %i",param);
}
void Worker::setParam(unsigned int _param)
{
    param = _param;
}
