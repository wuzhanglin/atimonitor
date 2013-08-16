#pragma once
#pragma warning(disable:4251)

#include "globals.h"
#include <string>
#include <vector>
#include "adl/include/adl_structures.h"

namespace Dm{

    class EXPORT StatusData
    {
    public:
        int index;

        int gpuTemperature;
        int gpuUsage;
        int gpuClock;
        int gpuVolt;

        int memoryClock;
        int memoryVolt;
        int memoryUtilization;

        int fanDuty;
        int fanSpeed;

        int pcbTemperature;

        StatusData(); // constructor
    };

    class EXPORT Status
    {
    public:
        StatusData data;

        void print() const;
        void update(const AdapterInfo* pAdpt = NULL);
    };

} // end of namespace Dm