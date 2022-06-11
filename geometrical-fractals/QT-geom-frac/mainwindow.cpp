#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <math.h>
#include <bits/stdc++.h>
const int l=600;
double nowl=0;

std::vector<std::pair <double, double>> points;

void evolve()
{
    std::vector<std::pair <double, double>> newp;
    for (int i=0; i<points.size()-1; i++)
    {
        newp.push_back(points[i]);
        double x1=points[i+1].first, y1=points[i+1].second;
        double x2=points[i].first, y2=points[i].second;
        double newx1=(x2-x1)/3+x1, newy1=(y2-y1)/3+y1;
        double newx3=(x2-x1)*2/3+x1, newy3=(y2-y1)*2/3+y1;
        newp.push_back(std::make_pair(newx3, newy3));
        double tx=(newx3-newx1);
        double ty=(newy3-newy1);
        double newx2=newx1+(tx/2 - ty*sqrt(3)/2);
        double newy2=newy1+(ty/2 + tx*sqrt(3)/2);
        newp.push_back(std::make_pair(newx2, newy2));
        newp.push_back(std::make_pair(newx1, newy1));
    }
    newp.push_back(points[points.size()-1]);
    double x1=points[0].first, y1=points[0].second;
    double x2=points[points.size()-1].first, y2=points[points.size()-1].second;
    double newx1=(x2-x1)/3+x1, newy1=(y2-y1)/3+y1;
    double newx3=(x2-x1)*2/3+x1, newy3=(y2-y1)*2/3+y1;
    newp.push_back(std::make_pair(newx3, newy3));
    double tx=(newx3-newx1);
    double ty=(newy3-newy1);
    double newx2=newx1+(tx/2 - ty*sqrt(3)/2);
    double newy2=newy1+(ty/2 + tx*sqrt(3)/2);
    newp.push_back(std::make_pair(newx2, newy2));
    newp.push_back(std::make_pair(newx1, newy1));

    points=newp;
}
double angletorad(int k)
{
    return ((double) k)/180 * M_PI;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(dosmt()));
    this->i=0;
    points.push_back(std::make_pair(600,50));
    points.push_back(std::make_pair(900,570));
    points.push_back(std::make_pair(300,570));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::paintEvent(QPaintEvent *e) {

  Q_UNUSED(e);
  QPainter qp(this);
  drawLines(&qp);
}
void MainWindow::drawLines(QPainter *qp) {
    QPen pen2(Qt::black, 2, Qt::SolidLine);
    qp->setPen(pen2);
    for (int j=0; j<points.size()-1; j++)
    {
        qp->drawLine(points[j].first, points[j].second, points[j+1].first, points[j+1].second);
    }
    qp->drawLine(points[points.size()-1].first, points[points.size()-1].second, points[0].first, points[0].second);

}




void MainWindow::dosmt(){
    evolve();
    update();
}


