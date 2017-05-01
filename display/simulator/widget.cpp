#include <QtDebug>
#include "ui_widget.h"

#include "widget.h"

#include "program.h"


#include "SmartMatrix.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    const int pixelSize = 4;

    pixels = new QGraphicsRectItem*[MATRIX_HEIGHT * MATRIX_WIDTH];

    scene = new QGraphicsScene();
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int j = 0; j < MATRIX_WIDTH; j++) {
            pixels[i * MATRIX_WIDTH + j] = scene->addRect(
                j * pixelSize, i * pixelSize,
                pixelSize,
                pixelSize,
                QPen(Qt::NoPen),
                QBrush(Qt::black));
        }
    }
    ui->view->setScene(scene);

    Program* program = new Program();
    matrix = program->getMatrix();
    connect(&refreshTimer, SIGNAL(timeout()), this, SLOT(redrawDisplay()));
    program->start();
    refreshTimer.start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::redrawDisplay()
{
    matrix->updateForRead();

    rgb24* buffer = matrix->frontBuffer();
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int j = 0; j < MATRIX_WIDTH; j++) {
            rgb24 pixel;
            if (!matrix->getForegroundPixel(j, i, &pixel)) {
                pixel = buffer[i * MATRIX_WIDTH + j];
            }
            QColor color(pixel.red, pixel.green, pixel.blue);
            pixels[i * MATRIX_WIDTH + j]->setBrush(QBrush(color));
        }
    }
}
