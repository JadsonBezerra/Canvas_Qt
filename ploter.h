#ifndef PLOTER_H
#define PLOTER_H

#include <QMouseEvent>
#include <QWidget>
#include <string>

class ploter : public QWidget
{
    Q_OBJECT
    bool desenhar;
    int teste,modo,ret,circ;
    QColor backColor;
    std::vector<std::vector <QPoint>> moveu;
    std::vector <std::vector<QPoint>> retangulos;
    std::vector <std::vector<QPoint>> circulos;
public:
    explicit ploter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void setBackColor(QColor _color);

signals:
    int mudaX(int);
    int mudaY(int);

public slots:
    void setModo(int _modo);
    void clear();
};

#endif // PLOTER_H
