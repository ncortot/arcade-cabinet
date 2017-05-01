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
    void begin();
    void loop();

protected:
    virtual void run();
    int millis();
    int random(int max);
    void delay(int millis);

private:
    SmartMatrix matrix;
    QTime runTime;
};

#endif // PROGRAM_H
