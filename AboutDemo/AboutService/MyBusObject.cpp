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

MyBusObject::MyBusObject(
    BusAttachment& bus, 
    AllJoynContainer *pAllJoynContainer,
    const char* path, 
    const char* interfaceName) : 
    BusObject(path),
    m_allJoynContainer(pAllJoynContainer),
    m_interfaceName(interfaceName)
{
    QStatus status;
    const InterfaceDescription* iface = bus.GetInterface(m_interfaceName.c_str());
    assert(iface != nullptr);

    status = AddInterface(*iface, ANNOUNCED);
    if (status == ER_OK) 
    {
        cout << "[INFO]: Added " << m_interfaceName << " interface to the BusObject." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to add " << m_interfaceName << " interface to the BusObject (status = 0x" 
            << hex << status << " = " << QCC_StatusText(status) << ")."<< endl;
    }

    const MethodEntry methodEntries[] = {
        { iface->GetMember("Echo"), static_cast<MessageReceiver::MethodHandler>(&MyBusObject::Echo) }
    };
    AddMethodHandlers(methodEntries, sizeof(methodEntries) / sizeof(methodEntries[0]));
}

MyBusObject::~MyBusObject(void)
{

}

void MyBusObject::Echo(
    const InterfaceDescription::Member* member, 
    Message& msg) 
{
    QCC_UNUSED(member);

    m_allJoynContainer->SetAllJoynApiCallProcessing(true);

    cout << "[INFO]: Echo method called: " << msg->GetArg(0)->v_string.str << endl;
    const MsgArg* arg((msg->GetArg(0)));

    QStatus status = MethodReply(msg, arg, 1);
    if (status == ER_OK) 
    {
        cout << "[INFO]: Created MethodReply." << endl;
    }
    else
    {
        cout << "[ERROR]: Failed to created MethodReply (status = 0x" << hex << status 
            << " = " << QCC_StatusText(status) << ")." << endl;
    }

    m_allJoynContainer->SetAllJoynApiCallProcessing(false);
}