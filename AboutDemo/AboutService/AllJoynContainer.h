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

#pragma once

enum class AllJoynContainerState
{
    Uninitialized,
    Initialized,
    Running
};

class AllJoynContainer
{
private:
    // The interface name should be the only thing required to find and form a
    // connection between the service and the client using the about feature.
    static const char* sc_interfaceName;
    static const ajn::SessionPort sc_assignedSessionPort;

    std::unique_ptr<ajn::BusAttachment> m_bus;
    std::unique_ptr<MySessionPortListener> m_sessionPortListener;
    std::unique_ptr<ajn::BusObject> m_busObject;

    std::unique_ptr<ajn::AboutData> m_aboutData;
    std::unique_ptr<ajn::AboutObj> m_aboutObj;

    AllJoynContainerState m_state;

    bool m_allJoynInited;
    bool m_allJoynRouterInited;
    bool m_allJoynApiCallProcessing;

    mutable std::mutex m_mut;
    std::condition_variable m_allJoynApiCallDone;

    void SetState(AllJoynContainerState nextState);

    void InitAboutDataAndObj(void);

public:
    AllJoynContainer(void);
    ~AllJoynContainer(void);

    void Init(void);
    void DeInit(void);

    void Start(void);
    void Stop(void);

    void SetAllJoynApiCallProcessing(bool allJoynApiCallProcessing);

    bool IsCommandValid(AboutServiceCommands command) const;
};