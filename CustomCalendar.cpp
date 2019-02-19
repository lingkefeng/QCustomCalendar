#include "CustomCalendar.h"
#include <QVBoxLayout>

CustomCalendar::CustomCalendar(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;

    calendar1 = new Calendar(this);
    calendar1->setSpacing(5);

    calendar2 = new Calendar(this);
    calendar2->setSpacing(5);
    calendar2->setSelectedDateBkBrush(QBrush(QColor(128,128,128)));


    calendar3 = new Calendar(this);
    calendar3->setSpacing(5);
    calendar3->setBackground(QColor(39,49,66));
    calendar3->setActiveMonthTextColor(QColor(241,241,241));
    calendar3->setInactiveMonthTextColor(QColor(147,152,161));
    calendar3->setWeekTextColor(QColor(255,255,255));
    calendar3->setHeaderDateTextColor(QColor(255,255,255));

    layout->addWidget(calendar1);
    layout->addWidget(calendar2);
    layout->addWidget(calendar3);

    setLayout(layout);
}

CustomCalendar::~CustomCalendar()
{

}
