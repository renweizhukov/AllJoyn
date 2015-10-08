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

// AboutClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MySessionListener.h"
#include "MyAboutListener.h"

using namespace std;
using namespace ajn;

static volatile sig_atomic_t s_interrupt = false;

static void CDECL_CALL SigIntHandler(int sig) 
{
    QCC_UNUSED(sig);
    s_interrupt = true;
}

// The interface name should be the only thing required to find and form a
// connection between the service and the client using the about feature.
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
    unique_ptr<BusAttachment> bus(new BusAttachment("About Client Demo", true));
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

    MyAboutListener aboutListener(bus.get(), INTERFACE_NAME);
    cout << "[STEP]: Create aboutListener." << endl;

    bus->RegisterAboutListener(aboutListener);
    cout << "[STEP]: Register aboutListener to the bus." << endl;

    cout << "[STEP]: Calling WhoImplements." << endl;
    const char* interfaces[] = { INTERFACE_NAME };
    status = bus->WhoImplements(interfaces, sizeof(interfaces) / sizeof(interfaces[0]));
    if (status == ER_OK) 
    {
        cout << "[STEP]: WhoImplements called." << endl;
    } 
    else 
    {
        cout << "[ERROR]: WhoImplements failed with status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
        return 1;
    }

    cout << "[STEP]: Perform the service asynchronously until the user signals for an exit." << endl;
    while (s_interrupt == false) 
    {
        Sleep(100);
    }

    bus->UnregisterAboutListener(aboutListener);
    cout << "[STEP]: Unregister aboutListener to the bus." << endl;

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