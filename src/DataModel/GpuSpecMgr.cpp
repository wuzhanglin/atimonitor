
#include "GpuSpecMgr.h"
#include "adl.h"

using namespace Dm;

GpuSpecMgr* GpuSpecMgr::s_pTheOnlyOne = NULL;

GpuSpecMgr::GpuSpecMgr()
{
}

GpuSpecMgr* GpuSpecMgr::get()
{
    if (s_pTheOnlyOne == NULL)
    {
        s_pTheOnlyOne = new GpuSpecMgr();
        s_pTheOnlyOne->update();
    }

    return s_pTheOnlyOne;
}

size_t GpuSpecMgr::update()
{
#ifdef FAKE_GRAPHICS_CARD
    GpuSpec gpu = GpuSpec();

    gpu.update();
    gpu.data.index = 0;
    this->gpus.push_back(gpu);

    gpu.update();
    gpu.data.index = 1;
    this->gpus.push_back(gpu);

    return 2;
#else
    size_t count = ADL::get()->mNrOfAdapters;
    if (count == 0)
        return count;

    LPADLBiosInfo pBios = (LPADLBiosInfo) malloc(sizeof(ADLBiosInfo));
    LPADLMemoryInfo pMemoryInfo = (LPADLMemoryInfo) malloc(sizeof(ADLMemoryInfo));
    ADLAdapterODClockInfo* pClock = (ADLAdapterODClockInfo*) malloc(sizeof(ADLAdapterODClockInfo));
    ADLPMActivity* pActivity = (ADLPMActivity*) malloc(sizeof(ADLPMActivity));
    ADLCrossfireComb* pCrossfireComb = (ADLCrossfireComb*) malloc(sizeof(ADLCrossfireComb));
    ADLCrossfireInfo* pCrossfire = (ADLCrossfireInfo*) malloc(sizeof(ADLCrossfireInfo));
    for (size_t i = 0; i < count; i++)
    {
        GpuSpec gpu = GpuSpec();
        gpu.update(&(ADL::get()->mpAdapterInfo[i]));

        memset(pBios, 0, sizeof(ADLBiosInfo));
        if (SAFE_CALL(ADL::get()->ADL_Adapter_VideoBiosInfo_Get)(i, pBios) == ADL_OK)
        {
            gpu.data.biosVersion = pBios->strVersion;
        }

        memset(pMemoryInfo, 0, sizeof(ADLMemoryInfo));
        if (SAFE_CALL(ADL::get()->ADL_Adapter_MemoryInfo_Get)(i, pMemoryInfo) == ADL_OK)
        {
            gpu.data.memorySize = int64(long double(pMemoryInfo->iMemorySize) / 1024.0 / 1024.0);
            gpu.data.memoryType = pMemoryInfo->strMemoryType;
            gpu.data.bandwidth  = pMemoryInfo->iMemoryBandwidth;
        }

        memset(pClock, 0, sizeof(ADLAdapterODClockInfo));
        if (SAFE_CALL(ADL::get()->ADL_Display_ODClockInfo_Get)(i, pClock) == ADL_OK)
        {
            gpu.data.memoryClock = pClock->sMemoryClock.iCurrentClock;
            gpu.data.memoryDefaultClock = pClock->sMemoryClock.iDefaultClock;
            gpu.data.gpuClock = pClock->sEngineClock.iCurrentClock;
            gpu.data.gpuDefaultClock = pClock->sEngineClock.iDefaultClock;
        }
        
        memset(pActivity, 0, sizeof(ADLPMActivity));
        if (SAFE_CALL(ADL::get()->ADL_Overdrive5_CurrentActivity_Get)(i, pActivity) == ADL_OK)
        {
            gpu.data.memoryClock = pActivity->iMemoryClock;
            gpu.data.gpuClock = pActivity->iEngineClock;
        }

        memset(pCrossfireComb, 0, sizeof(ADLCrossfireComb));
        memset(pCrossfire, 0, sizeof(ADLCrossfireInfo));
        if (SAFE_CALL(ADL::get()->ADL_Adapter_Crossfire_Get)(i, pCrossfireComb, pCrossfire) == ADL_OK)
        {
            gpu.data.atiCrossFireEnabled = (pCrossfire->iSupported == ADL_TRUE);
        }

        this->gpus.push_back(gpu);
    }

    free(pBios);
    free(pMemoryInfo);
    free(pClock);
    free(pActivity);
    free(pCrossfireComb);
    free(pCrossfire);
    return count;
#endif // FAKE_GRAPHICS_CARD
}

size_t GpuSpecMgr::getCount() const
{
    return this->gpus.size();
}

GpuSpec& GpuSpecMgr::getGpuSpec(int index)
{
    return this->gpus[index];
}