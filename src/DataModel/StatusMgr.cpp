
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
        }

        this->statuses.push_back(status);
    }

    free(pClock);
    free(pActivity);
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