#ifndef SOMEPARALLELPROCESS_H
#define SOMEPARALLELPROCESS_H
#include "SimpleThreadClass.h"
#include "QString"
class SomeParallelprocess: public SimpleThread
{
public:
    SomeParallelprocess();
    virtual void configure() override;
    virtual void start() override;
private:
    QString text;
};

#endif // SOMEPARALLELPROCESS_H
