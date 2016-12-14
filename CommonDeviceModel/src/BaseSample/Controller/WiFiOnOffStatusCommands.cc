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

#include <cstdlib>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>
#include "WiFiOnOffStatusCommands.h"
#include "WiFiOnOffStatusIntfControllerImpl.h"
#include "ControllerSample.h"

WiFiOnOffStatusListener::WiFiOnOffStatusListener()
{
}

WiFiOnOffStatusListener::~WiFiOnOffStatusListener()
{
}

void WiFiOnOffStatusListener::OnIsOnChanged(const qcc::String& objectPath, const bool value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "IsOn: " << value << endl;
}

void WiFiOnOffStatusListener::OnResponseGetIsOn(QStatus status, const qcc::String& objectPath, const bool value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "IsOn: " << value << endl;
}

WiFiOnOffStatusCommands::WiFiOnOffStatusCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath): 
    InterfaceCommands(sample, info, objectPath),
    m_intfController(NULL),
    m_vendorDefinedIntfType(UNDEFINED_INTERFACE)
{
}

WiFiOnOffStatusCommands::~WiFiOnOffStatusCommands()
{
    // The raw pointer m_intfController will be deleted in the destructor of CdmProxyBusObject when the map 
    // m_cdmInterfacesMap is destroyed. 
}

void WiFiOnOffStatusCommands::Init()
{
    if (!m_intfController) {
        // This is a vendor-defined interface, so we need to register it before creating it, which essentially add 
        // the vendor-defined interface to the map InterfaceTypesMap defined in alljoyn/services/cdm/cpp/src/interfaces/CdmInterface.cc.
        m_vendorDefinedIntfType = m_sample->RegisterVendorDefinedInterface("com.smartconn.SmartToys.Operation.WiFiOnOffStatus", static_cast<CreateIntfControllerFptr>(&WiFiOnOffStatusIntfControllerImpl::CreateInterface));
    
        CdmInterface* cdmInterface = m_sample->CreateInterface(m_vendorDefinedIntfType, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<WiFiOnOffStatusIntfController*>(cdmInterface);
    }

    RegisterCommand(&WiFiOnOffStatusCommands::OnCmdOnOffStatus, "wifionoff", "Current WiFi IsOn Status");

    PrintCommands();
}

void WiFiOnOffStatusCommands::OnCmdOnOffStatus(Commands* commands, std::string& cmd)
{
    WiFiOnOffStatusIntfController* intfController = static_cast<WiFiOnOffStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface does not exist." << endl;
        return;
    }

    intfController->GetIsOn();
}

