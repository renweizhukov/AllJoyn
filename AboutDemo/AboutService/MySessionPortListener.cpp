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

using namespace std;
using namespace ajn;

MySessionPortListener::MySessionPortListener(SessionPort sessionPort) :
    m_sessionPort(sessionPort)
{
}

MySessionPortListener::~MySessionPortListener(void)
{
}

bool MySessionPortListener::AcceptSessionJoiner(
    ajn::SessionPort sessionPort, 
    const char* joiner, 
    const ajn::SessionOpts& opts)
{
    QCC_UNUSED(joiner);
    QCC_UNUSED(opts);

    if (sessionPort == m_sessionPort) 
    {
        cout << "[INFO]: Accepting join attempt on the session port " << sessionPort << "." << endl;
        return true;
    }
    else
    {
        cout << "[ERROR]: Rejecting join attempt on unexpected session port " << sessionPort << "." << endl;
        return false;
    }
}

void MySessionPortListener::SessionJoined(
    SessionPort sessionPort, 
    SessionId id, 
    const char* joiner)
{
    QCC_UNUSED(sessionPort);
    QCC_UNUSED(joiner);

    cout << "[INFO]: Session Joined SessionId = " << id << "." << endl;
}