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

#include "stdafx.h"
#include "MySessionListener.h"
#include "MyAboutListener.h"
#include "AboutClientCommands.h"
#include "AllJoynContainer.h"
#include "CommandProcessor.h"

using namespace std;

const CommandProcessor::CommandStringAndHelpInfo CommandProcessor::sc_cmdStrAndHelpInfos[] = 
{
    { "init", "init -- Initialize the AllJoyn framework and register the About Listener." },
    { "join", "join -- Join the session of a bus object which implements the desired interface. This is required before making the API call." },
    { "call", "call -- Make a call of the API defined by the desired interface." },
    { "q"   , "q    -- Exit." },
    { "?"   , "?    -- Display the current available commands and their help info." }
};

CommandProcessor::CommandProcessor(void)
{
    m_allJoynContainer.reset(new AllJoynContainer());
}

CommandProcessor::~CommandProcessor(void)
{

}

void CommandProcessor::Run(void)
{
    string cmdStr;

    while (cmdStr != "q")
    {
        cout << "Please input a command (type \"?\" for current available commands): ";
        cin >> cmdStr;
        transform(cmdStr.begin(), cmdStr.end(), cmdStr.begin(), ::tolower);

        if (cmdStr == sc_cmdStrAndHelpInfos[static_cast<int>(AboutClientCommands::Init)].cmdStr)
        {
            m_allJoynContainer->Init();
        }
        else if (cmdStr == sc_cmdStrAndHelpInfos[static_cast<int>(AboutClientCommands::Join)].cmdStr)
        {
            m_allJoynContainer->Join();
        }
        else if (cmdStr == sc_cmdStrAndHelpInfos[static_cast<int>(AboutClientCommands::Call)].cmdStr)
        {
            m_allJoynContainer->MakeCall();
        }
        else if (cmdStr == sc_cmdStrAndHelpInfos[static_cast<int>(AboutClientCommands::Help)].cmdStr)
        {
            PrintHelpInfo();
        }
    }

    // If AllJoynContainer is not initialized, then this DeInit will be an no-op.
    m_allJoynContainer->DeInit();
    m_allJoynContainer.reset();
}

void CommandProcessor::PrintHelpInfo()
{
    cout << "Current available commands are: " << endl;
    for (AboutClientCommands command = AboutClientCommands::Min; command < AboutClientCommands::Max; ++command)
    {
        if (m_allJoynContainer->IsCommandValid(command))
        {
            cout << "\t " << sc_cmdStrAndHelpInfos[static_cast<int>(command)].helpInfo << endl;
        }
    }

    cout << endl;
}