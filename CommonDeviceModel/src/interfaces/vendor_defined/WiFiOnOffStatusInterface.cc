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

#include <alljoyn/cdm/LogModule.h>
//
// Change by hand the include path of the vendor-defined header.
//
#include <alljoyn/cdm/vendor_defined/WiFiOnOffStatusInterface.h>

namespace ajn {
namespace services {

const uint16_t WiFiOnOffStatusInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test.
//
// Modify the interface xml by hand.
//
const qcc::String WiFiOnOffStatusInterface::s_xml =
        "<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
        "    <interface name='com.smartconn.SmartToys.Operation.WiFiOnOffStatus'>"
        "        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides a capability to monitor the WiFi on/off status of device.'/>"
        "        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
        "        <property name='Version' type='q' access='read'>"
        "            <description language='en'>Interface version</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <property name='IsOn' type='b' access='read'>"
        "            <annotation name='org.alljoyn.Bus.DocString.En' value='Current WiFi on/off state of the appliance. If true, the WiFi of the device is on state.'/>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "    </interface>"
        "</node>";

const qcc::String WiFiOnOffStatusInterface::s_prop_Version = "Version";
// 
// Add the property name by hand.
//
const qcc::String WiFiOnOffStatusInterface::s_prop_IsOn = "IsOn";

} //namespace services
} //namespace ajn
