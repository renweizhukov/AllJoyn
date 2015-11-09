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

// AboutClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MySessionListener.h"
#include "MyAboutListener.h"
#include "AboutClientCommands.h"
#include "AllJoynContainer.h"
#include "CommandProcessor.h"

using namespace std;
using namespace ajn;

int _tmain(int argc, _TCHAR* argv[])
{
    QCC_UNUSED(argc);
    QCC_UNUSED(argv);

    CommandProcessor cmdProcessor;
    cmdProcessor.Run();

    return 0;
}