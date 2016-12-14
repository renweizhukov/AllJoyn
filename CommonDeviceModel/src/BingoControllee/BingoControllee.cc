/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <iostream>
#include <map>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/cdm/DeviceTypeDescription.h>

//---------------------------------------- BaseSample common headers ----------------------------------------

#include "ControlleeSample.h"
#include "ControlleeCommands.h"

//--------------------------------------- BaseSample listener headers ---------------------------------------
#include "OffControlListener.h"
#include "OnOffStatusListener.h"
#include "WiFiOnOffStatusListener.h"

//--------------------------------------- Interface controllee headers ---------------------------------------
#include <alljoyn/cdm/interfaces/operation/OffControlIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfControllee.h>
#include "alljoyn/cdm/vendor_defined/WiFiOnOffStatusIntfControllee.h"
#include "WiFiOnOffStatusIntfControlleeImpl.h"

using namespace std;
using namespace qcc;

class BingoControllee : public ControlleeSample
{
  private:
    OffControlListener m_offControlListener;
    OnOffStatusListener m_onOffStatusListener;
    WiFiOnOffStatusListener m_wifiOnOffStatusListener;

    OffControlIntfControllee* m_offControlIntfControllee;
    OnOffStatusIntfControllee* m_onOffStatusIntfControllee;
    WiFiOnOffStatusIntfControllee* m_wifiOnOffStatusIntfControllee;
    
    CdmInterfaceType m_wifiOnOffStatusIntfType;
    
  public:
    BingoControllee(BusAttachment* bus, CdmAboutData* aboutData);
    virtual ~BingoControllee();
    void CreateInterfaces();
    void SetInitialProperty();
};

BingoControllee::BingoControllee(BusAttachment* bus, CdmAboutData* aboutData) :
    ControlleeSample(bus, aboutData), 
    m_offControlIntfControllee(NULL),
    m_onOffStatusIntfControllee(NULL),
    m_wifiOnOffStatusIntfControllee(NULL)
{
}

BingoControllee::~BingoControllee()
{
}

void BingoControllee::CreateInterfaces()
{
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }
    
    CdmInterface* intf = NULL;
    intf = cdmControllee->CreateInterface(OFF_CONTROL_INTERFACE, "/Cdm/BingoControllee", m_offControlListener);
    m_offControlIntfControllee = static_cast<OffControlIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(ON_OFF_STATUS_INTERFACE, "/Cdm/BingoControllee", m_onOffStatusListener);
    m_onOffStatusIntfControllee = static_cast<OnOffStatusIntfControllee*>(intf);

    // This is a vendor-defined interface, so we need to register it before creating it, which essentially add 
    // the vendor-defined interface to the map InterfaceTypesMap defined in alljoyn/services/cdm/cpp/src/interfaces/CdmInterface.cc.
    m_wifiOnOffStatusIntfType = cdmControllee->RegisterVendorDefinedInterface("com.smartconn.SmartToys.Operation.WiFiOnOffStatus", static_cast<CreateIntfControlleeFptr>(&WiFiOnOffStatusIntfControlleeImpl::CreateInterface));
    intf = cdmControllee->CreateInterface(m_wifiOnOffStatusIntfType, "/Cdm/BingoControllee", m_wifiOnOffStatusListener);
    m_wifiOnOffStatusIntfControllee = static_cast<WiFiOnOffStatusIntfControllee*>(intf);
}

void BingoControllee::SetInitialProperty()
{
    if (m_onOffStatusIntfControllee) {
        bool onoff = true;
        m_wifiOnOffStatusIntfControllee->SetIsOn(onoff);
    }

    if (m_wifiOnOffStatusIntfControllee) {
        bool wifiOnOff = true;
        m_wifiOnOffStatusIntfControllee->SetIsOn(wifiOnOff);
    }
}

QStatus FillAboutData(CdmAboutData* aboutData)
{
    String const defaultLanguage = "en";
    String device_id = "deviceID";
    String app_id = "554b50b1-d4f3-4479-9b7c-6c33bdcca852";
    String app_name = "BingoControllee";
    map<String, String> deviceNames;
    deviceNames.insert(pair<String, String>("en", "BingoControllee"));

    if (!app_id.empty()) {
        aboutData->SetAppId(app_id.c_str());
    }

    if (device_id != "") {
        aboutData->SetDeviceId(device_id.c_str());
    }

    vector<String> languages(1);
    languages[0] = "en";

    for (size_t i = 0; i < languages.size(); i++) {
        aboutData->SetSupportedLanguage(languages[i].c_str());
    }

    if (defaultLanguage != "") {
        aboutData->SetDefaultLanguage(defaultLanguage.c_str());
    }

    if (app_name != "") {
        aboutData->SetAppName(app_name.c_str(), languages[0].c_str());
    }

    aboutData->SetModelNumber("12345"); // TODO
    aboutData->SetDateOfManufacture("12/01/2016"); // TODO
    aboutData->SetSoftwareVersion("1.0.0"); // TODO
    aboutData->SetHardwareVersion("R1B"); // TODO

    map<String, String>::const_iterator iter = deviceNames.find(languages[0]);
    if (iter != deviceNames.end()) {
        aboutData->SetDeviceName(iter->second.c_str(), languages[0].c_str());
    } else {
        aboutData->SetDeviceName("My device name", "en");
    }

    aboutData->SetDescription("This is a Bingo Controllee Application", "en");
    aboutData->SetManufacturer("Umii Tech.", "en");
    aboutData->SetSupportUrl("http://www.bbcloud.com");

    // CDM custom metadata fields
    aboutData->SetCountryOfProduction("China", "en");
    aboutData->SetCorporateBrand("Umii", "en");
    aboutData->SetProductBrand("BingoControllee", "en");
    aboutData->SetLocation("Indoors", "en"); // TODO

    DeviceTypeDescription description;
    description.AddDeviceType(OTHER, "/Cdm/BingoControllee");
    aboutData->SetDeviceTypeDescription(&description);

    if (!aboutData->IsValid()) {
        return ER_FAIL;
    }

    return ER_OK;
}

int main()
{
    if (AllJoynInit() != ER_OK) {
        printf("FAILED to init alljoyn\n");
        exit(1);
    }
#ifdef ROUTER
    if (AllJoynRouterInit() != ER_OK) {
        AllJoynShutdown();
        printf("FAILED to init router\n");
        exit(1);
    }
#endif
    printf("AllJoyn Library version: %s\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s\n", ajn::GetBuildInfo());
    QCC_SetLogLevels("CDM_MODULE_LOG_NAME=15;");

    BusAttachment* bus = new BusAttachment("BingoControllee", true);
    if (!bus) {
        printf("BusAttachment creation failed.\n");
        exit(1);
    }

    CdmAboutData* aboutData = new CdmAboutData();
    if (!aboutData) {
        printf("AboutData creation failed.\n");
        delete bus;
        exit(1);
    }
    FillAboutData(aboutData);

    QStatus status = bus->Start();
    if (ER_OK != status) {
        printf("BusAttachment::Start failed (%s)\n", QCC_StatusText(status));
        delete bus;
        delete aboutData;
        exit(1);
    }

    status = bus->Connect();
    if (ER_OK != status) {
        printf("BusAttachment::Connect failed (%s)\n", QCC_StatusText(status));
        bus->Stop();
        bus->Join();
        delete bus;
        delete aboutData;
        exit(1);
    }

    BingoControllee controllee(bus, aboutData);

    controllee.Startup();

    controllee.Shutdown();

    if (bus) {
        bus->Disconnect();
        bus->Stop();
        bus->Join();

        delete bus;
    }

    if (aboutData) {
        delete aboutData;
    }

#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();

    return 0;
}
