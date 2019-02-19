#include "Calendar.h"
#include <QLabel>
#include "DayButton.h"
#include <QDebug>
#include <QPainter>
#include <QPalette>

Calendar::Calendar(QWidget *parent)
    : QWidget(parent)
    , weekTextColor(Qt::black)
    , todayTextColor(QColor(251,196,42))
    , todayBkBrush(QBrush(QColor(247,144,28)))
    , activeMonthTextColor(Qt::black)
    , inactiveMonthTextColor(QColor(200,200,200))
    , selectedDateTextColor(QColor(255,255,0))
    , selectedDateBkBrush(QBrush(QColor(128,233,34)))
{
    //两个button 一个月份加1 一个月份减1
    QPushButton *addButton = new QPushButton;
//    addButton->setText("+1");
    addButton->setIcon(QIcon(QPixmap(":/images/Arrow-Left.png")));
    connect(addButton,SIGNAL(clicked(bool)),this,SLOT(addMonth()));
    addButton->setStyleSheet("background:transparent");

    QPushButton *jianButton = new QPushButton;
//    jianButton->setText("-1");
    jianButton->setIcon(QIcon(QPixmap(":/images/Arrow-Right.png")));
    connect(jianButton,SIGNAL(clicked(bool)),this,SLOT(jianMonth()));
    jianButton->setStyleSheet("background:transparent");

    dateLabel = new QLabel(this);
    dateLabel->setText(formatDate(QDate::currentDate()));

    //初始化头
    headerLayout = new QHBoxLayout;
    headerLayout->addWidget(addButton);
    headerLayout->addStretch();
    headerLayout->addWidget(dateLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(jianButton);
    headerLayout->setContentsMargins(0,0,0,0);

    //初始化星期
    weekLayout = new QGridLayout;
    weekLayout->setContentsMargins(0,0,0,0);
//    QStringList weekDay;
    weekDay << "Mon" << "Tun" << "Wen" << "Thu" << "Fri" << "Sat" << "Sun";
    for(ushort i=0;i<7;i++)
    {
        QLabel *label = new QLabel;
        label->setText(weekDay.at(i));
        weekLayout->addWidget(label,0,i,Qt::AlignCenter);
        weekMapWidget.insert(label,weekDay.at(i));
    }

    mouthLayout = new QGridLayout;

    for(qint8 i=1;i<=42;i++)
    {
        DayButton *btn = new DayButton;
        connect(btn,SIGNAL(selected(DayButton*)),this,SLOT(onDateSelected(DayButton*)));
        mapWidget.insert(btn,i);
    }

    //初始化container
//    container = new QWidget;
//    containerLayout = new QVBoxLayout;
//    containerLayout->addLayout(headerLayout);
//    containerLayout->addLayout(weekLayout);
//    containerLayout->setMargin(0);
//    container->setContentsMargins(0,0,0,0);
//    container->setLayout(containerLayout);

//    container->setAutoFillBackground(true);
//    QPalette palette = container->palette();
//    palette.setColor(QPalette::Window,QColor(0,0,233));
//    container->setPalette(palette);

//    container->setStyleSheet("background:rgb(223,224,223)");

    layout = new QVBoxLayout(this);
//    layout->addWidget(addButton);
//    layout->addWidget(jianButton);
    layout->addLayout(headerLayout);
    layout->addLayout(weekLayout);
//    layout->addWidget(container);
    layout->addLayout(mouthLayout);

    layout->setSpacing(14); //设置头布局 星期布局 月份布局的间距

    setLayout(layout);

    today = QDate::currentDate();

    initCalendar(today);
    setBackground(QColor(255,255,255));

    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}

void Calendar::initCalendar(QDate date)
{
    tempMapWidget.clear();
    //先置DayButton为null
    todayDayButton = NULL;

    selectedDate = date;
    qDebug() << selectedDate;

    //设置日期为当月的第一天
    date.setDate(date.year(),date.month(),1);

    qint8 key=1;
    qint8 nextDay=1;
    qint8 selectDay = selectedDate.day();
    qint8 dayOfWeek=date.dayOfWeek();   //获取当月的第一天为星期几
    qint8 curMaxDays=date.daysInMonth(); //获取当月的最大天数
    qint8 preMaxDays=date.addMonths(-1).daysInMonth();    //获取上月的最大天数

    qint8 deltaKey = 42;
    for(qint8 row=0;row<6;row++)
    {
        for(qint8 col=0;col<7;col++)
        {
            DayButton *btn;

            qint8 day;  //几号

            QColor color;

            if(key>curMaxDays || dayOfWeek>1)
            {
                btn = mapWidget.key(deltaKey);

                qint8 tempDay;

                if(dayOfWeek>1)
                {
                    tempDay = preMaxDays-dayOfWeek+2;
                    tempMapWidget.insert(btn,tempDay-preMaxDays);
                    dayOfWeek--;
                    color = inactiveMonthTextColor;
                }
                else
                {
                    tempDay = nextDay;
                    tempMapWidget.insert(btn,curMaxDays+tempDay);
                    nextDay++;
                    color = inactiveMonthTextColor;
                }

                day = tempDay;
                deltaKey--;
            }
            else
            {
                btn = mapWidget.key(key);
                day = key;

                color = activeMonthTextColor;

                if(key==selectDay)
                {
                    selectedDayButton = btn;
                    color = selectedDateTextColor;
                }

                if(date==today){
                    todayDayButton = btn;
                    color = todayTextColor;
                }

                date=date.addDays(1);
                key++;
            }

            //如果传入的时间date等于今天的时间 设置颜色为红色


            btn->setText(QString::number(day));
            btn->setTextColor(color);
            mouthLayout->addWidget(btn,row,col,Qt::AlignCenter);
        }
    }
}

void Calendar::updateCalendar()
{
    initCalendar(selectedDate);
}

void Calendar::setBackground(const QColor &color)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window,color);
    this->setPalette(palette);
    this->setAutoFillBackground(true);
}

void Calendar::setBackground(const QBrush &brush)
{
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,brush);
    this->setPalette(palette);
    this->setAutoFillBackground(true);
}

void Calendar::setSpacing(const int &value)
{
    if(value<0)
        return;

    this->weekLayout->setSpacing(value);
    this->mouthLayout->setSpacing(value);
}

QString Calendar::formatDate(const QDate &date)
{
//    qDebug() << date;
    int year  = date.year();
    int month = date.month();
    int day = date.day();
    QString str = QString("%1-%2-%3").arg(year).arg(month).arg(day);
    return str;
}

//
void Calendar::updateDate(const QDate &date)
{
    QString str = formatDate(date);
    this->dateLabel->setText(str);
}

void Calendar::setHeaderDateTextColor(const QColor &color)
{
    QPalette palette = dateLabel->palette();
    palette.setColor(QPalette::WindowText,color);
    dateLabel->setPalette(palette);
}

void Calendar::setWeekTextColor(const QColor &color)
{
    QLabel *label;
    for(int i=0;i<weekMapWidget.count();i++) {
        label = weekMapWidget.key(weekDay.at(i));
        QPalette palette = label->palette();
        palette.setColor(QPalette::WindowText,color);
        label->setPalette(palette);
    }
}

void Calendar::setActiveMonthTextColor(const QColor &color)
{
    if(!color.isValid())
        return;

    activeMonthTextColor = color;
    updateCalendar();
}

void Calendar::setInactiveMonthTextColor(const QColor &color)
{
    if(!color.isValid())
        return;

    inactiveMonthTextColor = color;
    updateCalendar();
}

void Calendar::setSelectedDateTextColor(const QColor &color)
{
    if(!color.isValid())
        return;

    selectedDateTextColor = color;
    updateCalendar();
}

void Calendar::setSelectedDateBkBrush(const QBrush &brush)
{
    selectedDateBkBrush = brush;
    updateCalendar();
}

//QColor &Calendar::activeMonthTextColor() const
//{
//    return activeMonthTextColor;
//}

void Calendar::addMonth()
{
    selectedDate = selectedDate.addMonths(-1);
    initCalendar(selectedDate);
    updateDate(selectedDate);
}

void Calendar::jianMonth()
{
    selectedDate = selectedDate.addMonths(1);
    initCalendar(selectedDate);
    updateDate(selectedDate);
}

void Calendar::onDateSelected(DayButton *dayButton)
{
    if(selectedDayButton != dayButton)
    {
        if(mapWidget.value(dayButton)<=selectedDate.daysInMonth())
        {
            selectedDayButton = dayButton;
            selectedDate.setDate(selectedDate.year(),selectedDate.month(),mapWidget.value(dayButton));
            initCalendar(selectedDate);
            updateDate(selectedDate);
            emit dateSelected(selectedDate);
        }
        else
        {
            selectedDate = selectedDate.addDays(tempMapWidget.value(dayButton)-mapWidget.value(selectedDayButton));
            initCalendar(selectedDate);
            updateDate(selectedDate);
            emit dateSelected(selectedDate);
        }

        update();
    }
}

void Calendar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    if(selectedDayButton!=NULL)
    {
        painter.save();
        QPoint pos = selectedDayButton->pos();
        int width = selectedDayButton->width();
        int height = selectedDayButton->height();
        painter.setPen(Qt::NoPen);
        painter.setBrush(selectedDateBkBrush);
        painter.drawEllipse(pos.x(),pos.y(),width,height);
        painter.restore();
    }

    if(todayDayButton!=NULL)
    {
        painter.save();
        QPoint pos = todayDayButton->pos();
        int width = selectedDayButton->width();
        int height = selectedDayButton->height();
        painter.setPen(Qt::NoPen);
        painter.setBrush(todayBkBrush);
        painter.drawEllipse(pos.x(),pos.y(),width,height);
        painter.restore();
    }

//    QRect r = this->rect();
//    r.adjust(2,2,-2,-2);

//    QPen pen;
//    pen.setColor(QColor(0,0,255));
//    pen.setWidth(1);
//    painter.setPen(pen);
//    painter.drawRect(r);
    painter.end();

    QWidget::paintEvent(event);
}
