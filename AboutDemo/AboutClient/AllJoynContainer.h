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