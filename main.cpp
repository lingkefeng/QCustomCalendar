#include "CustomCalendar.h"
#include <QApplication>
#include <QDate>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomCalendar w;
    w.show();

//    QDate date = QDate::currentDate();
//    qDebug() << date;

//    qDebug() << date.dayOfWeek(); //返回值为3 星期三
//    qDebug() << date.daysInMonth();  //返回当月的天数
//    qDebug() << date.daysInYear();   //返回当年的天数 365 or 366
//    qDebug() << date.day();   //返回11  这个月的第几天

    return a.exec();
}
