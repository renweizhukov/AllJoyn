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

#ifndef WIFIONOFFSTATUSINTFCONTROLLEEIMPL_H_
#define WIFIONOFFSTATUSINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
//
// Change by hand the include path of the vendor-defined header.
//
#include <alljoyn/cdm/vendor_defined/WiFiOnOffStatusIntfControllee.h>

namespace ajn {
namespace services {

class WiFiOnOffStatusIntfControlleeListener;
class CdmBusObject;

/**
 * WiFiOnOffStatus Interface Controllee implementation class
 */
class WiFiOnOffStatusIntfControlleeImpl : public InterfaceControllee, public WiFiOnOffStatusIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of WiFiOnOffStatusIntfControlleeImpl
     */
    WiFiOnOffStatusIntfControlleeImpl(BusAttachment& busAttachment, WiFiOnOffStatusIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of WiFiOnOffStatusIntfControlleeImpl
     */
    virtual ~WiFiOnOffStatusIntfControlleeImpl();

    /**
     * Initialize interface
     * @return status
     */
     virtual QStatus Init();

    /**
     * a callback function for getting property.
     * @param propName   Identifies the property to get
     * @param[out] val   Returns the property value. The type of this value is the actual value type.
     * @return status
     */
    virtual QStatus OnGetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * a callback function for setting property.
     * @param propName  Identifies the property to set
     * @param val       The property value to set. The type of this value is the actual value type.
     */
    virtual QStatus OnSetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * method handler
     * @param member    Method interface member entry.
     * @param message   The received method call message.
     */
    virtual void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    virtual const MethodHandlers& GetMethodHanders() const { return m_methodHandlers; }

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    //
    // Add the Property Get and Set methods by hand.
    //
    virtual const bool GetIsOn() const;
    virtual QStatus SetIsOn(const bool value);

  private:
    WiFiOnOffStatusIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    WiFiOnOffStatusIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    
    //
    // Add the internal cached value of the property IsOn.
    // 
    bool m_isOn;
};

} //namespace services
} //namespace ajn

#endif /* WIFIONOFFSTATUSINTFCONTROLLEEIMPL_H_ */
