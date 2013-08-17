
#include "PerfOverTime.h"
#include <iostream>
#include "adl.h"

using namespace Dm;

PerfOverTimeData::PerfOverTimeData()
    : index(0)
    , hdType("")

    , gpuTemperatureMax(0)
    , gpuTemperatureNow(0)
    , gpuTemperatureMin(0)

    , gpuClockMax(0)
    , gpuClockNow(0)
    , gpuClockMin(0)

    , gpuUsageMax(0)
    , gpuUsageNow(0)
    , gpuUsageMin(0)

    , fanSpeedMax(0)
    , fanSpeedNow(0)
    , fanSpeedMin(0)
{
}

void PerfOverTime::print() const
{
#define PRINT_DATA(key) std::cout << std::endl << #key << ": " << this->data.key

    std::cout << std::endl << "______________" << "PERFORMANCE OVER TIME " << this->data.index << "_________________";

    PRINT_DATA(index);
    PRINT_DATA(hdType);

    PRINT_DATA(gpuTemperatureMax);
    PRINT_DATA(gpuTemperatureNow);
    PRINT_DATA(gpuTemperatureMin);

    PRINT_DATA(gpuClockMax);
    PRINT_DATA(gpuClockNow);
    PRINT_DATA(gpuClockMin);

    PRINT_DATA(gpuUsageMax);
    PRINT_DATA(gpuUsageNow);
    PRINT_DATA(gpuUsageMin);

    PRINT_DATA(fanSpeedMax);
    PRINT_DATA(fanSpeedNow);
    PRINT_DATA(fanSpeedMin);
}

void PerfOverTime::update(const AdapterInfo* pAdpt/* = NULL*/)
{
#ifdef FAKE_GRAPHICS_CARD

    this->data.index = 0;
    this->data.hdType = "HD7990-DC2T-3GD5";

    this->data.gpuTemperatureMax = 58;
    this->data.gpuTemperatureNow = 50;
    this->data.gpuTemperatureMin = 40;

    this->data.gpuClockMax = 1151;
    this->data.gpuClockNow = 1150;
    this->data.gpuClockMin = 1105;

    this->data.gpuUsageMax = 100;
    this->data.gpuUsageNow = 89;
    this->data.gpuUsageMin = 80;

    this->data.fanSpeedMax = 100;
    this->data.fanSpeedNow = 89;
    this->data.fanSpeedMin = 80;

#else

    if (pAdpt == NULL)
        return;

    this->data.index = pAdpt->iAdapterIndex;
    this->data.hdType = "";

    this->data.gpuTemperatureMax = 0;
    this->data.gpuTemperatureNow = 0;
    this->data.gpuTemperatureMin = 0;

    this->data.gpuClockMax = 0;
    this->data.gpuClockNow = 0;
    this->data.gpuClockMin = 0;

    this->data.gpuUsageMax = 0;
    this->data.gpuUsageNow = 0;
    this->data.gpuUsageMin = 0;

    this->data.fanSpeedMax = 0;
    this->data.fanSpeedNow = 0;
    this->data.fanSpeedMin = 0;

#endif
}