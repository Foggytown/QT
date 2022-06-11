#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void mousePressEvent(QMouseEvent*event);
    virtual void mouseReleaseEvent(QMouseEvent*event);
    virtual void mouseMoveEvent(QMouseEvent*event);
    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *qp);
    int xend, yend, selstartx, selstarty, selendx,selendy;
    double xrs,xre,yrs,yre;
    bool fancy, drawrect;

private slots:
    void dosmt();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
