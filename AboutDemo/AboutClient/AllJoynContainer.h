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
    Joined
};

class AllJoynContainer
{
private:
    // The interface name should be the only thing required to find and form a
    // connection between the service and the client using the about feature.
    static const char* sc_interfaceName;

    std::unique_ptr<ajn::BusAttachment> m_bus;
    std::unique_ptr<MyAboutListener> m_aboutListener;
    std::unique_ptr<ajn::ProxyBusObject> m_proxyBusObject;

    AllJoynContainerState m_state;

    bool m_allJoynInited;
    bool m_allJoynRouterInited;
    bool m_aboutListenerRegistered;

    mutable std::mutex m_mut;
    std::condition_variable m_proxyBusObjectSet;

    void SetState(AllJoynContainerState nextState);

public:
    AllJoynContainer(void);
    ~AllJoynContainer(void);

    void Init(void);
    void DeInit(void);

    void Join(void);
    void Unjoin(void);

    void SetProxyBusObject(std::unique_ptr<ajn::ProxyBusObject>& proxyBusObject);
    void MakeCall(void) const;

    bool IsCommandValid(AboutClientCommands command) const;
};