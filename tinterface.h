#ifndef TINTERFACE_H
#define TINTERFACE_H

#include "Tticketwind.h"

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class TInterface;
}
QT_END_NAMESPACE

class TInterface : public QWidget
{
    Q_OBJECT

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

    void createLablWindow(std::string str, ticketWind tcw, int cnt);

    QString messageWindow(ticketWind tcw, int cnt);

    void updateQueueWindow();

    void dialogWindow(QString title, QString message);

    void changeColorLabel(int index);

    void updateCountServ();


private slots:
    void acceptWindowButton_pressed();

    void queueButton_pressed();

    void updateTimer();

    void windowButton_pressed();

    void timerButton_pressed();

    void serviceQueueWindow();

    void indexChanged(int index);

    void openAllWindow();

    void serviceTimeBtn();

private:
    Ui::TInterface *ui;

    int countWindow = 0;

    int countQueue = 0;

    ticketWind *TicketWindow;

    void deleteLabel(int count);

    //Timer

    int timerTime = 1;

    bool timeIsActive = false;

    QTimer *tmr = new QTimer();

    QTimer *servTimer = new QTimer();

    int serviceTime = 0;

    int countClient = 0;


};
#endif // TINTERFACE_H
