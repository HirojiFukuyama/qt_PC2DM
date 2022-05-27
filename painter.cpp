#include "painter.h"

painter::painter()
{

}

void Painter::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //设置画笔颜色
    QPen pen(QColor(0,0,127));
    //设置笔宽度
    pen.setWidth(1);
    //给画家拿笔
    painter.setPen(pen);
    //画字体
    painter.drawText(QRect(10,20,200,50),Qt::AlignCenter,"控件上的图案");
    painter.drawRect(QRect(0,0,100,100));
}
