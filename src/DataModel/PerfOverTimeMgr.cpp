
#include "PerfOverTimeMgr.h"
#include "adl.h"

using namespace Dm;

PerfOverTimeMgr* PerfOverTimeMgr::s_pTheOnlyOne = NULL;

PerfOverTimeMgr::PerfOverTimeMgr()
{
}

PerfOverTimeMgr* PerfOverTimeMgr::get()
{
    if (s_pTheOnlyOne == NULL)
    {
        s_pTheOnlyOne = new PerfOverTimeMgr();
        s_pTheOnlyOne->update();
    }

    return s_pTheOnlyOne;
}

size_t PerfOverTimeMgr::update()
{
#ifdef FAKE_GRAPHICS_CARD
    PerfOverTime perf = PerfOverTime();

    perf.update();
    perf.data.index = 0;
    this->perfs.push_back(perf);

    perf.update();
    perf.data.index = 1;
    this->perfs.push_back(perf);

    return 2;
#else
    size_t count = ADL::get()->mNrOfAdapters;
    if (count == 0)
        return count;

    ADLAdapterODClockInfo* pClock = (ADLAdapterODClockInfo*) malloc(sizeof(ADLAdapterODClockInfo));
    ADLPMActivity* pActivity = (ADLPMActivity*) malloc(sizeof(ADLPMActivity));
    ADLTemperature* pTemperature = (ADLTemperature*) malloc(sizeof(ADLTemperature));
    ADLOD6CurrentStatus* pCurrentStatus = (ADLOD6CurrentStatus*) malloc(sizeof(ADLOD6CurrentStatus));
    ADLFanSpeedValue* pFan = (ADLFanSpeedValue*) malloc(sizeof(ADLFanSpeedValue));
    ADLOD6FanSpeedInfo* pFanOD6 = (ADLOD6FanSpeedInfo*) malloc(sizeof(ADLOD6FanSpeedInfo));
    for (size_t i = 0; i < count; i++)
    {
        PerfOverTime perf = PerfOverTime();
        perf.update(&(ADL::get()->mpAdapterInfo[i]));

        memset(pClock, 0, sizeof(ADLAdapterODClockInfo));
        if (SAFE_CALL(ADL::get()->ADL_Display_ODClockInfo_Get)(i, pClock) == ADL_OK)
        {
            perf.data.gpuClockNow = pClock->sEngineClock.iCurrentClock;
        }
        
        memset(pActivity, 0, sizeof(ADLPMActivity));
        if (SAFE_CALL(ADL::get()->ADL_Overdrive5_CurrentActivity_Get)(i, pActivity) == ADL_OK)
        {
            perf.data.gpuClockNow = pActivity->iEngineClock;
            perf.data.gpuUsageNow = pActivity->iActivityPercent;
        }

        int t = 0;
        memset(pTemperature, 0, sizeof(ADLTemperature));
        if (SAFE_CALL(ADL::get()->ADL_Overdrive5_Temperature_Get)(i, 0, pTemperature) == ADL_OK)
        {
            perf.data.gpuTemperatureNow = pTemperature->iTemperature;
        }
        else if (SAFE_CALL(ADL::get()->ADL_Overdrive6_Temperature_Get)(i, &t))
        {
            perf.data.gpuTemperatureNow = t;
        }

        memset(pCurrentStatus, 0, sizeof(ADLOD6CurrentStatus));
        if (SAFE_CALL(ADL::get()->ADL_Overdrive6_CurrentStatus_Get)(i, pCurrentStatus) == ADL_OK)
        {
            perf.data.gpuUsageNow = pCurrentStatus->iActivityPercent;
        }

        memset(pFan, 0, sizeof(ADLFanSpeedValue));
        memset(pFanOD6, 0, sizeof(ADLOD6FanSpeedInfo));
        if (SAFE_CALL(ADL::get()->ADL_Overdrive5_FanSpeed_Get)(i, 0, pFan) == ADL_OK)
        {
            perf.data.fanSpeedNow = pFan->iFanSpeed;
        }
        else if (SAFE_CALL(ADL::get()->ADL_Overdrive6_FanSpeed_Get)(i, pFanOD6) == ADL_OK)
        {
            perf.data.fanSpeedNow = pFanOD6->iFanSpeedPercent;
        }

        this->perfs.push_back(perf);
    }

    free(pClock);
    free(pActivity);
    free(pTemperature);
    free(pCurrentStatus);
    free(pFan);
    free(pFanOD6);
    return count;
#endif // FAKE_GRAPHICS_CARD
}

size_t PerfOverTimeMgr::getCount() const
{
    return this->perfs.size();
}

PerfOverTime& PerfOverTimeMgr::getPerfOverTime(int index)
{
    return this->perfs[index];
}