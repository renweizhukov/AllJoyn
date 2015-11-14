#pragma once

class CommandProcessor
{
private:
    struct CommandStringAndHelpInfo
    {
        const char* cmdStr;
        const char* helpInfo;
    };

    static const CommandStringAndHelpInfo sc_cmdStrAndHelpInfos[];
    std::unique_ptr<AllJoynContainer> m_allJoynContainer;

    void PrintHelpInfo();

public:
    CommandProcessor(void);
    ~CommandProcessor(void);

    void Run(void);
};