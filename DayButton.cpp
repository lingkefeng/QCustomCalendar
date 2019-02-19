#include "DayButton.h"
#include <QPainter>
#include <QMouseEvent>

DayButton::DayButton(QWidget *parent)
    : QPushButton(parent)
    , isHover(false)
    , hoverTextColor(Qt::white)
    , hoverBkBrush(QBrush(QColor(Qt::blue)))
{
    setFixedSize(25,25);
    setTextColor(QColor(0,0,0));

//    this->setStyleSheet("color:white");


    QFont font = this->font();
//    font.setBold(true);
    font.setFamily("微软雅黑");
    setFont(font);
}

void DayButton::setTextColor(const QColor &color)
{
    if(color.isValid())
    {
        textColor = color;
        update();
    }
}

void DayButton::setHoverTextColor(const QColor &color)
{
    if(!color.isValid())
        return;

    hoverTextColor = color;
}

void DayButton::setHoverBkBrush(const QBrush &brush)
{
    hoverBkBrush = brush;
}

void DayButton::enterEvent(QEvent *event)
{
    isHover = true;
    update();

    QWidget::enterEvent(event);
}

void DayButton::leaveEvent(QEvent *event)
{
    isHover = false;
    update();

    QWidget::leaveEvent(event);
}

void DayButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    QRect r = rect();
//    r.adjust(1,1,-1,-1);

    //画背景
    if(isHover==true)
    {
        painter.save();
        painter.setPen(Qt::NoPen);
        painter.setBrush(hoverBkBrush);
        painter.drawEllipse(r);
        painter.restore();

        painter.save();
        painter.setPen(hoverTextColor);
        painter.drawText(r,Qt::AlignCenter,this->text());
        painter.restore();
    }
    else
    {
        //画文字
        painter.save();
        painter.setPen(textColor);
        painter.drawText(r,Qt::AlignCenter,this->text());
        painter.restore();
    }

    painter.end();

    QWidget::paintEvent(event);
}

void DayButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        emit selected(this);
}
