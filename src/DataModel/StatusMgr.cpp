
#include "StatusMgr.h"
#include "adl.h"

using namespace Dm;

StatusMgr* StatusMgr::s_pTheOnlyOne = NULL;

StatusMgr::StatusMgr()
{
}

StatusMgr* StatusMgr::get()
{
    if (s_pTheOnlyOne == NULL)
    {
        s_pTheOnlyOne = new StatusMgr();
        s_pTheOnlyOne->update();
    }

    return s_pTheOnlyOne;
}

size_t StatusMgr::update()
{
#ifdef FAKE_GRAPHICS_CARD
    Status status = Status();

    status.update();
    status.data.index = 0;
    this->statuses.push_back(status);

    status.update();
    status.data.index = 1;
    this->statuses.push_back(status);

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
        Status status = Status();
        status.update(&(ADL::get()->mpAdapterInfo[i]));

        memset(pClock, 0, sizeof(ADLAdapterODClockInfo));
        if (SAFE_CALL(ADL::get()->ADL_Display_ODClockInfo_Get)(i, pClock) == ADL_OK)
        {
            status.data.gpuClock = pClock->sEngineClock.iCurrentClock;
            status.data.memoryClock = pClock->sMemoryClock.iCurrentClock;
        }
        
        memset(pActivity, 0, sizeof(ADLPMActivity));
        if (SAFE_CALL(ADL::get()->ADL_Overdrive5_CurrentActivity_Get)(i, pActivity) == ADL_OK)
        {
            status.data.memoryClock = pActivity->iMemoryClock;
            status.data.gpuClock = pActivity->iEngineClock;
            status.data.gpuUsage = pActivity->iActivityPercent;
            status.data.gpuVolt = pActivity->iVddc;
        }

        int t = 0;
        memset(pTemperature, 0, sizeof(ADLTemperature));
        if (SAFE_CALL(ADL::get()->ADL_Overdrive5_Temperature_Get)(i, 0, pTemperature) == ADL_OK)
        {
            status.data.gpuTemperature = pTemperature->iTemperature;
        }
        else if (SAFE_CALL(ADL::get()->ADL_Overdrive6_Temperature_Get)(i, &t))
        {
            status.data.gpuTemperature = t;
        }

        memset(pCurrentStatus, 0, sizeof(ADLOD6CurrentStatus));
        if (SAFE_CALL(ADL::get()->ADL_Overdrive6_CurrentStatus_Get)(i, pCurrentStatus) == ADL_OK)
        {
            status.data.gpuUsage = pCurrentStatus->iActivityPercent;
        }

        memset(pFan, 0, sizeof(ADLFanSpeedValue));
        memset(pFanOD6, 0, sizeof(ADLOD6FanSpeedInfo));
        if (SAFE_CALL(ADL::get()->ADL_Overdrive5_FanSpeed_Get)(i, 0, pFan) == ADL_OK)
        {
            status.data.fanDuty = pFan->iFanSpeed;
            status.data.fanSpeed = pFan->iFanSpeed;
        }
        else if (SAFE_CALL(ADL::get()->ADL_Overdrive6_FanSpeed_Get)(i, pFanOD6) == ADL_OK)
        {
            status.data.fanDuty = pFanOD6->iFanSpeedPercent;
            status.data.fanSpeed = pFanOD6->iFanSpeedRPM;
        }

        this->statuses.push_back(status);
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

size_t StatusMgr::getCount() const
{
    return this->statuses.size();
}

Status& StatusMgr::getStatus(int index)
{
    return this->statuses[index];
}