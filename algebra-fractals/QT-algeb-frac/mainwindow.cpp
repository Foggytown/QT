#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <math.h>
#include <QDebug>
#include <bits/stdc++.h>
int step, inf, inft, r,g,b;
double cr,ci;
QColor colours[10];

class complexsnya
{
   double r, i;

public:
   complexsnya();
   complexsnya(double x);
   complexsnya(double x, double y)
   {
       r=x;
       i=y;
   }
   double module() {return sqrt(r*r+i*i);}
   double getr() {return r;}
   double geti() {return i;}
   complexsnya power(int st)
   {
       double sr=r, si=i, savesr;
       for (int j=0; j<st-1; j++)
       {
           savesr=sr;
           sr=sr*r-si*i;
           si=savesr*i+si*r;
       }
       return complexsnya(sr,si);
   }
   complexsnya operator + (complexsnya &c) const
   {
       complexsnya save=complexsnya(0,0);
       save.r=r+c.r;
       save.i=i+c.i;
       return save;
   }
   complexsnya operator + (double &c) const
   {
       complexsnya save;
       save.r=r+c;
       save.i=i;
       return save;
   }
   complexsnya operator * (complexsnya &c) const
      {
         complexsnya save=complexsnya(0,0);
         save.r = r*c.r-i*c.i;
         save.i = r*c.i+i*c.r;
         return save;
      }
};

complexsnya c_comp=complexsnya(0,0);
int domandel(complexsnya a)
{
    int i;
    complexsnya save=a;
    for (i=0; i<inft; i++)
    {
        if (save.module()>=inf)
        {
            return i;
        }
        save=save.power(step)+c_comp;

    }
    return -1;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->xend=940;
    this->yend=940;
    this->selstartx=-1;
    this->selstarty=-1;
    this->selendx=-1;
    this->selendy=-1;
    this->drawrect=0;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(dosmt()));
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
    QPen penb(Qt::black, 1, Qt::SolidLine);
    qp->setPen(penb);
    double dy=((double) (this->yre-this->yrs))/( (double) this->yend);
    double dx=((double) (this->xre-this->xrs) )/( (double) this->xend);
    double xr,yr;
    if (this->fancy)
    {
        colours[0]=QColor(r,0,0);
        colours[1]=QColor(0,g,0);
        colours[2]=QColor(0,0,b);
        colours[3]=QColor(r,g,0);
        colours[4]=QColor(r,0,b);
        colours[5]=QColor(0,g,b);
        colours[6]=QColor(r,g,b);
        colours[7]=QColor(r/2,g,b);
        colours[8]=QColor(r,g/2,b);
        colours[9]=QColor(r,g,b/2);
    }
    for (int xm=0; xm<this->xend; xm++)
    {
        for (int ym=0; ym<this->yend; ym++)
        {
            xr=this->xrs+xm*dx;
            yr=this->yre-ym*dy;
            int ans=domandel(complexsnya(xr,yr));
            if (this->fancy && ans!=-1)
            {
                qp->setPen(colours[(ans*10)/inft]);
            }
            else if (ans==-1)
            {
                qp->setPen(QColor(0,0,0));
            }
            else
            {
                qp->setPen(QColor(r-(r/inft*ans),g-(g/inft*ans),b-(b/inft*ans)));
            }
            qp->drawPoint(xm,ym);
        }
    }
    if (drawrect)
    {
        qp->setPen(QPen(Qt::blue,2, Qt::SolidLine));
        qp->drawLine(this->selstartx, this->selstarty, this->selstartx, this->selendy);
        qp->drawLine(this->selstartx, this->selstarty, this->selendx, this->selstarty);
        qp->drawLine(this->selstartx, this->selendy, this->selendx, this->selendy);
        qp->drawLine(this->selendx, this->selstarty, this->selendx, this->selendy);
    }
}




void MainWindow::dosmt(){
    this->fancy=ui->checkBox->isChecked();
    step=ui->textEdit_1->toPlainText().toInt();
    cr=ui->textEdit_2->toPlainText().toDouble();
    ci=ui->textEdit_12->toPlainText().toDouble();
    inf=ui->textEdit_3->toPlainText().toInt();
    inft=ui->textEdit_4->toPlainText().toInt();
    r=ui->textEdit_5->toPlainText().toInt();
    g=ui->textEdit_6->toPlainText().toInt();
    b=ui->textEdit_7->toPlainText().toInt();
    this->xrs=ui->textEdit_8->toPlainText().toDouble();
    this->xre=ui->textEdit_9->toPlainText().toDouble();
    this->yrs=ui->textEdit_10->toPlainText().toDouble();
    this->yre=ui->textEdit_11->toPlainText().toDouble();
    c_comp=complexsnya(cr,ci);
    update();
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->selstartx=event->x();
    this->selstarty=event->y();
}



void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->selendx=event->x();
    this->selendy=event->y();
    this->drawrect=1;
    update();
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    this->selendx=event->x();
    this->selendy=event->y();
    this->drawrect=0;
    double xrs,yrs,xre,yre;
    double dy=((double) (this->yre-this->yrs))/( (double) this->yend);
    double dx=((double) (this->xre-this->xrs) )/( (double) this->xend);
    qDebug() << this->selstartx << " " << this->selstarty << " " << this->selendx <<  " " <<this->selendy ;
    xrs=this->selstartx*dx+this->xrs;
    xre=this->selendx*dx+this->xrs;
    yrs=this->yre-this->selstarty*dy;
    yre=this->yre-this->selendy*dy;
    this->xrs=std::min(xrs,xre);
    this->xre=std::max(xrs,xre);
    this->yrs=std::min(yrs,yre);
    this->yre=std::max(yrs,yre);
    qDebug() <<   this->xrs << " " << this->xre << " " << this->yrs <<  " " <<this->yre ;
    QString forprint;
    ui->textEdit_8->setText(forprint.setNum(this->xrs));
    ui->textEdit_9->setText(forprint.setNum(this->xre));
    ui->textEdit_10->setText(forprint.setNum(this->yrs));
    ui->textEdit_11->setText(forprint.setNum(this->yre));
    update();
}


