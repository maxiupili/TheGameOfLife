#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    int n = qrand() % 2;
    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 500; ++j) {
            time= QTime::currentTime();
            qsrand(time.msec()+time.second()*1000);
            n = qrand() % 2;
            grids[i][j] = n;
        }
    }
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timeID) {
        gameoflife();
        update();
    }

}

void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter p;
    p.begin(this);

    QPen pen;
    pen.setColor(Qt::blue);
    p.setPen(pen);

    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 500; ++j) {
            if (grids[i][j] == 1) {
                p.drawPoint(i + 150, j + 50);
            }
        }
    }

    p.end();

}
void MyWidget::on_pushButton_clicked()
{
    timeID = this->startTimer(1000);
}

void MyWidget::on_pushButton_2_clicked()
{
    this->killTimer(timeID);
}

void MyWidget::gameoflife()
{
    // 遍历面板每一个格子里的细胞
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {

            // 对于每一个细胞统计其八个相邻位置里的活细胞数量
            int liveNeighbors = 0;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {

                    if (!(neighbors[i] == 0 && neighbors[j] == 0)) {
                        // 相邻位置的坐标
                        int r = (row + neighbors[i]);
                        int c = (col + neighbors[j]);

                        // 查看相邻的细胞是否是活细胞
                        if ((r < rows && r >= 0) && (c < cols && c >= 0) && (abs(grids[r][c]) == 1)) {
                            liveNeighbors += 1;
                        }
                    }
                }
            }

            // 规则 1 或规则 3
            if ((grids[row][col] == 1) && (liveNeighbors < 2 || liveNeighbors > 3)) {
                // -1 代表这个细胞过去是活的现在死了
                grids[row][col] = -1;
            }
            // 规则 4
            if (grids[row][col] == 0 && liveNeighbors == 3) {
                // 2 代表这个细胞过去是死的现在活了
                grids[row][col] = 2;
            }
        }
    }

    // 遍历 board 得到一次更新后的状态
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (grids[row][col] > 0) {
                grids[row][col] = 1;
            } else {
                grids[row][col] = 0;
            }
        }
    }

}
