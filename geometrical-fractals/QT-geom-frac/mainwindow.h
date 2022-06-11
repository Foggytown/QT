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
    int i, angle;
    double posx, posy;

protected:
    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *qp);
    void rotate(int k);

private slots:
    void dosmt();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
