#pragma once

#include "PerfOverTime.h"

namespace Dm{

    // PerfOverTimeMgr is the manager of PerfOverTime.
    // It is a singleton class.
    class EXPORT PerfOverTimeMgr
    {
    public:
        std::vector<PerfOverTime> perfs;

        PerfOverTimeMgr();
        
        // singleton function
        static PerfOverTimeMgr* get();

        size_t update();

        PerfOverTime& getPerfOverTime(int index);
        size_t getCount() const;

    private:
        static PerfOverTimeMgr* s_pTheOnlyOne;

        // forbidden constructors
        PerfOverTimeMgr(PerfOverTimeMgr&);
        PerfOverTimeMgr& operator =(PerfOverTimeMgr&);
    };

} // end of namespace Dm