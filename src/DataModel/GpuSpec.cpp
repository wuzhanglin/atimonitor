
#include "GpuSpec.h"
#include <iostream>
#include "adl.h"
#include "RegistryUtil.h"

using namespace Dm;

GpuSpecData::GpuSpecData()
    : index(0)
    , name("AMD Radeon HD 7900 Series")
    , gpu("Tahiti")
    , revision("1.0")
    , releaseDate("Dec 22, 2011")
    , biosVersion("015.012.0000.004.000346")
    , deviceID("1002-6798")
    , subvendor("XFX")
    , busInterface("PCI-E 3.0 x16 @ 16 1.1")
    , memorySize(3072)
    , memoryType("GDDR5")
    , driverVersion("ATIUMDAG 89.1223.23")

    , rops(32)
    , busWidth(384)
    , bandwidth(302)
    , gpuClock(1125)
    , gpuDefaultClock(1125)
    , memoryClock(1575)
    , memoryDefaultClock(1575)
    , shaderClock(1000)
    , shaderDefaultClock(1000)
    , atiCrossFireEnabled(true)
{
}

void GpuSpec::print() const
{
#define PRINT_DATA(key) std::cout << std::endl << #key << ": " << this->data.key 
    std::cout << std::endl << "______________" << "GPU SPEC " << this->data.index << "_________________";
    PRINT_DATA(index);
    PRINT_DATA(name);
    PRINT_DATA(gpu);
    PRINT_DATA(revision);
    PRINT_DATA(releaseDate);
    PRINT_DATA(biosVersion);
    PRINT_DATA(deviceID);
    PRINT_DATA(subvendor);
    PRINT_DATA(busInterface);
    PRINT_DATA(memorySize);
    PRINT_DATA(memoryType);
    PRINT_DATA(driverVersion);

    PRINT_DATA(rops);
    PRINT_DATA(busWidth);
    PRINT_DATA(bandwidth);
    PRINT_DATA(gpuClock);
    PRINT_DATA(gpuDefaultClock);
    PRINT_DATA(memoryClock);
    PRINT_DATA(memoryDefaultClock);
    PRINT_DATA(shaderClock);
    PRINT_DATA(shaderDefaultClock);
    PRINT_DATA(atiCrossFireEnabled);
}

// utility function
// Extracts the "Device ID" from a "UDID" string.
// Usually, a "UDID" string looks like:
//     PCI_VEN_1002&DEV_95C4&SUBSYS_02541028&REV_00_4&13E82272&0&0008&02A
// and, the "Device ID" should be:
//     1002-95C4
static string ExtractDeviceId(const string udid)
{
    string id;
    if (udid.size() < 21)
        return id;

    string pci = udid.substr(8, 4);
    string dev = udid.substr(17, 4);
    id = pci + "-" + dev;
    return id;
}

void GpuSpec::update(const AdapterInfo* pAdpt/* = NULL*/)
{
#ifndef FAKE_GRAPHICS_CARD
    if (pAdpt == NULL)
        return;

    this->data.index = pAdpt->iAdapterIndex;
    this->data.name = pAdpt->strAdapterName;
    this->data.gpu = "";
    this->data.revision = "";
    this->data.releaseDate = "";
    this->data.biosVersion = "";
    this->data.deviceID = ExtractDeviceId(string(pAdpt->strUDID));
    this->data.subvendor = "XFX";
    this->data.busInterface = "";
    this->data.memorySize = 0;
    this->data.memoryType = "";
    this->data.driverVersion = pAdpt->strDriverPath;

    this->data.rops = 0;
    this->data.busWidth = 0;
    this->data.bandwidth = 0;
    this->data.gpuClock = 0;
    this->data.gpuDefaultClock = 0;
    this->data.memoryClock = 0;
    this->data.memoryDefaultClock = 0;
    this->data.shaderClock = 0;
    this->data.shaderDefaultClock = 0;
    this->data.atiCrossFireEnabled = false;

    // try to get the values for "Driver Version" from the Registry
    size_t i = this->data.driverVersion.find("System");
    size_t size = this->data.driverVersion.size();
    string path = this->data.driverVersion.substr(i, size - i);
    HKEY key;
    LONG r = RegOpenKeyEx(HKEY_LOCAL_MACHINE, path.c_str(), 0, KEY_READ, &key);
    if (r == ERROR_SUCCESS)
    {
        std::string provider, version, empty;
        GetStringRegKey(key, "ProviderName", provider, empty);
        GetStringRegKey(key, "DriverVersion", version, empty);
        this->data.driverVersion = provider + " " + version;
    }
#endif
}