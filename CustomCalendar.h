#ifndef CUSTOMCALENDAR_H
#define CUSTOMCALENDAR_H

#include <QWidget>
#include "Calendar.h"

class CustomCalendar : public QWidget
{
    Q_OBJECT

public:
    explicit CustomCalendar(QWidget *parent = 0);
    ~CustomCalendar();

private:
    Calendar *calendar1;
    Calendar *calendar2;
    Calendar *calendar3;
};

#endif // CUSTOMCALENDAR_H
