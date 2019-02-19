#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>
#include <QDate>
#include <QLabel>
#include <QVBoxLayout>
#include <QMap>
#include <QPushButton>
#include "DayButton.h"

class Calendar : public QWidget
{
    Q_OBJECT
public:
    explicit Calendar(QWidget *parent = 0);

public:
    void initCalendar(QDate date);
    //当设置文字 背景颜色时 需要对日历进行更新
    void updateCalendar(void);
    void setBackground(const QColor &color);
    void setBackground(const QBrush &brush);
    void setSpacing(const int &value);

    QString formatDate(const QDate &date);
    void updateDate(const QDate &date);

    void setHeaderDateTextColor(const QColor &color); //设置顶部时间标签文字的颜色
    void setWeekTextColor(const QColor &color);

    void setActiveMonthTextColor(const QColor &color);
//    QColor& activeMonthTextColor() const;
    void setInactiveMonthTextColor(const QColor &color);
    void setSelectedDateTextColor(const QColor &color);
    void setSelectedDateBkBrush(const QBrush &brush);

    //选中日期
//    void selectedDate() const;

signals:
    void dateSelected(QDate date);

public slots:
    void addMonth();
    void jianMonth();

    void onDateSelected(DayButton *dayButton);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QWidget *container;     //包裹头布局和星期布局，方便设置背景色
    QVBoxLayout *containerLayout;

    QVBoxLayout *layout;    //主布局
    QHBoxLayout *headerLayout;  //头布局
    QGridLayout *weekLayout;   //星期布局
    QGridLayout *mouthLayout;  //月份布局 存放每一天日期

    QLabel *dateLabel;  //显示年月
    QMap<DayButton*,qint8> mapWidget;
    QMap<DayButton*,qint8> tempMapWidget;
    QMap<QLabel*,QString> weekMapWidget;
    QStringList weekDay;    //存放星期

    QDate today;                        //今天的日期
    QDate selectedDate;
    DayButton *selectedDayButton;
    DayButton *todayDayButton;

    QColor weekTextColor;               //星期文字颜色
    QColor todayTextColor;              //当月当天的文字颜色
    QBrush todayBkBrush;                //当月当天的背景颜色
    QColor activeMonthTextColor;        //当月文字颜色
    QColor inactiveMonthTextColor;      //不在当月文字颜色
    QColor selectedDateTextColor;       //选中文字颜色
    QBrush selectedDateBkBrush;         //选中文字背景画刷
};

#endif // CALENDAR_H
