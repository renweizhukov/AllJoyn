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

#ifndef OFFCONTROLINTFCONTROLLERIMPL_H_
#define OFFCONTROLINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/OffControlIntfController.h>

namespace ajn {
namespace services {

class OffControlIntfControllerListener;
class CdmProxyBusObject;

/**
 * OffControl Interface Controller implementation class
 */
class OffControlIntfControllerImpl : public InterfaceController, public OffControlIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of OffControlIntfControllerImpl
     */
    OffControlIntfControllerImpl(BusAttachment& busAttachment, OffControlIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of OffControlIntfControllerImpl
     */
    virtual ~OffControlIntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    //
    // Add by hand the function that requests the SwitchOff method call.
    //
    virtual QStatus SwitchOff(void* context);

  private:
    OffControlIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    //
    // Add the SwitchOff method reply handler by hand.
    //
    void SwitchOffReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    OffControlIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* OFFCONTROLINTFCONTROLLERIMPL_H_ */
