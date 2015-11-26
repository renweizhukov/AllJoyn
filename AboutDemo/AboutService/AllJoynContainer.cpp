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

#include "stdafx.h"
#include "MySessionPortListener.h"
#include "MyBusObject.h"
#include "AboutServiceCommands.h"
#include "AllJoynContainer.h"

using namespace std;
using namespace ajn;

const char* AllJoynContainer::sc_interfaceName = "com.smartconn.about.sample.interface.string";
const SessionPort AllJoynContainer::sc_assignedSessionPort = 900;

AllJoynContainer::AllJoynContainer(void) : 
    m_state(AllJoynContainerState::Uninitialized),
    m_allJoynInited(false),
    m_allJoynRouterInited(false),
    m_allJoynApiCallProcessing(false)
{

}


AllJoynContainer::~AllJoynContainer(void)
{

}

void AllJoynContainer::SetState(AllJoynContainerState nextState)
{
    cout << "[INFO]: currState = " << as_integer(m_state) << ", nextState = " << as_integer(nextState)
        << "." << endl;

    switch (m_state)
    {
    case AllJoynContainerState::Uninitialized:
        if (nextState == AllJoynContainerState::Initialized)
        {
            m_state = nextState;
        }
        else
        {
            cout << "[ERROR]: Invalid state transition." << endl;
        }

        break;

    case AllJoynContainerState::Initialized:
        if ((nextState == AllJoynContainerState::Running) || 
            (nextState == AllJoynContainerState::Uninitialized))
        {
            m_state = nextState;
        }
        else
        {
            cout << "[ERROR]: Invalid state transition." << endl;
        }

        break;

    case AllJoynContainerState::Running:
        if ((nextState == AllJoynContainerState::Initialized) || 
            (nextState == AllJoynContainerState::Uninitialized))
        {
            m_state = nextState;
        }
        else
        {
            cout << "[ERROR]: Invalid state transition." << endl;
        }

        break;

    default:
        cout << "[ERROR]: Invalid current state." << endl;
        break;
    }
}

void AllJoynContainer::Init(void)
{
    if (m_state != AllJoynContainerState::Uninitialized)
    {
        cout << "[ERROR]: currState (" << as_integer(m_state) <<") is not Uninitialized." << endl;
        return;
    }

    cout << "[STEP]: Initializing AllJoyn." << endl;
    QStatus status = AllJoynInit();
    if (status == ER_OK) 
    {
        m_allJoynInited = true;
        cout << "[STEP]: Initialized AllJoyn." << endl;    
    }
    else
    {
        cout << "[ERROR]: Failed to initialize AllJoyn (status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
        return;
    }

    cout << "[STEP]: Initializing AllJoyn router." << endl;
    status = AllJoynRouterInit();
    if (status == ER_OK)
    {
        m_allJoynRouterInited = true;
        cout << "[STEP]: Initialized AllJoyn router." << endl;    
    }
    else
    {
        cout << "[ERROR]: Failed to initialize AllJoyn router (status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
        return;
    }

    cout << "[STEP]: Starting BusAttachment." << endl;
    m_bus.reset(new BusAttachment("About Client Demo", true, 8));
    status = m_bus->Start();
    if (status == ER_OK)
    {
        cout << "[STEP]: Succeeded starting BusAttachment." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to start BusAttachment (status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
        return;
    }

    cout << "[STEP]: Connecting BusAttachment to router node." << endl;
    status = m_bus->Connect();
    if (status == ER_OK) 
    {
        cout << "[STEP]: Connected BusAttachment to router node (BusName " 
            << m_bus->GetUniqueName().c_str() << ")." << endl;
    } 
    else 
    {
        cout << "[ERROR]: Failed to connect BusAttachment to router node (status = 0x" 
            << hex << status << " = " << QCC_StatusText(status) << ")." << endl;
        return;
    }

    cout << "[STEP] Binding SessionPort = " << sc_assignedSessionPort << "." << endl;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    SessionPort sessionPort = sc_assignedSessionPort;
    m_sessionPortListener.reset(new MySessionPortListener(sc_assignedSessionPort));

    status = m_bus->BindSessionPort(sessionPort, opts, *m_sessionPortListener);
    if (status == ER_OK)
    {
        cout << "[STEP]: Bound SessionPort." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to bind Session Port (status = 0x" 
            << hex << status << " = " << QCC_StatusText(status) << ")." << endl;
        return;
    }

    InitAboutDataAndObj();

    cout << "[STEP]: Create BusObject." << endl;
    m_busObject.reset(new MyBusObject(*m_bus, this, "/demo/path", sc_interfaceName));

    SetState(AllJoynContainerState::Initialized);
}

void AllJoynContainer::DeInit(void)
{
    if (m_state == AllJoynContainerState::Uninitialized)
    {
        cout << "[INFO]: currState is already Uninitialized." << endl;
        return;
    }

    // Stop the About Service if it is still running.
    Stop();

    cout << "[STEP]: Destroy AboutObj and AboutData." << endl;
    m_aboutObj.reset();
    m_aboutData.reset();

    cout << "[STEP]: Destroy BusObject." << endl;
    m_busObject.reset();

    // Clean up the Bus Attachment.
    QStatus status = ER_OK;
    if (m_bus != nullptr)
    {
        cout << "[STEP] Unbinding SessionPort = " << sc_assignedSessionPort << "." << endl;
        SessionPort sessionPort = sc_assignedSessionPort;

        status = m_bus->UnbindSessionPort(sessionPort);
        if (status == ER_OK)
        {
            cout << "[STEP]: Unbound SessionPort." << endl;
            m_sessionPortListener.reset();
        }
        else
        {
            cout << "[ERROR]: Failed to unbind Session Port (status = 0x" 
                << hex << status << " = " << QCC_StatusText(status) << ")." << endl;
            return;
        }

        cout << "[STEP]: Disconnecting BusAttachment to router node." << endl;
        status = m_bus->Disconnect();
        if (status == ER_OK) 
        {
            cout << "[STEP]: Disconnected BusAttachment to router node (BusName " 
                << m_bus->GetUniqueName().c_str() << ")." << endl;
        } 
        else 
        {
            cout << "[ERROR]: Failed to disconnect BusAttachment to router node (status = 0x" 
                << hex << status << " = " << QCC_StatusText(status) << ")." << endl;
            return;
        }

        cout << "[STEP]: Stopping BusAttachment." << endl;
        status = m_bus->Stop();
        if (status == ER_OK)
        {
            cout << "[STEP]: Succeeded stopping BusAttachment." << endl;
        }
        else
        {
            cout << "[ERROR]: Failed to stop BusAttachment (status = 0x" << hex << status 
                << " = " << QCC_StatusText(status) << ")." << endl;
            return;
        }

        cout << "[STEP]: Waiting for BusAttachment to be stopped." << endl;
        status = m_bus->Join();
        if (status == ER_OK)
        {
            cout << "[STEP]: BusAttachment is stopped." << endl;
            m_bus.reset();
        }
        else
        {
            cout << "[ERROR]: Failed to wait for BusAttachment to be stopped (status = 0x" << hex << status 
                << " = " << QCC_StatusText(status) << ")." << endl;
            return;
        }
    }

    if (m_allJoynRouterInited)
    {
        cout << "[STEP]: Shutting down AllJoyn router." << endl;
        status = AllJoynRouterShutdown();
        if (status == ER_OK)
        {
            cout << "[STEP]: Shut down AllJoyn router." << endl;
        }
        else
        {
            cout << "[ERROR]: Failed to shut down AllJoyn router (status = 0x" << hex << status 
                << " = " << QCC_StatusText(status) << ")." << endl;
        }
    }

    if (m_allJoynInited)
    {
        cout << "[STEP]: Shutting down AllJoyn." << endl;
        status = AllJoynShutdown();
        if (status == ER_OK)
        {
            cout << "[STEP]: Shut down AllJoyn." << endl;
        }
        else
        {
            cout << "[ERROR]: Failed to shut down AllJoyn (status = 0x" << hex << status 
                << " = " << QCC_StatusText(status) << ")." << endl;
        }
    }

    SetState(AllJoynContainerState::Uninitialized);
}

void AllJoynContainer::InitAboutDataAndObj(void)
{
    cout << "[STEP]: Setting up m_aboutData->" << endl;
    m_aboutData.reset(new AboutData("en"));
    // AppId is a 128bit uuid
    uint8_t appId[] = { 0x43, 0x2c, 0x74, 0xcf,
                        0x52, 0x87, 0x41, 0xc7,
                        0xb2, 0x19, 0x4e, 0xf0,
                        0x5b, 0xd6, 0x71, 0x3b };
    QStatus status = m_aboutData->SetAppId(appId, 16);
    status = m_aboutData->SetDeviceName("SmartConn About Service");
    // DeviceId is a string encoded 128bit UUID
    status = m_aboutData->SetDeviceId("e4cbac5f-67f1-4a10-b803-9f0cd2e03359");
    status = m_aboutData->SetAppName("Application");
    status = m_aboutData->SetManufacturer("SmartConn");
    status = m_aboutData->SetModelNumber("001");
    status = m_aboutData->SetDescription("SmartConn is awesome");
    status = m_aboutData->SetDateOfManufacture("2015-10-03");
    status = m_aboutData->SetSoftwareVersion("0.0.1");
    status = m_aboutData->SetHardwareVersion("0.0.1");
    status = m_aboutData->SetSupportUrl("http://www.smartconn.global");

    if (m_aboutData->IsValid()) 
    {
        cout << "[STEP]: Set up m_aboutData." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to set up m_aboutData." << endl;
        return;
    }

    string iface = "<node>"
                   "<interface name='" + string(sc_interfaceName) + "'>"
                   "  <method name='Echo'>"
                   "    <arg name='inputString' type='s' direction='in' />"
                   "    <arg name='outputString' type='s' direction='out' />"
                   "  </method>"
                   "</interface>"
                   "</node>";

    cout << "[STEP]: Creating the interface from xml." << endl;
    status = m_bus->CreateInterfacesFromXml(iface.c_str());
    if (status == ER_OK) 
    {
        cout << "[STEP]: Created the interface from xml." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to parse the xml interface definition (status = 0x" 
            << hex << status << " = " << QCC_StatusText(status) << ")." << endl;
        return;
    }

    cout << "[STEP]: Create AboutObj." << endl;
    m_aboutObj.reset(new AboutObj(*m_bus));
}

void AllJoynContainer::Start(void)
{
    cout << "[STEP]: Registering BusObject." << endl;
    QStatus status = m_bus->RegisterBusObject(*m_busObject);
    if (status == ER_OK) 
    {
        cout << "[STEP]: Registered BusObject." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to register BusObject (status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
        return;
    }

    cout << "[STEP]: Announcing." << endl;
    status = m_aboutObj->Announce(sc_assignedSessionPort, *m_aboutData);
    if (status == ER_OK) 
    {
        cout << "[STEP]: Announced." << endl;
    } 
    else 
    {
        cout << "[ERROR]: Failed to announce (status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
        return;
    }

    SetState(AllJoynContainerState::Running);
}

void AllJoynContainer::Stop(void)
{
    {
        unique_lock<mutex> lk(m_mut);

        // If there is a pending AllJoyn API call, wait for the call to complete and 
        // then stop the About Service.
        m_allJoynApiCallDone.wait(lk, [this](){ return !m_allJoynApiCallProcessing; });
    }

    cout << "[STEP]: Unannouncing." << endl;
    QStatus status = m_aboutObj->Unannounce();
    if (status == ER_OK) 
    {
        cout << "[STEP]: Unannounced." << endl;
    } 
    else 
    {
        cout << "[ERROR]: Failed to unannounce (status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
        return;
    }

    cout << "[STEP]: Unregister BusObject." << endl;
    m_bus->UnregisterBusObject(*m_busObject);

    SetState(AllJoynContainerState::Initialized);
}

void AllJoynContainer::SetAllJoynApiCallProcessing(bool allJoynApiCallProcessing)
{
    lock_guard<mutex> lk(m_mut);

    m_allJoynApiCallProcessing = allJoynApiCallProcessing;
    if (!m_allJoynApiCallProcessing)
    {
        m_allJoynApiCallDone.notify_one();
    }
}

bool AllJoynContainer::IsCommandValid(AboutServiceCommands command) const
{
    switch (m_state)
    {
    case AllJoynContainerState::Uninitialized:
        return ((command == AboutServiceCommands::Init) || 
            (command == AboutServiceCommands::Exit));

    case AllJoynContainerState::Initialized:
        return ((command == AboutServiceCommands::Start) || 
            (command == AboutServiceCommands::Exit));

    case AllJoynContainerState::Running:
        return ((command == AboutServiceCommands::Stop) || 
            (command == AboutServiceCommands::Exit));

    default:
        return false;
    }
}