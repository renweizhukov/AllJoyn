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
#include "MySessionPortListener.h"
#include "MyBusObject.h"
#include "AboutServiceCommands.h"
#include "AllJoynContainer.h"
#include "CommandProcessor.h"

using namespace std;

const CommandProcessor::CommandStringAndHelpInfo CommandProcessor::sc_cmdStrAndHelpInfos[] = 
{
    { "init",  "init  -- Initialize the AllJoyn framework, bind the session port, create the Bus Object, the About Data, and the About Object." },
    { "start", "start -- Register the Bus object and announce the About object. Then this About Service is ready for accepting the API call." },
    { "stop",  "stop  -- Unannounce the About object and unregister the Bus object. Then this About Service can't accept any API call." },
    { "q"   ,  "q     -- Exit." },
    { "?"   ,  "?     -- Display the current available commands and their help info." }
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

        if (cmdStr == sc_cmdStrAndHelpInfos[static_cast<int>(AboutServiceCommands::Init)].cmdStr)
        {
            m_allJoynContainer->Init();
        }
        else if (cmdStr == sc_cmdStrAndHelpInfos[static_cast<int>(AboutServiceCommands::Start)].cmdStr)
        {
            m_allJoynContainer->Start();
        }
        else if (cmdStr == sc_cmdStrAndHelpInfos[static_cast<int>(AboutServiceCommands::Stop)].cmdStr)
        {
            m_allJoynContainer->Stop();
        }
        else if (cmdStr == sc_cmdStrAndHelpInfos[static_cast<int>(AboutServiceCommands::Help)].cmdStr)
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
    for (AboutServiceCommands command = AboutServiceCommands::Min; command < AboutServiceCommands::Max; ++command)
    {
        if (m_allJoynContainer->IsCommandValid(command))
        {
            cout << "\t " << sc_cmdStrAndHelpInfos[static_cast<int>(command)].helpInfo << endl;
        }
    }

    cout << endl;
}