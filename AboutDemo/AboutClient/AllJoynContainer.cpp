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
#include "MySessionListener.h"
#include "MyAboutListener.h"
#include "AboutClientCommands.h"
#include "AllJoynContainer.h"

using namespace std;
using namespace ajn;

const char* AllJoynContainer::sc_interfaceName = "com.smartconn.about.sample.interface.string";

AllJoynContainer::AllJoynContainer(void) :
    m_state(AllJoynContainerState::Uninitialized),
    m_allJoynInited(false),
    m_allJoynRouterInited(false),
    m_aboutListenerRegistered(false)
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
        if ((nextState == AllJoynContainerState::Joined) || 
            (nextState == AllJoynContainerState::Uninitialized))
        {
            m_state = nextState;
        }
        else
        {
            cout << "[ERROR]: Invalid state transition." << endl;
        }

        break;

    case AllJoynContainerState::Joined:
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
    lock_guard<mutex> lk(m_mut);

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
    m_bus.reset(new BusAttachment("About Client Demo", true));
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

    m_aboutListener.reset(new MyAboutListener(m_bus.get(), this, sc_interfaceName));
    cout << "[STEP]: Create aboutListener." << endl;

    m_bus->RegisterAboutListener(*m_aboutListener);
    m_aboutListenerRegistered = true;
    cout << "[STEP]: Register aboutListener to the bus." << endl;

    SetState(AllJoynContainerState::Initialized);
}

void AllJoynContainer::DeInit(void)
{
    lock_guard<mutex> lk(m_mut);

    if (m_state == AllJoynContainerState::Uninitialized)
    {
        cout << "[INFO]: currState is already Uninitialized." << endl;
        return;
    }

    QStatus status = ER_OK;
    if (m_state == AllJoynContainerState::Joined)
    {
        cout << "[STEP]: Calling CancelWhoImplements." << endl;
        status = m_bus->CancelWhoImplements(sc_interfaceName);
        if (status == ER_OK) 
        {
            cout << "[STEP]: CancelWhoImplements called." << endl;
        } 
        else 
        {
            cout << "[ERROR]: CancelWhoImplements failed with status = 0x" << hex << status 
                << " = " << QCC_StatusText(status) << ")." << endl;
        }
    }

    m_proxyBusObject.reset();
    cout << "[STEP]: Destroy the Proxy Bus Object." << endl;

    if (m_aboutListenerRegistered)
    {
        m_bus->UnregisterAboutListener(*m_aboutListener);
        cout << "[STEP]: Unregister aboutListener to the bus." << endl;
    }

    m_aboutListener.reset();
    cout << "[STEP]: Destroy the aboutListener." << endl;

    cout << "[STEP]: Disconnecting BusAttachment to router node." << endl;
    status = m_bus->Disconnect();
    if (status == ER_OK) 
    {
        cout << "[STEP]: Disconnected BusAttachment from router node (BusName " 
            << m_bus->GetUniqueName().c_str() << ")." << endl;
    } 
    else 
    {
        cout << "[ERROR]: Failed to disconnect BusAttachment from router node (status = 0x" 
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

void AllJoynContainer::Join(void)
{
    unique_lock<mutex> lk(m_mut);

    if (m_state != AllJoynContainerState::Initialized)
    {
        cout << "[ERROR]: currState (" << as_integer(m_state) <<") is not Initialized." << endl;
        return;
    }

    cout << "[STEP]: Calling WhoImplements. Start waiting for the announced signal for 60 seconds." << endl;
    QStatus status = m_bus->WhoImplements(sc_interfaceName);
    if (status == ER_OK) 
    {
        if (m_proxyBusObjectSet.wait_for(lk, chrono::seconds(60), 
                [this](){ return static_cast<bool>(m_proxyBusObject != nullptr); }) 
            == cv_status::timeout) 
        {
            cout << "[ERROR]: Either the AboutListener hasn't received any announced signal within 60 seconds" 
                " or the Proxy Bus Object is NULL." << endl;
            cout << "[STEP]: Calling CancelWhoImplements." << endl;
            status = m_bus->CancelWhoImplements(sc_interfaceName);
            if (status == ER_OK) 
            {
                cout << "[STEP]: CancelWhoImplements called." << endl;
            } 
            else 
            {
                cout << "[ERROR]: CancelWhoImplements failed with status = 0x" << hex << status 
                    << " = " << QCC_StatusText(status) << ")." << endl;
            }
            return;
        }

        cout << "[STEP]: WhoImplements called." << endl;
        cout << "[INFO]: ProxyBusObject created." << endl;

        SetState(AllJoynContainerState::Joined);
    } 
    else 
    {
        m_proxyBusObject.reset();
        cout << "[ERROR]: WhoImplements failed with status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
    }
}

void AllJoynContainer::Unjoin(void)
{
    lock_guard<mutex> lk(m_mut);

    if (m_state != AllJoynContainerState::Joined)
    {
        cout << "[ERROR]: currState (" << as_integer(m_state) <<") is not Joined." << endl;
        return;
    }

    cout << "[STEP]: Calling CancelWhoImplements." << endl;
    QStatus status = m_bus->CancelWhoImplements(sc_interfaceName);
    if (status == ER_OK) 
    {
        cout << "[STEP]: CancelWhoImplements called." << endl;
    } 
    else 
    {
        cout << "[ERROR]: CancelWhoImplements failed with status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
    }

    m_proxyBusObject.reset();
    SetState(AllJoynContainerState::Initialized);
}

void AllJoynContainer::SetProxyBusObject(unique_ptr<ProxyBusObject>& proxyBusObject)
{
    lock_guard<mutex> lk(m_mut);
    m_proxyBusObject = move(proxyBusObject);
    m_proxyBusObjectSet.notify_one();
}

void AllJoynContainer::MakeCall(void) const
{
    lock_guard<mutex> lk(m_mut);

    if (m_state != AllJoynContainerState::Joined)
    {
        cout << "[ERROR]: currState (" << as_integer(m_state) <<") is not Joined." << endl;
        return;
    }

    if (m_proxyBusObject == nullptr)
    {
        cout << "[ERROR]: ProxyBusObject is NULL." << endl;
        return;
    }

    QStatus status = m_proxyBusObject->IntrospectRemoteObject();
    if (status == ER_OK) 
    {
        cout << "[INFO]: Introspected remote object." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to introspect remote object" << " (status = 0x" 
            << hex << status << " = " << QCC_StatusText(status) << "." << endl;
    }

    MsgArg arg("s", "ECHO Echo echo...");
    Message replyMsg(*m_bus);
    status = m_proxyBusObject->MethodCall(sc_interfaceName, "Echo", &arg, 1, replyMsg);
    if (status == ER_OK) 
    {
        cout << "[INFO]: Called Echo method." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to call Echo method" << " (status = 0x" 
            << hex << status << " = " << QCC_StatusText(status) << "." << endl;
        return;
    }

    char* echoReply = nullptr;
    status = replyMsg->GetArg(0)->Get("s", &echoReply);
    if (status == ER_OK) 
    {
        cout << "[INFO]: Echo method reply: \""<< echoReply << "\"."<< endl;
    }
    else
    {
        cout << "[ERROR]: Failed to read Echo method reply" << " (status = 0x" 
            << hex << status << " = " << QCC_StatusText(status) << "." << endl;
    }
}

bool AllJoynContainer::IsCommandValid(AboutClientCommands command) const
{
    lock_guard<mutex> lk(m_mut);

    switch (m_state)
    {
    case AllJoynContainerState::Uninitialized:
        return ((command == AboutClientCommands::Init) || 
            (command == AboutClientCommands::Exit));

    case AllJoynContainerState::Initialized:
        return ((command == AboutClientCommands::Join) || 
            (command == AboutClientCommands::Exit));

    case AllJoynContainerState::Joined:
        return ((command == AboutClientCommands::Call) || 
            (command == AboutClientCommands::Exit));

    default:
        return false;
    }
}