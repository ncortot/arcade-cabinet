#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsrectItem>
#include <QTimer>

class SmartMatrix;

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QGraphicsRectItem** pixels;
    QGraphicsScene* scene;
    QTimer refreshTimer;
    SmartMatrix* matrix;

private slots:
    void redrawDisplay();
};

#endif // WIDGET_H
