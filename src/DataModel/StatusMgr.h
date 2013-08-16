#pragma once

#include "Status.h"

namespace Dm{

    // StatusMgr is the manager of Status.
    // It is a singleton class.
    class EXPORT StatusMgr
    {
    public:
        std::vector<Status> statuses;

        StatusMgr();
        
        // singleton function
        static StatusMgr* get();

        size_t update();

        Status& getStatus(int index);
        size_t getCount() const;

    private:
        static StatusMgr* s_pTheOnlyOne;

        // forbidden constructors
        StatusMgr(StatusMgr&);
        StatusMgr& operator =(StatusMgr&);
    };

} // end of namespace Dm