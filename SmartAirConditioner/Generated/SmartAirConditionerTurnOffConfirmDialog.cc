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

#include "SmartAirConditionerTurnOffConfirmDialog.h"
#include "SmartAirConditionerProvided.h"


namespace ajn {
namespace services {

SmartAirConditionerTurnOffConfirmDialog::SmartAirConditionerTurnOffConfirmDialog(qcc::String name, Widget* rootWidget) : Dialog(name, rootWidget)
{

}

SmartAirConditionerTurnOffConfirmDialog::~SmartAirConditionerTurnOffConfirmDialog()
{

}

bool SmartAirConditionerTurnOffConfirmDialog::executeAction1CallBack()
{
    turnOffAc();

    //by default return success
    return true;
}

bool SmartAirConditionerTurnOffConfirmDialog::executeAction2CallBack()
{
    cancelTurnOffAc();

    //by default return success
    return true;
}

bool SmartAirConditionerTurnOffConfirmDialog::executeAction3CallBack()
{
    return executeActionNotDefined();

    //by default return success
    return true;
}

} /* namespace services */
} /* namespace ajn */
