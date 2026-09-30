#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsEllipseItem;
class QTimer;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void moveUAV();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene = nullptr;
    QGraphicsEllipseItem *uav = nullptr;
    QTimer *timer = nullptr;

    // Координаты левого верхнего угла дрона (20 × 20).
    // Центр квадратного маршрута совпадает с центром сцены (400, 300).
    static constexpr int routeLeft = 290;
    static constexpr int routeRight = 490;
    static constexpr int routeTop = 190;
    static constexpr int routeBottom = 390;

    int x = routeLeft;
    int y = routeTop;
    int side = 0; // 0 — вправо, 1 — вниз, 2 — влево, 3 — вверх
};

#endif // MAINWINDOW_H
