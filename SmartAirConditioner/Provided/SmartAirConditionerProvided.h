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

#include <qcc/platform.h>
#include <cstdio>
#include <alljoyn/controlpanel/CPSDate.h>
#include <alljoyn/controlpanel/CPSTime.h>

/**
 * Functions for SmartAirConditioner.xml
 */

/**
 * Functions for Properties
 */
const ajn::services::CPSDate& getCurrentDate();
void setCurrentDate(const ajn::services::CPSDate& dateValue);

const ajn::services::CPSTime& getCurrentTime();
void setCurrentTime(const ajn::services::CPSTime& timeValue);

const char* getOnOffString();
void setOnOffString(const char* strValue);

const char* getCurrentTempString();
void setCurrentTempString(const char* strValue);

int16_t getCurrentTemp();
void setCurrentTemp(int16_t currentTempValue);

uint16_t getCurrentHumidity();
void setCurrentHumidity(uint16_t currentHumidityValue);

uint16_t getAcMode();
void setAcMode(uint16_t acModeValue);

bool getTurboMode();
void setTurboMode(bool turboModeValue);

uint16_t getExpectedTemp();
void setExpectedTemp(uint16_t expectedTempValue);

/**
 * Functions for Actions
 */
void turnOnAc();
void turnOffAc();
void cancelTurnOffAc();