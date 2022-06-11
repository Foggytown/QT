#include <bits/stdc++.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QString>
#include <QPainterPath>
#include <functional>


typedef std::function<double (double)> smfunk;
typedef std::function<double (double,double)> intfunk;
intfunk funcg;
smfunk fx,dfx;
int x1g,x2g,y1g,y2g;
double dxg,dyg,dming,dmaxg,ag,bg,eps1g,eps2g,aig=0,big=M_PI/2,x0g;

double func1(double x, double y)
{
    return pow(M_E, -cos(y)*0.5*x*x)*sqrt(sin(y));
}

double dfunc1(double x, double y)
{
    return (x*-1*cos(y)/2-x*cos(y)/2)*func1(x,y);
}

double integ(intfunk func, double x)
{
    double a=aig, b=big, eps=eps1g;
    int n=20;
    double h=(b-a)/20;
    double chet, nechet, ends, now, save, ans=1000000000000;
    for (int i=1; i<n; i++)
    {
        now=func(x,a+h* (double) i);
        if (i%2==1)
        {
            nechet+=now;
        }
        else
        {
            chet+=now;
        }
    }
    ends=func(x,a)+func(x,b);
    save=2*((b-a)/(6 * (double) n)) * (ends+4*nechet+2*chet);
    while (abs(ans-save)>eps)
    {
        ans=save;
        chet+=nechet;
        h=h/2;
        n*=2;
        nechet=0;
        for (int i=1; i<n; i+=2)
        {
            nechet+=func(x, a+h* (double) i);
        }
        save=2*((b-a)/(6 * (double) n)) * (ends+4*nechet+2*chet);
    }
    return ans;
}

double fxl(double x)
{
    return -1+x*x*integ(func1,x);
}

double dfxl(double x)
{
    return 2*x*integ(func1,x)+x*x*integ(dfunc1,x);
}


void graph(double a, double b, int x1, int x2, int y1, int y2)
{
    smfunk func=fx;
    double xr, yr;
    int xm,ym;
    double dx=(b-a)/(x2-x1);
    double dmin=func(a), dmax=func(a);
    for (xm=x1; xm<=x2; xm++)
    {
        xr=a+(xm-x1)*dx;
        if (func(xr)<dmin)
        {
            dmin=func(xr);
        }
        if (func(xr)>dmax)
        {
            dmax=func(xr);
        }
    }
    double dy=(dmax-dmin)/(y2-y1);
    dxg=dx;
    dyg=dy;
    dming=dmin;
    dmaxg=dmax;
}




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pix=QPixmap(this->size().width(), this->size().height());
    QPainter qp;
    QPen pen(Qt::darkGreen, 4, Qt::SolidLine);
    qp.begin(&pix);
    qp.setPen(pen);
    QPolygon poly;
        poly << QPoint(0,0);
        poly << QPoint(0,this->size().height());
        poly << QPoint(this->size().width(), this->size().height());
        poly << QPoint(this->size().width(),0);
    QPainterPath path;
    path.addPolygon(poly);
    QBrush brush;
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    qp.fillPath(path,brush);
    qp.end();
    //FUNC HERE;
    funcg=func1;
    fx=fxl;
    dfx=dfxl;
    connect(ui->pushButton, SIGNAL (released()), this, SLOT (handleButton()));
    connect(ui->pushButton_2, SIGNAL (released()), this, SLOT (handleButton2()));
}
void MainWindow::handleButton()
{
    QString s1,s2,s3;
    QStringList l1,l2,l3;
    s1=ui->plainTextEdit->toPlainText();
    s2=ui->plainTextEdit_2->toPlainText();
    s3=ui->plainTextEdit_3->toPlainText();
    l1=s1.split(' ');
    l2=s2.split(' ');
    l3=s3.split(' ');
    //aig=l1[0].toDouble();
    //big=l1[1].toDouble();
    eps1g=l1[0].toDouble();
    x1g=l2[0].toInt();
    x2g=l2[1].toInt();
    y1g=l2[2].toInt();
    y2g=l2[3].toInt();
    ag=l3[0].toDouble();
    bg=l3[1].toDouble();
    graph(ag,bg,x1g,x2g,y1g,y2g);
    drawLines();
    repaint();
}

void MainWindow::handleButton2()
{
    QString s1,s2,s3;
    QStringList l1,l2,l3;
    s1=ui->plainTextEdit->toPlainText();
    s2=ui->plainTextEdit_2->toPlainText();
    s3=ui->plainTextEdit_3->toPlainText();
    l1=s1.split(' ');
    l2=s2.split(' ');
    l3=s3.split(' ');
    //aig=l1[0].toDouble();
    //big=l1[1].toDouble();
    eps1g=l1[0].toDouble();
    x1g=l2[0].toInt();
    x2g=l2[1].toInt();
    y1g=l2[2].toInt();
    y2g=l2[3].toInt();
    ag=l3[0].toDouble();
    bg=l3[1].toDouble();
    eps2g=l3[2].toDouble();
    graph(ag,bg,x1g,x2g,y1g,y2g);
    if (l3.size()>3)
    {
        x0g=l3[3].toDouble();
    }
    else
    {
        x0g=0.75;
    }
    drawLines_2();
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *e) {

  Q_UNUSED(e);

  QPainter wPainter;
  wPainter.begin( this );
  wPainter.drawPixmap( 0 , 0 , pix );
  wPainter.end();
}

void MainWindow::drawLines() {
    QPainter qp;
    qp.begin(&pix);
    int x1,x2,xm,ym,y1,y2;
    double xr,yr,dmin,dmax,a,b,dx,dy;
    smfunk func;
    x1=x1g;
    x2=x2g;
    y1=y1g;
    y2=y2g;
    dx=dxg;
    dy=dyg;
    dmin=dming;
    dmax=dmaxg;
    a=ag;
    b=bg;
    func=fx;
    if (a==0 && b==0 && x1==0 && y1==0)
    {
        return;
    }

    QPen pen(Qt::darkGreen, 4, Qt::SolidLine);
    qp.setPen(pen);
    int ot=60;
    QPolygon poly;
        poly << QPoint(x1-ot,y1-ot);
        poly << QPoint(x1-ot,y2+ot);
        poly << QPoint(x2+ot, y2+ot);
        poly << QPoint(x2+ot,y1-ot);
    QPainterPath path;
    path.addPolygon(poly);
    QBrush brush;
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    qp.fillPath(path,brush);
    qp.drawLine(x1,y1,x1,y2);
    qp.drawLine(x1,y1,x2,y1);
    qp.drawLine(x2,y1,x2,y2);
    qp.drawLine(x1,y2,x2,y2);
    int ys=(y1+y2)/2;
    int xs=(x1+x2)/2;
    QString s;
    QPen pen2 (Qt::black, 4, Qt::SolidLine);
    qp.setPen(pen2);
    //a=(double) ((int) (a*1000))/1000;
    s=QString::fromStdString(std::to_string(a));
    qp.drawText(x1+15, ys, s);
    //b=(double) ((int) (b*1000))/1000;
    s=QString::fromStdString(std::to_string(b));
    qp.drawText(x2+30, ys, s);
    s=QString::fromStdString(std::to_string(dmin));
    qp.drawText(xs, y2+30, s);
    s=QString::fromStdString(std::to_string(dmax));
    qp.drawText(xs, y1-10, s);
    if (a<0 && b>0)
    {
        xm=(int) (-a)/dx+x1;
        QPen pen(Qt::darkGreen, 2, Qt::DashLine);
        qp.setPen(pen);
        qp.drawLine(xm, y1, xm,y2);
        s='0';
        QPen pen2 (Qt::black, 4, Qt::SolidLine);
        qp.setPen(pen2);
        qp.drawText(xm+4,y2-4, s);
    }
    if (dmin<0 && dmax>0)
    {
        ym=(int) (y2-(0-dmin)/dy);
        QPen pen(Qt::darkGreen, 2, Qt::DashLine);
        qp.setPen(pen);
        qp.drawLine(x1, ym, x2,ym);
        s="0    ";
        QPen pen2 (Qt::black, 4, Qt::SolidLine);
        qp.setPen(pen2);
        qp.drawText(x1+4,ym-4, s);
    }

    QPen pen1(Qt::black, 1, Qt::SolidLine);
    qp.setPen(pen1);
    double save=0;
    for (int xm=x1; xm<x2; xm++)
    {
        xr=a+(xm-x1)*dx;
        yr=func(xr);
        ym=(int) (y2-(yr-dmin)/dy);
        if (save!=0)
        {
            qp.drawLine(xm-1, save, xm, ym);
        }
        else
        {
            qp.drawPoint(xm, ym);
        }
        save=ym;
    }
    qp.end();
}




void MainWindow::drawLines_2() {
    drawLines();
    QPainter qp;
    qp.begin(&pix);
    QPen pen(Qt::darkBlue, 2, Qt::DashLine);
    qp.setPen(pen);
    int x1,x2,xm,ym,y1,y2;
    double xr,yr,dmin,dmax,a,b,dx,dy;
    x1=x1g;
    x2=x2g;
    y1=y1g;
    y2=y2g;
    dx=dxg;
    dy=dyg;
    dmin=dming;
    dmax=dmaxg;
    a=ag;
    b=bg;
    double eps=eps2g;
    smfunk fx1=fx, dfx1=dfx;
    int savex,savey;
    double x0=x0g;
    double x_1=x0-fx1(x0)/dfx1(x0);
    if (x_1!=INFINITY)
    {
        int y0=(int) (y2-(0-dmin)/dy);
        xr=x0;
        xm=(int) ((xr-a)/dx) +x1;
        yr=fx1(xr);
        ym=(int) (y2-(yr-dmin)/dy);
        savex=xm;
        savey=ym;
        xr=x_1;
        xm=(int) ((xr-a)/dx) +x1;
        yr=fx1(xr);
        ym=(int) (y2-(yr-dmin)/dy);
        qp.drawLine(savex, y0, savex, savey);
        qp.drawLine(savex, savey, xm,y0);
        int cnt=0;
        while (abs(x_1-x0)>eps && cnt<20 && x_1!=INFINITY)
        {
            cnt++;
            x0=x_1;
            savex=xm;
            savey=ym;
            x_1=x0-fx1(x0)/dfx1(x0);
            xr=x_1;
            xm=(int) ((xr-a)/dx) +x1;
            yr=fx1(xr);
            ym=(int) (y2-(yr-dmin)/dy);
            qp.drawLine(savex, y0, savex, savey);
            qp.drawLine(savex, savey, xm,y0);
        }
        ui->label->setText(QString::number(x_1, 'f', 20));
        ui->label_2->setText(QString::number(fx1(x_1), 'f', 20));
        return ;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
