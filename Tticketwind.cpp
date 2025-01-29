#include "Tticketwind.h"

ticketWind::ticketWind() {
    maxLengthQueue = 0;
    currentLengthQueue = 0;
    windowIsOpen = false;
}

ticketWind::ticketWind(int num) {
    maxLengthQueue = num;
    currentLengthQueue = 0;
    windowIsOpen = false;
}

int ticketWind::GetCurrentQueue()
{
    return currentLengthQueue;
}
int ticketWind::GetMaxQueue()
{
    return maxLengthQueue;
}
bool ticketWind::GetWindowIsOpen()
{
    return windowIsOpen;
}

void ticketWind::SetCurrentLengthQueue(int num)
{
    currentLengthQueue = num;
}

void ticketWind::SetMaxLengthQueue(int num)
{
    maxLengthQueue = num;
}

void  ticketWind::SetWindowIsOpen(bool num)
{
    windowIsOpen = num;
}


