#pragma once

// specifies if we are using faked graphics card data
//#define FAKE_GRAPHICS_CARD

// dll export symbols
#if defined(LINUX)
    #define EXPORT          __attribute__ ((visibility("default")))
    #define LOCAL           __attribute__((visibility("hidden")))
#else
    #if defined(DATAMODEL_EXPORTS)	
        #define EXPORT      __declspec(dllexport)
    #else
        #define EXPORT      __declspec(dllimport)
    #endif
#endif

// function pointer safe check
#define SAFE_CALL(x)    (x) != NULL && (x)