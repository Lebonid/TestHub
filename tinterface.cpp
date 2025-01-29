#include "tinterface.h"

#include "ui_tinterface.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TInterface)
{
    this->setWindowTitle("RailStation");
    this->setMinimumSize(960,640);

    ui->setupUi(this);

    connect(ui->setServiceTimeButton, SIGNAL(pressed()), this, SLOT(serviceTimeBtn()));

    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTimer()));

    ui->spinWindowCountBox->setMaximum(20);


    connect(servTimer, SIGNAL(timeout()), this, SLOT(serviceQueueWindow()));

    connect(ui->comboBoxWindow, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));

    connect(ui->windowAllButton, SIGNAL(pressed()), this, SLOT(openAllWindow()));

    connect(ui->acceptWindowButton, SIGNAL(pressed()), this, SLOT(acceptWindowButton_pressed()));

    connect(ui->windowButton, SIGNAL(pressed()), this, SLOT(windowButton_pressed()));

    connect(ui->queueButton, SIGNAL(pressed()), this, SLOT(queueButton_pressed()));

    connect(ui->timerButton, SIGNAL(pressed()), this, SLOT(timerButton_pressed()));
}

TInterface::~TInterface()
{
    delete ui;
}

void TInterface::acceptWindowButton_pressed()
{
    QList<QString> stringList;

    deleteLabel(countWindow);

    countWindow = ui->spinWindowCountBox->text().toInt();

    countQueue = ui->spinQueueCountBox->text().toInt();

    if(countQueue == 0 || countWindow == 0)
    {
        dialogWindow("Предупреждение", "Выберите параметры кассы");
        return;
    }

    TicketWindow = new ticketWind[countWindow];



    for(int i = 0; i < countWindow; i++)
    {
        TicketWindow[i].SetMaxLengthQueue(countQueue);
    }

    ui->comboBoxWindow->clear();

    for(int i = 0; i < countWindow; i++)
    {
        stringList.append("Окно " + QString::fromStdString(std::to_string(i+1)));
    }

    ui->comboBoxWindow->addItems(stringList);

    for(int i = 0; i < countWindow; i++)
    {
        createLablWindow("str",TicketWindow[i],i);
        changeColorLabel(i);
    }

}


void TInterface::queueButton_pressed()
{
    int value = ui->comboBoxWindow->currentIndex();
    if(value == -1)
    {
        dialogWindow("Предупреждение", "Выберите окно!");
        return;
    }

    if(TicketWindow[value].GetWindowIsOpen() == false)
    {
        TicketWindow[value].SetWindowIsOpen(true);
        changeColorLabel(value);
        ui->queueButton->setText("Закрыть очередь");
    }else{
        TicketWindow[value].SetWindowIsOpen(false);
        changeColorLabel(value);
        ui->queueButton->setText("Открыть очередь");
    }

    QLabel  *lbl1 = this->findChild<QLabel *>(QString::fromStdString("lbl_" + std::to_string(value)));
    lbl1->setText(messageWindow(TicketWindow[value], value));

    if( ui->vertLayout->objectName() == QString::fromStdString("lbl_" + std::to_string(value)))
    {
       messageWindow(TicketWindow[value],value);
    }
/*
    ui->lbl1->clear();
    ui->lbl1->setText("CurrentIndex: " + QString::fromStdString(std::to_string(value)) +
                      " /// MaxLength: " + QString::fromStdString(std::to_string(TicketWindow[value].GetMaxQueue())) +
                      " /// Status: " + QString::fromStdString(std::to_string(TicketWindow[value].GetWindowIsOpen())) +
                      " /// Current queue: " + QString::fromStdString(std::to_string(TicketWindow[value].GetCurrentQueue())) );
*/
}

void TInterface::createLablWindow(std::string str, ticketWind tcw, int cnt)
{

    QLabel *lbl = new QLabel(this);

    QFont font("Arial", 13, QFont::Bold);



    lbl->setFont(font);
    lbl->setText(messageWindow(tcw,cnt));
    lbl->setObjectName("lbl_" + std::to_string(cnt));
    lbl->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    lbl->setAlignment(Qt::AlignHCenter |Qt::AlignVCenter);
    lbl->setMaximumHeight(30);

    lbl->setMaximumWidth(340);

    ui->vertLayout->addWidget(lbl);

}

QString TInterface::messageWindow(ticketWind tcw, int cnt)
{
    QString message;
    std::string stdBool;

    if(tcw.GetWindowIsOpen() == true)
    {
        stdBool = " Открыто ";
    }else{
        stdBool = " Закрыто ";
    }

    message = "Окно " + QString::fromStdString(std::to_string(cnt + 1)) + "  " + QString::fromStdString(stdBool) + " Кол-во в очереди: " + QString::fromStdString( std::to_string(tcw.GetCurrentQueue()));

    return message;
}

void TInterface::updateTimer()
{

    updateQueueWindow();
}

void TInterface::updateQueueWindow()
{

    int point = -1;

    int minCount = TicketWindow->GetMaxQueue();
    for(int i = 0; i < countWindow; i++)
    {
        if(TicketWindow[i].GetWindowIsOpen())
        {
            if(TicketWindow[i].GetCurrentQueue() < TicketWindow[i].GetMaxQueue())
            {
                if(TicketWindow[i].GetCurrentQueue() < minCount)
                {
                    minCount = TicketWindow[i].GetCurrentQueue();
                    point = i;
                }

            }
        }
    }

    if(TicketWindow[point].GetWindowIsOpen() == true)
    {
        if(TicketWindow[point].GetCurrentQueue() < TicketWindow[point].GetMaxQueue())
        {
            int val = TicketWindow[point].GetCurrentQueue() + 1;
            TicketWindow[point].SetCurrentLengthQueue(val);

            QLabel  *lbl1 = this->findChild<QLabel *>(QString::fromStdString("lbl_" + std::to_string(point)));
            lbl1->setText(messageWindow(TicketWindow[point], point));
        }
    }

}



void TInterface::serviceQueueWindow()
{
    for(int i = 0; i < countWindow; i++)
    {
        if(TicketWindow[i].GetCurrentQueue() > 0)
        {
            int val = TicketWindow[i].GetCurrentQueue() - 1;
            TicketWindow[i].SetCurrentLengthQueue(val);

            updateCountServ();

            QLabel  *lbl1 = this->findChild<QLabel *>(QString::fromStdString("lbl_" + std::to_string(i)));
            lbl1->setText(messageWindow(TicketWindow[i], i));
        }
    }
}

void TInterface::deleteLabel(int count)
{
    QLabel  *lbl1;
    for(int i = 0; i<count; i++ )
    {
        if(!this->findChild<QLabel *>(QString::fromStdString("lbl_" + std::to_string(i))))return;
        lbl1 = this->findChild<QLabel *>(QString::fromStdString("lbl_" + std::to_string(i)));
        delete lbl1;
    }
}

void TInterface::windowButton_pressed()
{
    if(ui->spinTimerBox->text().toInt() == 0)
    {
        dialogWindow("Предупреждение", "Настройте время!");
        return;
    }
    if(serviceTime == 0)
    {
        dialogWindow("Предупреждение", "Настройте время обработки пассажира");
        return;
    }


    if(timeIsActive == false)
    {
        timeIsActive = true;
        ui->windowButton->setText("Закрыть кассу");
        ui->labelStatus->setText("Открыто");
        ui->labelStatus->setStyleSheet("QLabel{ color: black; background: #3dad36 }");
        tmr->start();
    }else{
        timeIsActive = false;
        ui->windowButton->setText("Открыть кассу");
        ui->labelStatus->setText("Закрыто");
        ui->labelStatus->setStyleSheet("QLabel{ color: black; background: #ee6161 }");
        tmr->stop();
    }
}


void TInterface::timerButton_pressed()
{
    if(ui->spinTimerBox->text().toInt() == 0)
    {
        dialogWindow("Предупреждение", "Настройте время!");
        return;
    }

    timerTime = ui->spinTimerBox->text().toInt() * 1000;

    tmr->setInterval(timerTime);
}

void TInterface::dialogWindow(QString title, QString message)
{
    QMessageBox::warning(this,title, message);
}

void TInterface::indexChanged(int index)
{
    if(TicketWindow[index].GetWindowIsOpen() == false){
        ui->queueButton->setText("Открыть очередь");
    }else{
        ui->queueButton->setText("Закрыть очередь");
    }
}

void TInterface::changeColorLabel(int index)
{
    QLabel  *lbl1 = this->findChild<QLabel *>(QString::fromStdString("lbl_" + std::to_string(index)));
    if(TicketWindow[index].GetWindowIsOpen())
    {
        lbl1->setStyleSheet("QLabel{ color: black; background: #3dad36 }"); // green
    }else{
        lbl1->setStyleSheet("QLabel{ color: black; background: #ee6161 }"); // red
    }
    lbl1->setText(messageWindow(TicketWindow[index], index));
}

void  TInterface::openAllWindow()
{
    if(countQueue == 0 || countWindow == 0)
    {
        dialogWindow("Предупреждение", "Настройте параметры кассы");
        return;
    }

    if(TicketWindow->GetWindowIsOpen())
    {
        for(int i = 0; i < countWindow; i++)
        {
            TicketWindow[i].SetWindowIsOpen(false);
            changeColorLabel(i);
            ui->windowAllButton->setText("Открыть все окна");
        }
    }else
    {
        for(int i = 0; i < countWindow; i++)
        {
            TicketWindow[i].SetWindowIsOpen(true);
            changeColorLabel(i);
            ui->windowAllButton->setText("Закрыть все окна");
        }
    }


}

void TInterface::serviceTimeBtn()
{
    serviceTime  = ui->spinServiceTimeBox->text().toInt() * 1000;

    if(serviceTime == 0)
    {
        dialogWindow("Предупреждение", "Минимальное время должно быть больше 0!");
        return;
    }

    servTimer->setInterval(serviceTime);

    servTimer->start();

}

void TInterface::updateCountServ()
{
    countClient++;
    QString str = QString::fromStdString(std::to_string(countClient));
    ui->countPassLabel->setText(str);
}

