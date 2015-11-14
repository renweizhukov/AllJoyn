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