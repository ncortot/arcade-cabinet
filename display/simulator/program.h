#ifndef PROGRAM_H
#define PROGRAM_H


#include <QThread>
#include <QTime>

#include "SmartMatrix.h"

class Program : public QThread
{
    Q_OBJECT

public:
    explicit Program(QObject *parent = 0);
    SmartMatrix* getMatrix();

protected:
    virtual void run();

private:
    SmartMatrix matrix;
    QTime runTime;
};

#endif // PROGRAM_H
