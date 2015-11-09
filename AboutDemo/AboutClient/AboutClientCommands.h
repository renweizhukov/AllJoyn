#pragma once

enum class AboutClientCommands
{
    Min = 0,
    Init = Min,
    Join,
    Call,
    Exit,
    Help,
    Max
};

AboutClientCommands& operator++(AboutClientCommands &cmd);
AboutClientCommands operator++(AboutClientCommands &cmd, int);

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}