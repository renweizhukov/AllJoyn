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

#ifndef WIFIONOFFSTATUSINTFCONTROLLEELISTENER_H_
#define WIFIONOFFSTATUSINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * WiFiOnOffStatus Interface Controllee Listener class
 */
class WiFiOnOffStatusIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of WiFiOnOffStatusIntfControlleeListener
     */
    virtual ~WiFiOnOffStatusIntfControlleeListener() {}

    //
    // Add by hand the function which retrieves the latest value from the device.
    // This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
    // In this case, the controllee will update its internal cached value with the latest actual value 
    // and then return the latest actual value to the controller.
    //
    virtual QStatus OnGetIsOn(bool& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* WIFIONOFFSTATUSINTFCONTROLLEELISTENER_H_ */
