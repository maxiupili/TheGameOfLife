#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QEvent>
#include <QVector2D>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QTime>
#include <QPen>


QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
    void gameoflife();

protected:
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MyWidget *ui;
    int timeID;
    int grids[500][500];
    int neighbors[3] = {0, 1, -1};
    int rows = 500;
    int cols = 500;
    //vector<vector<int> > grid(500, vector<int>(500));
};
#endif // MYWIDGET_H
