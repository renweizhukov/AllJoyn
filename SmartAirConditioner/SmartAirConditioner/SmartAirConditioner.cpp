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

// SmartAirConditioner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define SERVICE_PORT 900

using namespace std;
using namespace ajn;
using namespace services;
using namespace qcc;

AboutData* aboutData = NULL;
AboutObj* aboutObj = NULL;
CommonBusListener* controlpanelBusListener = NULL;
BusAttachment* bus = NULL;
ControlPanelService* controlPanelService = NULL;
ControlPanelControllee* controlPanelControllee = NULL;
SrpKeyXListener* srpKeyXListener = NULL;
NotificationService* notiService = NULL;
NotificationSender* notiSender = NULL;

static volatile sig_atomic_t s_interrupt = false;

static volatile sig_atomic_t s_restart = false;

static void CDECL_CALL SigIntHandler(int sig)
{
    s_interrupt = true;
}

static void daemonDisconnectCB()
{
    s_restart = true;
}

void cleanup()
{
    CommonSampleUtil::aboutServiceDestroy(bus, controlpanelBusListener);
    if (controlPanelService) {
        controlPanelService->shutdownControllee();
    }
    ControlPanelGenerated::Shutdown();
    if (notiService) {
        notiService->shutdown();
        delete notiService;
        notiService = NULL;
    }
    if (notiSender) {
        delete notiSender;
        notiSender = NULL;
    }
    if (controlPanelControllee) {
        delete controlPanelControllee;
        controlPanelControllee = NULL;
    }
    if (controlpanelBusListener) {
        delete controlpanelBusListener;
        controlpanelBusListener = NULL;
    }
    if (aboutData) {
        delete aboutData;
        aboutData = NULL;
    }
    if (aboutObj) {
        delete aboutObj;
        aboutObj = NULL;
    }
    if (controlPanelService) {
        delete controlPanelService;
        controlPanelService = NULL;
    }
    if (srpKeyXListener) {
        delete srpKeyXListener;
        srpKeyXListener = NULL;
    }
    if (bus) {
        delete bus;
        bus = NULL;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    QCC_UNUSED(argc);
    QCC_UNUSED(argv);

    // Initialize AllJoyn
    AJInitializer ajInit;
    if (ajInit.Initialize() != ER_OK) {
        return 1;
    }

    QStatus status;

    // Allow CTRL+C to end application
    signal(SIGINT, SigIntHandler);
    cout << "Beginning ControlPanel Application. (Press CTRL+C and enter or CTRL+D to end application)" << endl;

    // Initialize Service objects

start:
    controlPanelService = ControlPanelService::getInstance();
    QCC_SetDebugLevel(logModules::CONTROLPANEL_MODULE_LOG_NAME, logModules::ALL_LOG_LEVELS);

    // Initialize Notification Service object.
    notiService = NotificationService::getInstance();

    srpKeyXListener = new SrpKeyXListener();

    /* Connect to the daemon */
    uint16_t retry = 0;
    do {
        bus = CommonSampleUtil::prepareBusAttachment(srpKeyXListener);
        if (bus == NULL) {
            cout << "Could not initialize BusAttachment. Retrying" << endl;
#ifdef _WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
            retry++;
        }
    } while (bus == NULL && retry != 180 && !s_interrupt);

    if (bus == NULL) {
        cout << "Could not initialize BusAttachment." << endl;
        cleanup();
        return 1;
    }

    controlpanelBusListener = new CommonBusListener(bus, daemonDisconnectCB);

    String device_id, app_id;
    String app_name = "SmartConnAirConditioner";
    DeviceNamesType deviceNames;
    deviceNames.insert(move(pair<String, String>("en", "Wei's AC")));
    GuidUtil::GetInstance()->GetDeviceIdString(&device_id);
    GuidUtil::GetInstance()->GenerateGUID(&app_id);

    aboutData = new AboutData("en");
    status = CommonSampleUtil::fillAboutData(aboutData, app_id, app_name, device_id, deviceNames);
    if (status != ER_OK) {
        cout << "Could not fill About Data." << endl;
        cleanup();
        return 1;
    }
    aboutObj = new AboutObj(*bus, BusObject::ANNOUNCED);
    status = CommonSampleUtil::prepareAboutService(bus, aboutData, aboutObj,
                                                   controlpanelBusListener, SERVICE_PORT);
    if (status != ER_OK) {
        cout << "Could not register bus object." << endl;
        cleanup();
        return 1;
    }

    status = ControlPanelGenerated::PrepareWidgets(controlPanelControllee);
    if (status != ER_OK) {
        cout << "Could not prepare Widgets." << endl;
        cleanup();
        return 1;
    }

    status = controlPanelService->initControllee(bus, controlPanelControllee);
    if (status != ER_OK) {
        cout << "Could not initialize Controllee." << endl;
        cleanup();
        return 1;
    }

    // Initialize Notification Sender object.
    notiSender = notiService->initSend(bus, aboutData);
    if (!notiSender) {
        cout << "Could not initialize Sender - exiting application" << endl;
        cleanup();
        return 1;
    }

    status = CommonSampleUtil::aboutServiceAnnounce();
    if (status != ER_OK) {
        cout << "Could not announce." << endl;
        cleanup();
        return 1;
    }

    cout << "Sent announce, waiting for Controllers" << endl;
    cout << "Enter in the ControlPanelService object path or press 'enter' to use default:" << endl;

    string input;
    String controlPanelServiceObjectPath;
    String defaultControlPanelServiceObjectPath = "/ControlPanel/SmartAirConditioner/ErrorDialog";

    getline(std::cin, input);
    while ((s_interrupt == false) && (s_restart == false) && (!cin.eof())) {
        controlPanelServiceObjectPath = input.length() ? input.c_str() : defaultControlPanelServiceObjectPath;

        NotificationMessageType messageType = WARNING;
        NotificationText textToSend("en", "Something is wrong with this air conditioner!");
        vector<NotificationText> vecMessages;
        vecMessages.push_back(textToSend);
        Notification notification(messageType, vecMessages);
        notification.setControlPanelServiceObjectPath(controlPanelServiceObjectPath.c_str());

        status = notiSender->send(notification, 7200);
        if (status != ER_OK) {
            cout << "Notification was not sent successfully" << endl;
        } else {
            cout << "Notification sent successfully" << endl;
        }

        cout << "Enter in the ControlPanelService object path or press 'enter' to use default:" << endl;
        getline(cin, input);
    }

    cout << "Cleaning up in 10 seconds" << endl;
#ifdef _WIN32
    Sleep(10 * 1000);
#else
    sleep(10);
#endif

    if (s_restart) {
        s_restart = false;
        goto start;
    }

    return 0;
}