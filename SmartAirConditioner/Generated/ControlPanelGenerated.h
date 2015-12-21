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

#ifndef CONTROLPANELGENERATED_H_
#define CONTROLPANELGENERATED_H_

#include <alljoyn/controlpanel/ControlPanelControllee.h>
#include <alljoyn/controlpanel/Container.h>
#include <alljoyn/controlpanel/Label.h>
#include <alljoyn/controlpanel/ActionWithDialog.h>
#include "../Generated/SmartAirConditionerCurrentDateProperty.h"
#include "../Generated/SmartAirConditionerCurrentTimeProperty.h"
#include "../Generated/SmartAirConditionerOnOffStringProperty.h"
#include "../Generated/SmartAirConditionerCurrentTempProperty.h"
#include "../Generated/SmartAirConditionerCurrentHumidityProperty.h"
#include "../Generated/SmartAirConditionerOnAction.h"
#include "../Generated/SmartAirConditionerTurnOffConfirmDialog.h"
#include "../Generated/SmartAirConditionerAcModeProperty.h"
#include "../Generated/SmartAirConditionerTurboModeProperty.h"
#include "../Generated/SmartAirConditionerExpectedTempProperty.h"
#include "../Generated/SmartAirConditionerErrorDialog.h"


/**
 * Generated Class - do not change code
 */
class ControlPanelGenerated {
  public:

    static QStatus PrepareWidgets(ajn::services::ControlPanelControllee*& controlPanelControllee);

    static void PrepareLanguageSets();

    static void Shutdown();

    static bool languageSetsDone;

    static ajn::services::ControlPanelControlleeUnit* smartAirConditionerUnit;

    static ajn::services::ControlPanel* smartAirConditionerRootContainerControlPanel;

    static ajn::services::Container* smartAirConditionerRootContainer;

    static ajn::services::Container* smartAirConditionerDateTimeContainer;

    static ajn::services::SmartAirConditionerCurrentDateProperty* smartAirConditionerCurrentDateProperty;

    static ajn::services::SmartAirConditionerCurrentTimeProperty* smartAirConditionerCurrentTimeProperty;

    static ajn::services::Container* smartAirConditionerStatusContainer;

    static ajn::services::SmartAirConditionerOnOffStringProperty* smartAirConditionerOnOffStringProperty;

    static ajn::services::SmartAirConditionerCurrentTempProperty* smartAirConditionerCurrentTempProperty;

    static ajn::services::SmartAirConditionerCurrentHumidityProperty* smartAirConditionerCurrentHumidityProperty;

    static ajn::services::Container* smartAirConditionerActionContainer;

    static ajn::services::SmartAirConditionerOnAction* smartAirConditionerOnAction;

    static ajn::services::ActionWithDialog* smartAirConditionerOffAction;

    static ajn::services::SmartAirConditionerTurnOffConfirmDialog* smartAirConditionerTurnOffConfirmDialog;

    static ajn::services::Container* smartAirConditionerControlContainer;

    static ajn::services::SmartAirConditionerAcModeProperty* smartAirConditionerAcModeProperty;

    static ajn::services::SmartAirConditionerTurboModeProperty* smartAirConditionerTurboModeProperty;

    static ajn::services::SmartAirConditionerExpectedTempProperty* smartAirConditionerExpectedTempProperty;

    static ajn::services::Container* smartAirConditionerInfoContainer;

    static ajn::services::Label* smartAirConditionerHelpInfoLabelProperty;

    static ajn::services::NotificationAction* smartAirConditionerErrorDialogNotificationAction;

    static ajn::services::SmartAirConditionerErrorDialog* smartAirConditionerErrorDialog;


};

#endif /* CONTROLPANELGENERATED_H_ */
