#pragma once

enum class AboutServiceCommands
{
    Min = 0,
    Init = Min,
    Start,
    Stop,
    Exit,
    Help,
    Max
};

AboutServiceCommands& operator++(AboutServiceCommands &cmd);
AboutServiceCommands operator++(AboutServiceCommands &cmd, int);

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}