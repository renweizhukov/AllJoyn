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

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
//
// Change by hand the include path of the vendor-defined header.
//
#include <alljoyn/cdm/vendor_defined/WiFiOnOffStatusIntfControllerListener.h>
#include "WiFiOnOffStatusIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* WiFiOnOffStatusIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new WiFiOnOffStatusIntfControllerImpl(busAttachment, dynamic_cast<WiFiOnOffStatusIntfControllerListener&>(listener), cdmProxyObject);
}

WiFiOnOffStatusIntfControllerImpl::WiFiOnOffStatusIntfControllerImpl(BusAttachment& busAttachment, WiFiOnOffStatusIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

WiFiOnOffStatusIntfControllerImpl::~WiFiOnOffStatusIntfControllerImpl()
{
}

QStatus WiFiOnOffStatusIntfControllerImpl::Init()
{
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    status = m_proxyObject.RegisterPropertiesChangedListener(GetInterfaceName().c_str(), NULL, 0, *this, NULL);
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
    }

    return status;
}

void WiFiOnOffStatusIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    //
    // Add the implementation by hand.
    // 
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_IsOn.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BOOLEAN) {
                bool value = propValue->v_bool;
                m_interfaceListener.OnIsOnChanged(obj.GetPath(), value);
            }
        }
    }
}

//
// Add by hand the function which will request the GetProperty call.
//
QStatus WiFiOnOffStatusIntfControllerImpl::GetIsOn(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_IsOn.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&WiFiOnOffStatusIntfControllerImpl::GetIsOnPropertyCB, context);
    return status;
}

//
// Add by hand the callback function that receives the response of GetIsOnProperty.
//
void WiFiOnOffStatusIntfControllerImpl::GetIsOnPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    bool val;
    value.Get("b", &val);
    m_interfaceListener.OnResponseGetIsOn(status, obj->GetPath(), val, context);
}

} //namespace services
} //namespace ajn
