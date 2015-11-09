#include "stdafx.h"
#include "AboutClientCommands.h"

// Special behavior for ++AboutClientCommands
AboutClientCommands& operator++(AboutClientCommands &cmd) 
{
    typedef std::underlying_type<AboutClientCommands>::type IntType;

    if (cmd == AboutClientCommands::Max)
    {
        cmd = AboutClientCommands::Min;
    }
    else
    {
        cmd = static_cast<AboutClientCommands>(static_cast<IntType>(cmd) + 1);
    }

    return cmd;
}

// Special behavior for AboutClientCommands++
AboutClientCommands operator++(AboutClientCommands &cmd, int) 
{
    AboutClientCommands result = cmd;
    ++cmd;
    return result;
}