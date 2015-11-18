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
#include "AboutServiceCommands.h"

// Special behavior for ++AboutServiceCommands
AboutServiceCommands& operator++(AboutServiceCommands &cmd) 
{
    typedef std::underlying_type<AboutServiceCommands>::type IntType;

    if (cmd == AboutServiceCommands::Max)
    {
        cmd = AboutServiceCommands::Min;
    }
    else
    {
        cmd = static_cast<AboutServiceCommands>(static_cast<IntType>(cmd) + 1);
    }

    return cmd;
}

// Special behavior for AboutServiceCommands++
AboutServiceCommands operator++(AboutServiceCommands &cmd, int) 
{
    AboutServiceCommands result = cmd;
    ++cmd;
    return result;
}