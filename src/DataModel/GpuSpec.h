#pragma once
#pragma warning(disable:4251)

#include "globals.h"
#include <string>
#include <vector>
#include "adl/include/adl_structures.h"

namespace Dm{

    class EXPORT GpuSpecData
    {
    public:
        int         index;
        std::string name;
        std::string gpu;
        std::string revision;
        std::string releaseDate;
        std::string biosVersion;
        std::string deviceID;
        std::string subvendor;
        std::string busInterface;
        int64       memorySize;
        std::string memoryType;
        std::string driverVersion;

        int     rops;
        int     busWidth;
        int64   bandwidth;
        int     gpuClock;
        int     gpuDefaultClock;
        int     memoryClock;
        int     memoryDefaultClock;
        int     shaderClock;
        int     shaderDefaultClock;
        bool    atiCrossFireEnabled;

        GpuSpecData(); // constructor
    };

    class EXPORT GpuSpec
    {
    public:
        GpuSpecData data;

        void print() const;
        void update(const AdapterInfo* pAdpt = NULL);
    };

} // end of namespace Dm