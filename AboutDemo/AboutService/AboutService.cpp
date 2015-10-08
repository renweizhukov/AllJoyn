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

using namespace std;
using namespace ajn;

static volatile sig_atomic_t s_interrupt = false;

static void CDECL_CALL SigIntHandler(int sig)
{
    QCC_UNUSED(sig);
    cout << "Received an interrupt (possibly caused by Ctrl + C)." << endl;
    s_interrupt = true;
}

static const SessionPort ASSIGNED_SESSION_PORT = 900;
static const char* INTERFACE_NAME = "com.smartconn.about.sample.interface.string";

int _tmain(int argc, _TCHAR* argv[])
{
    QCC_UNUSED(argc);
    QCC_UNUSED(argv);

    cout << "[STEP]: Initializing AllJoyn." << endl;
    QStatus status = AllJoynInit();
    if (status == ER_OK) 
    {
        cout << "[STEP]: Initialized AllJoyn." << endl;    
    }
    else
    {
        cout << "[ERROR]: Failed to initialize AllJoyn (status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
        return 1;
    }

    cout << "[STEP]: Initializing AllJoyn router." << endl;
    status = AllJoynRouterInit();
    if (status == ER_OK)
    {
        cout << "[STEP]: Initialized AllJoyn router." << endl;    
    }
    else
    {
        cout << "[ERROR]: Failed to initialize AllJoyn router (status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
        return 1;
    }

    cout << "[STEP]: Install SIGINT handler so Ctrl + C deallocates memory properly." << endl;
    signal(SIGINT, SigIntHandler);

    cout << "[STEP]: Starting BusAttachment." << endl;
    unique_ptr<BusAttachment> bus(new BusAttachment("About Service Demo", true));
    status = bus->Start();
    if (status == ER_OK)
    {
        cout << "[STEP]: Started BusAttachment." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to start BusAttachment (status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
        return 1;
    }
    
    cout << "[STEP]: Connecting BusAttachment to router node." << endl;
    status = bus->Connect();
    if (status == ER_OK) 
    {
        cout << "[STEP]: Connected BusAttachment to router node (BusName " 
            << bus->GetUniqueName().c_str() << ")." << endl;
    } 
    else 
    {
        cout << "[ERROR]: Failed to connect BusAttachment to router node (status = 0x" 
            << hex << status << " = " << QCC_StatusText(status) << ")." << endl;
        return 1;
    }

    cout << "[STEP] Binding SessionPort = " << ASSIGNED_SESSION_PORT << "." << endl;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    SessionPort sessionPort = ASSIGNED_SESSION_PORT;
    MySessionPortListener sessionPortListener(ASSIGNED_SESSION_PORT);

    status = bus->BindSessionPort(sessionPort, opts, sessionPortListener);
    if (status == ER_OK)
    {
        cout << "[STEP]: Bound SessionPort." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to bind Session Port (status = 0x" 
            << hex << status << " = " << QCC_StatusText(status) << ")." << endl;
        return 1;
    }

    cout << "[STEP]: Setting up AboutData." << endl;
    AboutData aboutData("en");
    // AppId is a 128bit uuid
    uint8_t appId[] = { 0x43, 0x2c, 0x74, 0xcf,
                        0x52, 0x87, 0x41, 0xc7,
                        0xb2, 0x19, 0x4e, 0xf0,
                        0x5b, 0xd6, 0x71, 0x3b };
    status = aboutData.SetAppId(appId, 16);
    status = aboutData.SetDeviceName("SmartConn About Service");
    // DeviceId is a string encoded 128bit UUID
    status = aboutData.SetDeviceId("e4cbac5f-67f1-4a10-b803-9f0cd2e03359");
    status = aboutData.SetAppName("Application");
    status = aboutData.SetManufacturer("SmartConn");
    status = aboutData.SetModelNumber("001");
    status = aboutData.SetDescription("SmartConn is awesome");
    status = aboutData.SetDateOfManufacture("2015-10-03");
    status = aboutData.SetSoftwareVersion("0.0.1");
    status = aboutData.SetHardwareVersion("0.0.1");
    status = aboutData.SetSupportUrl("http://www.smartconn.com");

    if (aboutData.IsValid()) 
    {
        cout << "[STEP]: Set up AboutData." << endl;
    }
    else
    {
        cout << "[STEP]: Failed to set up AboutData." << endl;
        return 1;
    }

    string iface = "<node>"
                   "<interface name='" + string(INTERFACE_NAME) + "'>"
                   "  <method name='Echo'>"
                   "    <arg name='inputString' type='s' direction='in' />"
                   "    <arg name='outputString' type='s' direction='out' />"
                   "  </method>"
                   "</interface>"
                   "</node>";

    cout << "[STEP]: Creating the interface from xml." << endl;
    status = bus->CreateInterfacesFromXml(iface.c_str());
    if (status == ER_OK) 
    {
        cout << "[STEP]: Created the interface from xml." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to parse the xml interface definition (status = 0x" 
            << hex << status << " = " << QCC_StatusText(status) << ")." << endl;
        return 1;
    }

    cout << "[STEP]: Create BusObject." << endl;
    unique_ptr<MyBusObject> busObject(new MyBusObject(*bus, "/demo/path", INTERFACE_NAME));

    cout << "[STEP]: Registering BusObject." << endl;
    status = bus->RegisterBusObject(*busObject);
    if (status == ER_OK) 
    {
        cout << "[STEP]: Registered BusObject." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to register BusObject (status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
        return 1;
    }

    cout << "[STEP]: Create AboutObj." << endl;
    unique_ptr<AboutObj> aboutObj(new AboutObj(*bus));

    cout << "[STEP]: Announcing." << endl;
    status = aboutObj->Announce(sessionPort, aboutData);
    if (status == ER_OK) 
    {
        cout << "[STEP]: Announced." << endl;
    } 
    else 
    {
        cout << "[ERROR]: Failed to announce (status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
        return 1;
    }

    cout << "[STEP]: Keep waiting for About clients until the user signals for an exit." << endl;
    while (s_interrupt == false) 
    {
        Sleep(100);
    };

    aboutObj.reset();
    busObject.reset();
    bus.reset();

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

    return 0;
}