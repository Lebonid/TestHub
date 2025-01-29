#ifndef TTICKETWIND_H
#define TTICKETWIND_H

class ticketWind
{

private:
    int maxLengthQueue = 0;
    int currentLengthQueue = 0;
    bool windowIsOpen = false;

public:

    ticketWind();
    ticketWind(int num);



    int GetCurrentQueue();
    int GetMaxQueue();
    bool GetWindowIsOpen();
    void SetCurrentLengthQueue(int num);
    void SetMaxLengthQueue(int num);
    void SetWindowIsOpen(bool num);

};

#endif // TTICKETWIND_H
