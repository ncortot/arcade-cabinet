#include <QtDebug>
#include <math.h>
#include "program.h"
#include "display.h"


Program::Program(QObject *parent) :
    QThread(parent)
{
}

SmartMatrix* Program::getMatrix()
{
    return &matrix;
}

void Program::run()
{
    runTime.start();

    displaySetup();
    for (;;) {
        displayLoop();
    }
}
