
#include "Status.h"
#include <iostream>
#include "adl.h"

using namespace Dm;

StatusData::StatusData()
    : index(0)
    , gpuTemperature(0)
    , gpuUsage(0)
    , gpuClock(0)
    , gpuVolt(0)

    , memoryClock(0)
    , memoryVolt(0)
    , memoryUtilization(0)

    , fanDuty(0)
    , fanSpeed(0)

    , pcbTemperature(0)
{
}

void Status::print() const
{
#define PRINT_DATA(key) std::cout << std::endl << #key << ": " << this->data.key

    std::cout << std::endl << "______________" << "CURRENT STATUS " << this->data.index << "_________________";

    PRINT_DATA(index);

    PRINT_DATA(gpuTemperature);
    PRINT_DATA(gpuUsage);
    PRINT_DATA(gpuClock);
    PRINT_DATA(gpuVolt);

    PRINT_DATA(memoryClock);
    PRINT_DATA(memoryVolt);
    PRINT_DATA(memoryUtilization);

    PRINT_DATA(fanDuty);
    PRINT_DATA(fanSpeed);

    PRINT_DATA(pcbTemperature);
}

void Status::update(const AdapterInfo* pAdpt/* = NULL*/)
{
#ifdef FAKE_GRAPHICS_CARD

    this->data.index = 0;
    this->data.gpuTemperature = 0;
    this->data.gpuUsage = 0;
    this->data.gpuClock = 0;
    this->data.gpuVolt = 0;

    this->data.memoryClock = 0;
    this->data.memoryVolt = 0;
    this->data.memoryUtilization = 0;

    this->data.fanDuty = 0;
    this->data.fanSpeed = 0;

    this->data.pcbTemperature = 0;

#else

    if (pAdpt == NULL)
        return;

    this->data.index = pAdpt->iAdapterIndex;
    this->data.gpuTemperature = 0;
    this->data.gpuUsage = 0;
    this->data.gpuClock = 0;
    this->data.gpuVolt = 0;

    this->data.memoryClock = 0;
    this->data.memoryVolt = 0;
    this->data.memoryUtilization = 0;

    this->data.fanDuty = 0;
    this->data.fanSpeed = 0;

    this->data.pcbTemperature = 0;

#endif
}