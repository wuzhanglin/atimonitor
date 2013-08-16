
#include "GpuSpec.h"
#include <iostream>
#include "adl.h"
#include "RegistryUtil.h"

using namespace Dm;

GpuSpecData::GpuSpecData()
    : index(0)
    , name("")
    , gpu("Tahiti") // hard coded
    , revision("1") // hard coded
    , releaseDate("22-Dec-11") // hard coded
    , biosVersion("")
    , deviceID("")
    , subvendor("XFX") // hard coded
    , busInterface("")
    , memorySize(0)
    , memoryType("")
    , driverVersion("")

    , rops(0)
    , busWidth(0)
    , bandwidth(0)
    , gpuClock(0)
    , gpuDefaultClock(0)
    , memoryClock(0)
    , memoryDefaultClock(0)
    , shaderClock(0)
    , shaderDefaultClock(0)
    , atiCrossFireEnabled(false)
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
#ifdef FAKE_GRAPHICS_CARD

    this->data.index = 0;
    this->data.name = "AMD Radeon HD 7900 Series";
    //this->data.gpu = "Tahiti"; // hard coded
    //this->data.revision = "1"; // hard coded
    //this->data.releaseDate = "22-Dec-11"; // hard coded
    this->data.biosVersion = "015.012.0000.004.000346";
    this->data.deviceID = "1002-6798";
    //this->data.subvendor = "XFX"; // hard coded
    this->data.busInterface = "PCI-E 3.0 x16 @ 16 1.1";
    this->data.memorySize = 3072;
    this->data.memoryType = "GDDR5";
    this->data.driverVersion = "ATIUMDAG 89.1223.23";

    this->data.rops = 32;
    this->data.busWidth = 384;
    this->data.bandwidth = 302;
    this->data.gpuClock = 1125;
    this->data.gpuDefaultClock = 1125;
    this->data.memoryClock = 1575;
    this->data.memoryDefaultClock = 1575;
    this->data.shaderClock = 1000;
    this->data.shaderDefaultClock = 1000;
    this->data.atiCrossFireEnabled = true;

#else

    if (pAdpt == NULL)
        return;

    this->data.index = pAdpt->iAdapterIndex;
    this->data.name = pAdpt->strAdapterName;
    //this->data.gpu = "Tahiti"; // hard coded
    //this->data.revision = "1"; // hard coded
    //this->data.releaseDate = "22-Dec-11"; // hard coded
    this->data.biosVersion = "";
    this->data.deviceID = ExtractDeviceId(string(pAdpt->strUDID));
    //this->data.subvendor = "XFX"; // hard coded
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