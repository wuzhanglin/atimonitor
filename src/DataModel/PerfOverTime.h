#pragma once
#pragma warning(disable:4251)

#include "globals.h"
#include <string>
#include <vector>
#include "adl/include/adl_structures.h"

namespace Dm{

    class EXPORT PerfOverTimeData
    {
    public:
        int index;
        std::string hdType;

        int gpuTemperatureMax;
        int gpuTemperatureNow;
        int gpuTemperatureMin;

        int gpuClockMax;
        int gpuClockNow;
        int gpuClockMin;

        int gpuUsageMax;
        int gpuUsageNow;
        int gpuUsageMin;

        int fanSpeedMax;
        int fanSpeedNow;
        int fanSpeedMin;

        PerfOverTimeData(); // constructor
    };

    class EXPORT PerfOverTime
    {
    public:
        PerfOverTimeData data;

        void print() const;
        void update(const AdapterInfo* pAdpt = NULL);
    };

} // end of namespace Dm