#pragma once

#include "GpuSpec.h"

namespace Dm{

    // GpuSpecMgr is the manager of GpuSpec.
    // It is a singleton class.
    class EXPORT GpuSpecMgr
    {
    public:
        std::vector<GpuSpec> gpus;

        GpuSpecMgr();
        
        // singleton function
        static GpuSpecMgr* get();

        size_t update();

        GpuSpec& getGpuSpec(int index);
        size_t getCount() const;

    private:
        static GpuSpecMgr* s_pTheOnlyOne;

        // forbidden constructors
        GpuSpecMgr(GpuSpecMgr&);
        GpuSpecMgr& operator =(GpuSpecMgr&);
    };

} // end of namespace Dm