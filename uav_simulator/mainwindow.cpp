#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QBrush>
#include <QColor>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QPen>
#include <QPushButton>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);
    ui->graphicsView->setScene(scene);

    // Эллипс занимает 20 × 20 пикселей относительно своей позиции.
    uav = scene->addEllipse(0, 0, 20, 20,
                            QPen(Qt::black), QBrush(Qt::red));
    uav->setPos(x, y);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::moveUAV);

    connect(ui->btnStart, &QPushButton::clicked, this, [this]() {
        timer->start(20);
        ui->labelStatus->setText("Движение");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveUAV()
{
    // За каждый вызов таймера перемещаемся на 2 пикселя.
    switch (side) {
    case 0:
        x += 2;
        if (x >= routeRight) {
            x = routeRight;
            side = 1;
        }
        break;
    case 1:
        y += 2;
        if (y >= routeBottom) {
            y = routeBottom;
            side = 2;
        }
        break;
    case 2:
        x -= 2;
        if (x <= routeLeft) {
            x = routeLeft;
            side = 3;
        }
        break;
    case 3:
        y -= 2;
        if (y <= routeTop) {
            y = routeTop;
            side = 0;
        }
        break;
    }

    uav->setPos(x, y);

    // Задание 3: цвет зависит от координаты Y.
    if (y < 300) {
        uav->setBrush(QColor(Qt::blue));
    } else {
        uav->setBrush(QColor(Qt::red));
    }

    ui->labelStatus->setText(
        QString("Движение: X=%1, Y=%2").arg(x).arg(y));
}
