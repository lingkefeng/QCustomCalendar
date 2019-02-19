#ifndef DAYBUTTON_H
#define DAYBUTTON_H

#include <QWidget>
#include <QAbstractButton>
#include <QPushButton>

class DayButton : public QPushButton
{
    Q_OBJECT

public:
    explicit DayButton(QWidget *parent = 0);

public:
    void setTextColor(const QColor &color);

    void setHoverTextColor(const QColor &color);
    void setHoverBkBrush(const QBrush &brush);

signals:
    void selected(void);
    void selected(DayButton *dayButton);

public slots:

protected:
   void enterEvent(QEvent *event);
   void leaveEvent(QEvent *event);
   void paintEvent(QPaintEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);

private:
   QColor textColor;
   bool   isHover;

   QColor hoverTextColor;    //悬停状态文字颜色
   QBrush hoverBkBrush;      //悬停状态背景颜色
};

#endif // DAYBUTTON_H
