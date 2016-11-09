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

#include "ControlPanelGenerated.h"
#include <alljoyn/controlpanel/LanguageSets.h>
#include <alljoyn/controlpanel/Label.h>
#include "SmartAirConditionerProvided.h"



using namespace ajn;
using namespace services;

bool ControlPanelGenerated::languageSetsDone = false;
ControlPanelControlleeUnit* ControlPanelGenerated::smartAirConditionerUnit = 0;
ControlPanel* ControlPanelGenerated::smartAirConditionerRootContainerControlPanel = 0;
Container* ControlPanelGenerated::smartAirConditionerRootContainer = 0;
Container* ControlPanelGenerated::smartAirConditionerDateTimeContainer = 0;
SmartAirConditionerCurrentDateProperty* ControlPanelGenerated::smartAirConditionerCurrentDateProperty = 0;
SmartAirConditionerCurrentTimeProperty* ControlPanelGenerated::smartAirConditionerCurrentTimeProperty = 0;
Container* ControlPanelGenerated::smartAirConditionerStatusContainer = 0;
SmartAirConditionerOnOffStringProperty* ControlPanelGenerated::smartAirConditionerOnOffStringProperty = 0;
SmartAirConditionerCurrentTempProperty* ControlPanelGenerated::smartAirConditionerCurrentTempProperty = 0;
SmartAirConditionerCurrentHumidityProperty* ControlPanelGenerated::smartAirConditionerCurrentHumidityProperty = 0;
Container* ControlPanelGenerated::smartAirConditionerActionContainer = 0;
SmartAirConditionerOnAction* ControlPanelGenerated::smartAirConditionerOnAction = 0;
ActionWithDialog* ControlPanelGenerated::smartAirConditionerOffAction = 0;
SmartAirConditionerTurnOffConfirmDialog* ControlPanelGenerated::smartAirConditionerTurnOffConfirmDialog = 0;
Container* ControlPanelGenerated::smartAirConditionerControlContainer = 0;
SmartAirConditionerAcModeProperty* ControlPanelGenerated::smartAirConditionerAcModeProperty = 0;
SmartAirConditionerTurboModeProperty* ControlPanelGenerated::smartAirConditionerTurboModeProperty = 0;
SmartAirConditionerExpectedTempProperty* ControlPanelGenerated::smartAirConditionerExpectedTempProperty = 0;
Container* ControlPanelGenerated::smartAirConditionerInfoContainer = 0;
Label* ControlPanelGenerated::smartAirConditionerHelpInfoLabelProperty = 0;
NotificationAction* ControlPanelGenerated::smartAirConditionerErrorDialogNotificationAction = 0;
SmartAirConditionerErrorDialog* ControlPanelGenerated::smartAirConditionerErrorDialog = 0;


#define CHECK(x) if ((status = x) != ER_OK) { return status; }

void ControlPanelGenerated::PrepareLanguageSets()
{
    if (languageSetsDone) {
        return;
    }

    LanguageSet smartAirConditionerLanguageSet1("smartAirConditionerLanguageSet1");
    smartAirConditionerLanguageSet1.addLanguage("en");
    LanguageSets::add(smartAirConditionerLanguageSet1.getLanguageSetName(), smartAirConditionerLanguageSet1);

    languageSetsDone = true;
}

QStatus ControlPanelGenerated::PrepareWidgets(ControlPanelControllee*& controlPanelControllee)
{
    if (controlPanelControllee) {
        return ER_BAD_ARG_1;
    }

    PrepareLanguageSets();

    QStatus status = ER_OK;
    controlPanelControllee = new ControlPanelControllee();

    smartAirConditionerUnit = new ControlPanelControlleeUnit("SmartAirConditioner");
    CHECK(controlPanelControllee->addControlPanelUnit(smartAirConditionerUnit));

    smartAirConditionerRootContainerControlPanel = ControlPanel::createControlPanel(LanguageSets::get("smartAirConditionerLanguageSet1"));
    if (!smartAirConditionerRootContainerControlPanel)
        return ER_FAIL;
    CHECK(smartAirConditionerUnit->addControlPanel(smartAirConditionerRootContainerControlPanel));

    smartAirConditionerRootContainer = new Container("rootContainer", NULL);
    CHECK(smartAirConditionerRootContainerControlPanel->setRootWidget(smartAirConditionerRootContainer));

    smartAirConditionerRootContainer->setEnabled(true);
    smartAirConditionerRootContainer->setIsSecured(false);
    smartAirConditionerRootContainer->setBgColor(0x1e90ff);

    std::vector<qcc::String> smartAirConditionerRootContainerlabelVec;
    smartAirConditionerRootContainerlabelVec.push_back("SmartConn Air Conditioner");
    smartAirConditionerRootContainer->setLabels(smartAirConditionerRootContainerlabelVec);

    std::vector<uint16_t> smartAirConditionerRootContainerHintsVec;
    smartAirConditionerRootContainerHintsVec.push_back(VERTICAL_LINEAR);
    smartAirConditionerRootContainer->setHints(smartAirConditionerRootContainerHintsVec);

    smartAirConditionerDateTimeContainer = new Container("dateTimeContainer", smartAirConditionerRootContainer);
    CHECK(smartAirConditionerRootContainer->addChildWidget(smartAirConditionerDateTimeContainer));

    smartAirConditionerDateTimeContainer->setEnabled(true);
    smartAirConditionerDateTimeContainer->setIsSecured(false);

    std::vector<qcc::String> smartAirConditionerDateTimeContainerlabelVec;
    smartAirConditionerDateTimeContainerlabelVec.push_back("Date and Time");
    smartAirConditionerDateTimeContainer->setLabels(smartAirConditionerDateTimeContainerlabelVec);

    std::vector<uint16_t> smartAirConditionerDateTimeContainerHintsVec;
    smartAirConditionerDateTimeContainerHintsVec.push_back(HORIZONTAL_LINEAR);
    smartAirConditionerDateTimeContainer->setHints(smartAirConditionerDateTimeContainerHintsVec);

    smartAirConditionerCurrentDateProperty = new SmartAirConditionerCurrentDateProperty("currentDateProperty", smartAirConditionerDateTimeContainer, DATE_PROPERTY);
    CHECK(smartAirConditionerDateTimeContainer->addChildWidget(smartAirConditionerCurrentDateProperty));

    smartAirConditionerCurrentDateProperty->setEnabled(true);
    smartAirConditionerCurrentDateProperty->setIsSecured(false);
    smartAirConditionerCurrentDateProperty->setWritable(true);
    CHECK(smartAirConditionerCurrentDateProperty->setGetValue(getCurrentDate));

    std::vector<uint16_t> smartAirConditionerCurrentDatePropertyHintsVec;
    smartAirConditionerCurrentDatePropertyHintsVec.push_back(DATEPICKER);
    smartAirConditionerCurrentDateProperty->setHints(smartAirConditionerCurrentDatePropertyHintsVec);

    smartAirConditionerCurrentTimeProperty = new SmartAirConditionerCurrentTimeProperty("currentTimeProperty", smartAirConditionerDateTimeContainer, TIME_PROPERTY);
    CHECK(smartAirConditionerDateTimeContainer->addChildWidget(smartAirConditionerCurrentTimeProperty));

    smartAirConditionerCurrentTimeProperty->setEnabled(true);
    smartAirConditionerCurrentTimeProperty->setIsSecured(false);
    smartAirConditionerCurrentTimeProperty->setWritable(true);
    CHECK(smartAirConditionerCurrentTimeProperty->setGetValue(getCurrentTime));

    std::vector<uint16_t> smartAirConditionerCurrentTimePropertyHintsVec;
    smartAirConditionerCurrentTimePropertyHintsVec.push_back(TIMEPICKER);
    smartAirConditionerCurrentTimeProperty->setHints(smartAirConditionerCurrentTimePropertyHintsVec);

    smartAirConditionerStatusContainer = new Container("statusContainer", smartAirConditionerRootContainer);
    CHECK(smartAirConditionerRootContainer->addChildWidget(smartAirConditionerStatusContainer));

    smartAirConditionerStatusContainer->setEnabled(true);
    smartAirConditionerStatusContainer->setIsSecured(false);

    std::vector<qcc::String> smartAirConditionerStatusContainerlabelVec;
    smartAirConditionerStatusContainerlabelVec.push_back("Status");
    smartAirConditionerStatusContainer->setLabels(smartAirConditionerStatusContainerlabelVec);

    std::vector<uint16_t> smartAirConditionerStatusContainerHintsVec;
    smartAirConditionerStatusContainerHintsVec.push_back(HORIZONTAL_LINEAR);
    smartAirConditionerStatusContainer->setHints(smartAirConditionerStatusContainerHintsVec);

    smartAirConditionerOnOffStringProperty = new SmartAirConditionerOnOffStringProperty("onOffStringProperty", smartAirConditionerStatusContainer, STRING_PROPERTY);
    CHECK(smartAirConditionerStatusContainer->addChildWidget(smartAirConditionerOnOffStringProperty));

    smartAirConditionerOnOffStringProperty->setEnabled(true);
    smartAirConditionerOnOffStringProperty->setIsSecured(false);
    smartAirConditionerOnOffStringProperty->setWritable(false);
    CHECK(smartAirConditionerOnOffStringProperty->setGetValue(getOnOffString));

    std::vector<uint16_t> smartAirConditionerOnOffStringPropertyHintsVec;
    smartAirConditionerOnOffStringPropertyHintsVec.push_back(SWITCH);
    smartAirConditionerOnOffStringProperty->setHints(smartAirConditionerOnOffStringPropertyHintsVec);

    std::vector<ConstraintList> smartAirConditionerOnOffStringPropertyConstraintListVec(2);

    std::vector<qcc::String> smartAirConditionerOnOffStringPropertyDisplay1Vec;
    smartAirConditionerOnOffStringPropertyDisplay1Vec.push_back("On");
    smartAirConditionerOnOffStringPropertyConstraintListVec[0].setDisplays(smartAirConditionerOnOffStringPropertyDisplay1Vec);
    smartAirConditionerOnOffStringPropertyConstraintListVec[0].setConstraintValue("OnState");

    std::vector<qcc::String> smartAirConditionerOnOffStringPropertyDisplay2Vec;
    smartAirConditionerOnOffStringPropertyDisplay2Vec.push_back("Off");
    smartAirConditionerOnOffStringPropertyConstraintListVec[1].setDisplays(smartAirConditionerOnOffStringPropertyDisplay2Vec);
    smartAirConditionerOnOffStringPropertyConstraintListVec[1].setConstraintValue("OffState");

    smartAirConditionerOnOffStringProperty->setConstraintList(smartAirConditionerOnOffStringPropertyConstraintListVec);

    smartAirConditionerCurrentTempProperty = new SmartAirConditionerCurrentTempProperty("currentTempProperty", smartAirConditionerStatusContainer, INT16_PROPERTY);
    CHECK(smartAirConditionerStatusContainer->addChildWidget(smartAirConditionerCurrentTempProperty));

    smartAirConditionerCurrentTempProperty->setEnabled(true);
    smartAirConditionerCurrentTempProperty->setIsSecured(false);
    smartAirConditionerCurrentTempProperty->setWritable(false);
    CHECK(smartAirConditionerCurrentTempProperty->setGetValue(getCurrentTemp));

    std::vector<qcc::String> smartAirConditionerCurrentTempPropertylabelVec;
    smartAirConditionerCurrentTempPropertylabelVec.push_back("Temperature:");
    smartAirConditionerCurrentTempProperty->setLabels(smartAirConditionerCurrentTempPropertylabelVec);

    std::vector<uint16_t> smartAirConditionerCurrentTempPropertyHintsVec;
    smartAirConditionerCurrentTempPropertyHintsVec.push_back(NUMERICVIEW);
    smartAirConditionerCurrentTempProperty->setHints(smartAirConditionerCurrentTempPropertyHintsVec);

    std::vector<qcc::String> smartAirConditionerCurrentTempPropertyunitMeasureVec;
    smartAirConditionerCurrentTempPropertyunitMeasureVec.push_back("Fahrenheit");
    smartAirConditionerCurrentTempProperty->setUnitOfMeasures(smartAirConditionerCurrentTempPropertyunitMeasureVec);

    smartAirConditionerCurrentHumidityProperty = new SmartAirConditionerCurrentHumidityProperty("currentHumidityProperty", smartAirConditionerStatusContainer, UINT16_PROPERTY);
    CHECK(smartAirConditionerStatusContainer->addChildWidget(smartAirConditionerCurrentHumidityProperty));

    smartAirConditionerCurrentHumidityProperty->setEnabled(true);
    smartAirConditionerCurrentHumidityProperty->setIsSecured(false);
    smartAirConditionerCurrentHumidityProperty->setWritable(false);
    CHECK(smartAirConditionerCurrentHumidityProperty->setGetValue(getCurrentHumidity));

    std::vector<qcc::String> smartAirConditionerCurrentHumidityPropertylabelVec;
    smartAirConditionerCurrentHumidityPropertylabelVec.push_back("Humidity:");
    smartAirConditionerCurrentHumidityProperty->setLabels(smartAirConditionerCurrentHumidityPropertylabelVec);

    std::vector<uint16_t> smartAirConditionerCurrentHumidityPropertyHintsVec;
    smartAirConditionerCurrentHumidityPropertyHintsVec.push_back(NUMERICVIEW);
    smartAirConditionerCurrentHumidityProperty->setHints(smartAirConditionerCurrentHumidityPropertyHintsVec);

    std::vector<qcc::String> smartAirConditionerCurrentHumidityPropertyunitMeasureVec;
    smartAirConditionerCurrentHumidityPropertyunitMeasureVec.push_back("Percent");
    smartAirConditionerCurrentHumidityProperty->setUnitOfMeasures(smartAirConditionerCurrentHumidityPropertyunitMeasureVec);

    smartAirConditionerActionContainer = new Container("actionContainer", smartAirConditionerRootContainer);
    CHECK(smartAirConditionerRootContainer->addChildWidget(smartAirConditionerActionContainer));

    smartAirConditionerActionContainer->setEnabled(true);
    smartAirConditionerActionContainer->setIsSecured(false);

    std::vector<qcc::String> smartAirConditionerActionContainerlabelVec;
    smartAirConditionerActionContainerlabelVec.push_back("On/Off Switch");
    smartAirConditionerActionContainer->setLabels(smartAirConditionerActionContainerlabelVec);

    std::vector<uint16_t> smartAirConditionerActionContainerHintsVec;
    smartAirConditionerActionContainerHintsVec.push_back(HORIZONTAL_LINEAR);
    smartAirConditionerActionContainer->setHints(smartAirConditionerActionContainerHintsVec);

    smartAirConditionerOnAction = new SmartAirConditionerOnAction("onAction", smartAirConditionerActionContainer);
    CHECK(smartAirConditionerActionContainer->addChildWidget(smartAirConditionerOnAction));

    smartAirConditionerOnAction->setEnabled(true);
    smartAirConditionerOnAction->setIsSecured(false);
    smartAirConditionerOnAction->setBgColor(0xc00);

    std::vector<qcc::String> smartAirConditionerOnActionlabelVec;
    smartAirConditionerOnActionlabelVec.push_back("Start AC");
    smartAirConditionerOnAction->setLabels(smartAirConditionerOnActionlabelVec);

    std::vector<uint16_t> smartAirConditionerOnActionHintsVec;
    smartAirConditionerOnActionHintsVec.push_back(ACTIONBUTTON);
    smartAirConditionerOnAction->setHints(smartAirConditionerOnActionHintsVec);

    smartAirConditionerOffAction = new ActionWithDialog("offAction", smartAirConditionerActionContainer);
    CHECK(smartAirConditionerActionContainer->addChildWidget(smartAirConditionerOffAction));

    smartAirConditionerOffAction->setEnabled(true);
    smartAirConditionerOffAction->setIsSecured(false);
    smartAirConditionerOffAction->setBgColor(0x400);

    std::vector<qcc::String> smartAirConditionerOffActionlabelVec;
    smartAirConditionerOffActionlabelVec.push_back("Stop AC");
    smartAirConditionerOffAction->setLabels(smartAirConditionerOffActionlabelVec);

    std::vector<uint16_t> smartAirConditionerOffActionHintsVec;
    smartAirConditionerOffActionHintsVec.push_back(ACTIONBUTTON);
    smartAirConditionerOffAction->setHints(smartAirConditionerOffActionHintsVec);

    smartAirConditionerTurnOffConfirmDialog = new SmartAirConditionerTurnOffConfirmDialog("turnOffConfirmDialog", NULL);
    CHECK(smartAirConditionerOffAction->addChildDialog(smartAirConditionerTurnOffConfirmDialog));

    smartAirConditionerTurnOffConfirmDialog->setEnabled(true);
    smartAirConditionerTurnOffConfirmDialog->setIsSecured(false);

    std::vector<qcc::String> smartAirConditionerTurnOffConfirmDialogmessageVec;
    smartAirConditionerTurnOffConfirmDialogmessageVec.push_back("Are you sure you want to turn off the air conditioner?");
    smartAirConditionerTurnOffConfirmDialog->setMessages(smartAirConditionerTurnOffConfirmDialogmessageVec);
    smartAirConditionerTurnOffConfirmDialog->setNumActions(2);
    smartAirConditionerTurnOffConfirmDialog->setBgColor(0x1e90ff);

    std::vector<qcc::String> smartAirConditionerTurnOffConfirmDialoglabelVec;
    smartAirConditionerTurnOffConfirmDialoglabelVec.push_back("SmartConn Air Conditioner");
    smartAirConditionerTurnOffConfirmDialog->setLabels(smartAirConditionerTurnOffConfirmDialoglabelVec);

    std::vector<uint16_t> smartAirConditionerTurnOffConfirmDialogHintsVec;
    smartAirConditionerTurnOffConfirmDialogHintsVec.push_back(ALERTDIALOG);
    smartAirConditionerTurnOffConfirmDialog->setHints(smartAirConditionerTurnOffConfirmDialogHintsVec);

    std::vector<qcc::String> smartAirConditionerTurnOffConfirmDialogLabelAction1Vec;
    smartAirConditionerTurnOffConfirmDialogLabelAction1Vec.push_back("Yes");
    smartAirConditionerTurnOffConfirmDialog->setLabelsAction1(smartAirConditionerTurnOffConfirmDialogLabelAction1Vec);

    std::vector<qcc::String> smartAirConditionerTurnOffConfirmDialogLabelAction2Vec;
    smartAirConditionerTurnOffConfirmDialogLabelAction2Vec.push_back("No");
    smartAirConditionerTurnOffConfirmDialog->setLabelsAction2(smartAirConditionerTurnOffConfirmDialogLabelAction2Vec);

    smartAirConditionerControlContainer = new Container("controlContainer", smartAirConditionerRootContainer);
    CHECK(smartAirConditionerRootContainer->addChildWidget(smartAirConditionerControlContainer));

    smartAirConditionerControlContainer->setEnabled(true);
    smartAirConditionerControlContainer->setIsSecured(false);

    std::vector<qcc::String> smartAirConditionerControlContainerlabelVec;
    smartAirConditionerControlContainerlabelVec.push_back("Control Panel");
    smartAirConditionerControlContainer->setLabels(smartAirConditionerControlContainerlabelVec);

    std::vector<uint16_t> smartAirConditionerControlContainerHintsVec;
    smartAirConditionerControlContainerHintsVec.push_back(VERTICAL_LINEAR);
    smartAirConditionerControlContainer->setHints(smartAirConditionerControlContainerHintsVec);

    smartAirConditionerAcModeProperty = new SmartAirConditionerAcModeProperty("acModeProperty", smartAirConditionerControlContainer, UINT16_PROPERTY);
    CHECK(smartAirConditionerControlContainer->addChildWidget(smartAirConditionerAcModeProperty));

    smartAirConditionerAcModeProperty->setEnabled(true);
    smartAirConditionerAcModeProperty->setIsSecured(false);
    smartAirConditionerAcModeProperty->setWritable(true);
    CHECK(smartAirConditionerAcModeProperty->setGetValue(getAcMode));

    std::vector<qcc::String> smartAirConditionerAcModePropertylabelVec;
    smartAirConditionerAcModePropertylabelVec.push_back("Air Conditioner Mode");
    smartAirConditionerAcModeProperty->setLabels(smartAirConditionerAcModePropertylabelVec);

    std::vector<uint16_t> smartAirConditionerAcModePropertyHintsVec;
    smartAirConditionerAcModePropertyHintsVec.push_back(SPINNER);
    smartAirConditionerAcModeProperty->setHints(smartAirConditionerAcModePropertyHintsVec);

    std::vector<ConstraintList> smartAirConditionerAcModePropertyConstraintListVec(3);

    std::vector<qcc::String> smartAirConditionerAcModePropertyDisplay1Vec;
    smartAirConditionerAcModePropertyDisplay1Vec.push_back("Auto");
    smartAirConditionerAcModePropertyConstraintListVec[0].setDisplays(smartAirConditionerAcModePropertyDisplay1Vec);
    smartAirConditionerAcModePropertyConstraintListVec[0].setConstraintValue((uint16_t)175);

    std::vector<qcc::String> smartAirConditionerAcModePropertyDisplay2Vec;
    smartAirConditionerAcModePropertyDisplay2Vec.push_back("Cool");
    smartAirConditionerAcModePropertyConstraintListVec[1].setDisplays(smartAirConditionerAcModePropertyDisplay2Vec);
    smartAirConditionerAcModePropertyConstraintListVec[1].setConstraintValue((uint16_t)200);

    std::vector<qcc::String> smartAirConditionerAcModePropertyDisplay3Vec;
    smartAirConditionerAcModePropertyDisplay3Vec.push_back("Heat");
    smartAirConditionerAcModePropertyConstraintListVec[2].setDisplays(smartAirConditionerAcModePropertyDisplay3Vec);
    smartAirConditionerAcModePropertyConstraintListVec[2].setConstraintValue((uint16_t)225);

    smartAirConditionerAcModeProperty->setConstraintList(smartAirConditionerAcModePropertyConstraintListVec);

    smartAirConditionerTurboModeProperty = new SmartAirConditionerTurboModeProperty("turboModeProperty", smartAirConditionerControlContainer, BOOL_PROPERTY);
    CHECK(smartAirConditionerControlContainer->addChildWidget(smartAirConditionerTurboModeProperty));

    smartAirConditionerTurboModeProperty->setEnabled(true);
    smartAirConditionerTurboModeProperty->setIsSecured(false);
    smartAirConditionerTurboModeProperty->setWritable(true);
    CHECK(smartAirConditionerTurboModeProperty->setGetValue(getTurboMode));

    std::vector<qcc::String> smartAirConditionerTurboModePropertylabelVec;
    smartAirConditionerTurboModePropertylabelVec.push_back("Turbo Mode");
    smartAirConditionerTurboModeProperty->setLabels(smartAirConditionerTurboModePropertylabelVec);

    std::vector<uint16_t> smartAirConditionerTurboModePropertyHintsVec;
    smartAirConditionerTurboModePropertyHintsVec.push_back(CHECKBOX);
    smartAirConditionerTurboModeProperty->setHints(smartAirConditionerTurboModePropertyHintsVec);

    smartAirConditionerExpectedTempProperty = new SmartAirConditionerExpectedTempProperty("expectedTempProperty", smartAirConditionerControlContainer, UINT16_PROPERTY);
    CHECK(smartAirConditionerControlContainer->addChildWidget(smartAirConditionerExpectedTempProperty));

    smartAirConditionerExpectedTempProperty->setEnabled(true);
    smartAirConditionerExpectedTempProperty->setIsSecured(false);
    smartAirConditionerExpectedTempProperty->setWritable(true);
    CHECK(smartAirConditionerExpectedTempProperty->setGetValue(getExpectedTemp));

    std::vector<qcc::String> smartAirConditionerExpectedTempPropertylabelVec;
    smartAirConditionerExpectedTempPropertylabelVec.push_back("Expected Temperature:");
    smartAirConditionerExpectedTempProperty->setLabels(smartAirConditionerExpectedTempPropertylabelVec);

    std::vector<uint16_t> smartAirConditionerExpectedTempPropertyHintsVec;
    smartAirConditionerExpectedTempPropertyHintsVec.push_back(SLIDER);
    smartAirConditionerExpectedTempProperty->setHints(smartAirConditionerExpectedTempPropertyHintsVec);

    std::vector<qcc::String> smartAirConditionerExpectedTempPropertyunitMeasureVec;
    smartAirConditionerExpectedTempPropertyunitMeasureVec.push_back("Fahrenheit");
    smartAirConditionerExpectedTempProperty->setUnitOfMeasures(smartAirConditionerExpectedTempPropertyunitMeasureVec);

    ConstraintRange* smartAirConditionerExpectedTempPropertyConstraintRange = new ConstraintRange();
    smartAirConditionerExpectedTempProperty->setConstraintRange(smartAirConditionerExpectedTempPropertyConstraintRange);
    CHECK(smartAirConditionerExpectedTempPropertyConstraintRange->setConstraintMin((uint16_t)32));
    CHECK(smartAirConditionerExpectedTempPropertyConstraintRange->setConstraintMax((uint16_t)90));
    CHECK(smartAirConditionerExpectedTempPropertyConstraintRange->setConstraintIncrement((uint16_t)1));

    smartAirConditionerInfoContainer = new Container("infoContainer", smartAirConditionerRootContainer);
    CHECK(smartAirConditionerRootContainer->addChildWidget(smartAirConditionerInfoContainer));

    smartAirConditionerInfoContainer->setEnabled(true);
    smartAirConditionerInfoContainer->setIsSecured(false);

    std::vector<uint16_t> smartAirConditionerInfoContainerHintsVec;
    smartAirConditionerInfoContainerHintsVec.push_back(VERTICAL_LINEAR);
    smartAirConditionerInfoContainer->setHints(smartAirConditionerInfoContainerHintsVec);

    smartAirConditionerHelpInfoLabelProperty = new Label("helpInfoLabelProperty", smartAirConditionerInfoContainer);
    CHECK(smartAirConditionerInfoContainer->addChildWidget(smartAirConditionerHelpInfoLabelProperty));

    smartAirConditionerHelpInfoLabelProperty->setEnabled(true);

    std::vector<qcc::String> smartAirConditionerHelpInfoLabelPropertylabelVec;
    smartAirConditionerHelpInfoLabelPropertylabelVec.push_back("For questions, please visit http://www.smartconn.global.");
    smartAirConditionerHelpInfoLabelProperty->setLabels(smartAirConditionerHelpInfoLabelPropertylabelVec);

    std::vector<uint16_t> smartAirConditionerHelpInfoLabelPropertyHintsVec;
    smartAirConditionerHelpInfoLabelPropertyHintsVec.push_back(TEXTLABEL);
    smartAirConditionerHelpInfoLabelProperty->setHints(smartAirConditionerHelpInfoLabelPropertyHintsVec);

    smartAirConditionerErrorDialogNotificationAction = NotificationAction::createNotificationAction(LanguageSets::get("smartAirConditionerLanguageSet1"));
    if (!smartAirConditionerErrorDialogNotificationAction)
        return ER_FAIL;
    CHECK(smartAirConditionerUnit->addNotificationAction(smartAirConditionerErrorDialogNotificationAction));

    smartAirConditionerErrorDialog = new SmartAirConditionerErrorDialog("ErrorDialog", NULL);
    CHECK(smartAirConditionerErrorDialogNotificationAction->setRootWidget(smartAirConditionerErrorDialog));

    smartAirConditionerErrorDialog->setEnabled(true);
    smartAirConditionerErrorDialog->setIsSecured(false);

    std::vector<qcc::String> smartAirConditionerErrorDialogmessageVec;
    smartAirConditionerErrorDialogmessageVec.push_back("Something is wrong. Turn off the air conditioner?");
    smartAirConditionerErrorDialog->setMessages(smartAirConditionerErrorDialogmessageVec);
    smartAirConditionerErrorDialog->setNumActions(2);
    smartAirConditionerErrorDialog->setBgColor(0x1e90ff);

    std::vector<qcc::String> smartAirConditionerErrorDialoglabelVec;
    smartAirConditionerErrorDialoglabelVec.push_back("SmartConn Air Conditioner");
    smartAirConditionerErrorDialog->setLabels(smartAirConditionerErrorDialoglabelVec);

    std::vector<uint16_t> smartAirConditionerErrorDialogHintsVec;
    smartAirConditionerErrorDialogHintsVec.push_back(ALERTDIALOG);
    smartAirConditionerErrorDialog->setHints(smartAirConditionerErrorDialogHintsVec);

    std::vector<qcc::String> smartAirConditionerErrorDialogLabelAction1Vec;
    smartAirConditionerErrorDialogLabelAction1Vec.push_back("Yes");
    smartAirConditionerErrorDialog->setLabelsAction1(smartAirConditionerErrorDialogLabelAction1Vec);

    std::vector<qcc::String> smartAirConditionerErrorDialogLabelAction2Vec;
    smartAirConditionerErrorDialogLabelAction2Vec.push_back("No");
    smartAirConditionerErrorDialog->setLabelsAction2(smartAirConditionerErrorDialogLabelAction2Vec);

    return status;
}

void ControlPanelGenerated::Shutdown()
{
    if (smartAirConditionerUnit) {
        delete (smartAirConditionerUnit);
        smartAirConditionerUnit = 0;
    }
    if (smartAirConditionerRootContainerControlPanel) {
        delete (smartAirConditionerRootContainerControlPanel);
        smartAirConditionerRootContainerControlPanel = 0;
    }
    if (smartAirConditionerRootContainer) {
        delete (smartAirConditionerRootContainer);
        smartAirConditionerRootContainer = 0;
    }
    if (smartAirConditionerDateTimeContainer) {
        delete (smartAirConditionerDateTimeContainer);
        smartAirConditionerDateTimeContainer = 0;
    }
    if (smartAirConditionerCurrentDateProperty) {
        delete (smartAirConditionerCurrentDateProperty);
        smartAirConditionerCurrentDateProperty = 0;
    }
    if (smartAirConditionerCurrentTimeProperty) {
        delete (smartAirConditionerCurrentTimeProperty);
        smartAirConditionerCurrentTimeProperty = 0;
    }
    if (smartAirConditionerStatusContainer) {
        delete (smartAirConditionerStatusContainer);
        smartAirConditionerStatusContainer = 0;
    }
    if (smartAirConditionerOnOffStringProperty) {
        delete (smartAirConditionerOnOffStringProperty);
        smartAirConditionerOnOffStringProperty = 0;
    }
    if (smartAirConditionerCurrentTempProperty) {
        delete (smartAirConditionerCurrentTempProperty);
        smartAirConditionerCurrentTempProperty = 0;
    }
    if (smartAirConditionerCurrentHumidityProperty) {
        delete (smartAirConditionerCurrentHumidityProperty);
        smartAirConditionerCurrentHumidityProperty = 0;
    }
    if (smartAirConditionerActionContainer) {
        delete (smartAirConditionerActionContainer);
        smartAirConditionerActionContainer = 0;
    }
    if (smartAirConditionerOnAction) {
        delete (smartAirConditionerOnAction);
        smartAirConditionerOnAction = 0;
    }
    if (smartAirConditionerOffAction) {
        delete (smartAirConditionerOffAction);
        smartAirConditionerOffAction = 0;
    }
    if (smartAirConditionerTurnOffConfirmDialog) {
        delete (smartAirConditionerTurnOffConfirmDialog);
        smartAirConditionerTurnOffConfirmDialog = 0;
    }
    if (smartAirConditionerControlContainer) {
        delete (smartAirConditionerControlContainer);
        smartAirConditionerControlContainer = 0;
    }
    if (smartAirConditionerAcModeProperty) {
        delete (smartAirConditionerAcModeProperty);
        smartAirConditionerAcModeProperty = 0;
    }
    if (smartAirConditionerTurboModeProperty) {
        delete (smartAirConditionerTurboModeProperty);
        smartAirConditionerTurboModeProperty = 0;
    }
    if (smartAirConditionerExpectedTempProperty) {
        delete (smartAirConditionerExpectedTempProperty);
        smartAirConditionerExpectedTempProperty = 0;
    }
    if (smartAirConditionerInfoContainer) {
        delete (smartAirConditionerInfoContainer);
        smartAirConditionerInfoContainer = 0;
    }
    if (smartAirConditionerHelpInfoLabelProperty) {
        delete (smartAirConditionerHelpInfoLabelProperty);
        smartAirConditionerHelpInfoLabelProperty = 0;
    }
    if (smartAirConditionerErrorDialogNotificationAction) {
        delete (smartAirConditionerErrorDialogNotificationAction);
        smartAirConditionerErrorDialogNotificationAction = 0;
    }
    if (smartAirConditionerErrorDialog) {
        delete (smartAirConditionerErrorDialog);
        smartAirConditionerErrorDialog = 0;
    }

}
