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

#ifndef SMARTAIRCONDITIONERTURBOMODEPROPERTY_H_
#define SMARTAIRCONDITIONERTURBOMODEPROPERTY_H_

#include <alljoyn/controlpanel/Property.h>

namespace ajn {
namespace services {

/**
 * Generated class
 */
class SmartAirConditionerTurboModeProperty : public ajn::services::Property {
  public:
    SmartAirConditionerTurboModeProperty(qcc::String name, Widget* rootWidget, PropertyType propertyType);
    virtual ~SmartAirConditionerTurboModeProperty();

    QStatus setValue(bool value);
};
} //namespace services
} //namespace ajn

#endif /* SMARTAIRCONDITIONERTURBOMODEPROPERTY_H_ */
