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

#include "SmartAirConditionerProvided.h"
#include "..\Generated\ControlPanelGenerated.h"
#include <qcc/String.h>

const uint16_t sleepTimeInMilliSeconds = 5000;

static ajn::services::CPSDate currDate(4, 12, 2015);
static ajn::services::CPSTime currTime(14, 41, 25);

const char* onState = "OnState";
const char* offState = "OffState";
static qcc::String onOffString = offState;

static int16_t currTemp = 32;
static uint16_t currHumidity = 0;

static uint16_t acMode = 175;
static bool turboMode = false;

static uint16_t expectedTemp = currTemp;

static bool isOn = false;


/**
 * Functions for SmartAirConditioner.xml
 */

/**
 * Functions for Properties
 */
const ajn::services::CPSDate& getCurrentDate()
{
    printf("[INFO] Get the current date = %2d/%2d/%4d.\n", currDate.getMonth(), currDate.getDay(), currDate.getYear());
    return currDate;
}

void setCurrentDate(const ajn::services::CPSDate& dateValue)
{
    printf("[INFO] Set the current date (= %2d/%2d/%4d) to %2d/%2d/%4d.\n", 
        currDate.getMonth(), currDate.getDay(), currDate.getYear(),
        dateValue.getMonth(), dateValue.getDay(), dateValue.getYear());
    currDate = dateValue;
}

const ajn::services::CPSTime& getCurrentTime()
{
    printf("[INFO] Get the current date = %2d:%2d:%2d.\n", currTime.getHour(), currTime.getMinute(), currTime.getSecond());
    return currTime;
}

void setCurrentTime(const ajn::services::CPSTime& timeValue)
{
    printf("[INFO] Set the current date (= %2d:%2d:%2d) to %2d:%2d:%2d.\n", 
        currTime.getHour(), currTime.getMinute(), currTime.getSecond(),
        timeValue.getHour(), timeValue.getMinute(), timeValue.getSecond());
    currTime = timeValue;
}

const char* getOnOffString()
{
    printf("[INFO] Get the On/Off string = %s.\n", onOffString.c_str());
    return onOffString.c_str();
}

void setOnOffString(const char* strValue)
{
    printf("[ERROR] onOffString is not writtable.\n");
}

int16_t getCurrentTemp()
{
    printf("[INFO] Get the current temperature = %d Fahrenheit.\n", currTemp);
    return currTemp;
}

void setCurrentTemp(int16_t currentTempValue)
{
    printf("[ERROR] currentTemp is not writtable.\n");
}

uint16_t getCurrentHumidity()
{
    printf("[INFO] Get the current humidity = %d%%.\n", currHumidity);
    return currHumidity;
}

void setCurrentHumidity(uint16_t currentHumidityValue)
{
    printf("[ERROR] currentHumidity is not writtable.\n");
}

uint16_t getAcMode()
{
    printf("[INFO] Get the AC mode = %d.\n", acMode);
    return acMode;
}

void setAcMode(uint16_t acModeValue)
{
    if (isOn)
    {
        if (acMode != acModeValue)
        {
            printf("[INFO] Set the AC mode (= %d) to %d.\n", acMode, acModeValue);
            acMode = acModeValue;
        }
        else
        {
            printf("[WARNING] The AC mode is already %d.\n", acModeValue);
        }
    }
    else
    {
        printf("[ERROR] Please turn on the AC before setting the AC mode.\n");
    }
}

bool getTurboMode()
{
    printf("[INFO] Get the turbo mode = %d.\n", turboMode);
    return turboMode;
}

void setTurboMode(bool turboModeValue)
{
    if (isOn)
    {
        if (turboMode != turboModeValue)
        {
            printf("[INFO] Set the turbo mode (= %d) to %d.\n", turboMode, turboModeValue);
            turboMode = turboModeValue;
        }
        else
        {
            printf("[WARNING] The turbo mode is already %d.\n", turboModeValue);
        }
    }
    else
    {
        printf("[ERROR] Please turn on the AC before setting the turbo mode.\n");
    }
}

uint16_t getExpectedTemp()
{
    printf("[INFO] Get the expected temperature = %d.\n", expectedTemp);
    return expectedTemp;
}

void setExpectedTemp(uint16_t expectedTempValue)
{
    if (isOn)
    {
        if (expectedTemp != expectedTempValue)
        {
            printf("[INFO] Set the expected temperature (= %d) to %d.\n", expectedTemp, expectedTempValue);
            expectedTemp = expectedTempValue;
            
            if (currTemp != expectedTemp)
            {
                printf("[INFO] Wait for %d seconds for the change of the current temperature.\n", sleepTimeInMilliSeconds/1000);
                Sleep(sleepTimeInMilliSeconds);
                currTemp = expectedTemp;
            }
            else
            {
                printf("[INFO] The expected temperature is the same as the current temperature, so the current temperature is not changed.\n");
            }
        }
        else
        {
            printf("[WARNING] The expected temperature is already %d.\n", expectedTempValue);
        }
    }
    else
    {
        printf("[ERROR] Please turn on the AC before setting the expected temperature.\n");
    }
}


/**
 * Functions for Actions
 */
void turnOnAc()
{
    if (!isOn)
    {
        printf("[INFO] Turning on the AC.\n");
        printf("[INFO] Wait for %d seconds for the AC to be on.\n", sleepTimeInMilliSeconds/1000);
        Sleep(sleepTimeInMilliSeconds);
        isOn = true;
        onOffString = onState;
        printf("[INFO] AC is on.\n");

        ControlPanelGenerated::smartAirConditionerOnOffStringProperty->SendValueChangedSignal();
    }
    else
    {
        printf("[WARNING] AC is already on.\n");
    }
}

void turnOffAc()
{
    if (isOn)
    {
        printf("[INFO] Turning off the AC.\n");
        printf("[INFO] Wait for %d seconds for the AC to be off.\n", sleepTimeInMilliSeconds/1000);
        Sleep(sleepTimeInMilliSeconds);
        isOn = false;
        onOffString = offState;
        printf("[INFO] AC is off.\n");
    }
    else
    {
        printf("[WARNING] AC is already off.\n");
    }
}

void cancelTurnOffAc()
{
    printf("[INFO] Cancel turning off the AC.\n");
}