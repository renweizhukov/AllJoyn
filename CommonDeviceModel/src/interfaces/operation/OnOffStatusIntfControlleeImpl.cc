/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfControlleeListener.h>

#include "OnOffStatusIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* OnOffStatusIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new OnOffStatusIntfControlleeImpl(busAttachment, dynamic_cast<OnOffStatusIntfControlleeListener&>(listener), cdmBusObject);
}

OnOffStatusIntfControlleeImpl::OnOffStatusIntfControlleeImpl(BusAttachment& busAttachment, OnOffStatusIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    //
    // Add by hand the initialization of m_isOn.
    //
    m_isOn(false)
{
}

OnOffStatusIntfControlleeImpl::~OnOffStatusIntfControlleeImpl()
{
}

QStatus OnOffStatusIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();
    
    // This interface doesn't have any method, so there is no need to add any method handler.

    return status;
}

QStatus OnOffStatusIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            //
            // Add by hand the implementation using OnOffStatusIntfControlleeListener.
            //
            if (!(s_prop_IsOn.compare(propName))) {
                bool value = false;
                // Try getting the latest actual value from the device.
                status = m_interfaceListener.OnGetIsOn(value);
                if (status != ER_OK) {
                    value = GetIsOn();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetIsOn(value); // update the value in OnOffStatusIntfControllee.
                }

                val.typeId = ALLJOYN_BOOLEAN;
                val.v_bool = value;
            }
        } else {
            //
            // Add by hand the implementation using OnOffStatusIntfControlleeListener.
            //
            if (!(s_prop_IsOn.compare(propName))) {
                const bool value = GetIsOn();
                val.typeId = ALLJOYN_BOOLEAN;
                val.v_bool = value;
            }
       }
    }

    return status;
}

QStatus OnOffStatusIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    //
    // Add the implementation.
    //
    if (!(s_prop_IsOn.compare(propName))) {

        if (val.typeId != ALLJOYN_UINT16) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }

        status = ER_BUS_PROPERTY_VALUE_NOT_SET;

    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }     

    return status;
}

void OnOffStatusIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            MessageReceiver::MethodHandler handler = it->second;
            (this->*handler)(member, msg);
            isFound = true;
            break;
        }
    }

    if (!isFound) {
        status = ER_BUS_METHOD_CALL_ABORTED;
        QCC_LogError(status, ("%s: could not found method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}

//
// Add the Property Get and Set methods by hand.
//
const bool OnOffStatusIntfControlleeImpl::GetIsOn() const
{ 
    return m_isOn; 
}

QStatus OnOffStatusIntfControlleeImpl::SetIsOn(const bool value)
{
    QStatus status = ER_OK;

    if (m_isOn != value) {
        m_isOn = value;
        MsgArg val;
        val.typeId = ALLJOYN_BOOLEAN;
        val.v_bool = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_IsOn.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    }

    return status;
}

} //namespace services
} //namespace ajn
