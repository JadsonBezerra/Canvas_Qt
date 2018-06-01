#include "ploter.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <cmath>
#include <vector>

#define  PI 3.1415
ploter::ploter(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    teste=0;
    desenhar=0;
    modo=0;
    ret=0;
    circ=0;
    backColor=Qt::white;
}

void ploter::mousePressEvent(QMouseEvent *event)
{
    desenhar=1;
    //emit mudaX(x);
    //emit mudaY(y);
    int x,y;
    x= event->x();
    y= event->y();
    if(modo==0)
    moveu.push_back(std::vector <QPoint>());
    if(modo==1){
        retangulos.push_back(std::vector <QPoint>());
        retangulos[ret].push_back(QPoint(x,y));
        retangulos[ret].push_back(QPoint(x,y));
    }
    if(modo==2){
        circulos.push_back(std::vector <QPoint>());
        circulos[circ].push_back(QPoint(x,y));
        circulos[circ].push_back(QPoint(x,y));
    }
}

void ploter::mouseMoveEvent(QMouseEvent *event)
{
    int x,y;
    x= event->x();
    y= event->y();
    emit mudaX(x);
    emit mudaY(y);
    if(desenhar){
        if(modo==0){
             moveu[teste].push_back(QPoint (x,y));
        }
        if(modo==1){
            retangulos[ret][1]=QPoint(x,y);
        }
        if(modo==2){
            circulos[circ][1]=QPoint(x,y);
        }
    }
    repaint();
}

void ploter::mouseReleaseEvent(QMouseEvent *event)
{
    int x,y;
    x= event->x();
    y= event->y();
    if(modo==1){
        retangulos[ret][1]=(QPoint(x,y));
        ret++;
    }
    if(modo==2){
        circulos[circ][1]=QPoint(x,y);
        circ++;
    }
    desenhar=0;
    if(modo==0){
    teste++;
    }
    repaint();
}

void ploter::setBackColor(QColor _color)
{
    backColor=_color;
}

void ploter::setModo(int _modo)
{
    modo=_modo;
}

void ploter::clear()
{
        moveu.clear();
        retangulos.clear();
        circulos.clear();
        repaint();
}

void ploter::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    painter.setRenderHint(QPainter::Antialiasing);

    brush.setColor(backColor);
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);

    pen.setColor(QColor(0,0,0));
    pen.setWidth(1);

    painter.setPen(pen);

    painter.drawRect(0,0,width(),height());

    pen.setStyle(Qt::DashLine);

    painter.setPen(pen);


    painter.drawLine(0,height()/2,width(),height()/2);

    painter.drawLine(width()/2,0,width()/2,height());
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    painter.setPen(pen);
    for(unsigned int j=0;j<moveu.size();j++)
    {
        for(unsigned int i=1;i<moveu[j].size();i++){
            painter.drawLine(moveu[j][i].x(),moveu[j][i].y(),moveu[j][i-1].x(),moveu[j][i-1].y());
        }

    }
    brush.setColor(Qt::transparent);
    painter.setBrush(brush);
    for(unsigned int j=0;j<retangulos.size();j++)
    {
            painter.drawRect(
                        retangulos[j][0].x(),retangulos[j][0].y(),
                        retangulos[j][1].x()-retangulos[j][0].x(),retangulos[j][1].y()-retangulos[j][0].y());

    }
    for(unsigned int j=0;j<circulos.size();j++)
    {
            painter.drawArc(circulos[j][0].x(),circulos[j][0].y(),
                    circulos[j][1].x()-circulos[j][0].x(),circulos[j][1].y()-circulos[j][0].y()
                    ,0*16,360*16);

    }

}
