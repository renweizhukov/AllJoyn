#include <cstdlib>

#include "DeviceCommands.h"
#include "ControllerSample.h"
#include "OffControlCommands.h"
#include "OnOffStatusCommands.h"
#include "WiFiOnOffStatusCommands.h"

DeviceCommands::DeviceCommands(ControllerSample* sample, DeviceInfoPtr& info)
: ControllerCommands(sample)
, m_sample(sample)
, m_deviceInfo(info)
{
    RegisterCommand(&DeviceCommands::OnCmdBack, "-b", "go to previous commands");
}

DeviceCommands::~DeviceCommands()
{
}

void DeviceCommands::Init()
{
    RegisterCommand(&DeviceCommands::OnCmdSelectInterface, "si", "select interface");
    PrintCommands();
}

void DeviceCommands::OnCmdSelectInterface(Commands* commands, std::string& cmd)
{
    ControllerSample* sample = static_cast<DeviceCommands*>(commands)->GetControllerSample();
    DeviceInfoPtr& info = static_cast<DeviceCommands*>(commands)->GetDeviceInfo();
    int order = 0;
    char buf[1024];
    std::map<int, std::string> indexKeyMap;

    size_t path_num = info->GetAboutObjectDescription().GetPaths(NULL, 0);
    const char** paths = new const char*[path_num];
    info->GetAboutObjectDescription().GetPaths(paths, path_num);

    for (size_t i = 0; i < path_num; ++i) {
        if (!strncmp(paths[i], "/About", strlen(paths[i]))) {
            continue;
        }

        cout << paths[i] << endl;
        size_t intf_num = info->GetAboutObjectDescription().GetInterfaces(paths[i], NULL, 0);
        const char** intfs = new const char*[intf_num];
        info->GetAboutObjectDescription().GetInterfaces(paths[i], intfs, intf_num);

        for (size_t j = 0; j < intf_num; ++j) {
            order++;
            cout << order << " : " << intfs[j] << endl;
            sprintf(buf, "%s:%s", paths[i], intfs[j]);
            std::string key(buf);

            if (!(sample->GetCurrentCommands()->GetChild(key))) {
                Commands* intfCommands = static_cast<DeviceCommands*>(commands)->CreateInterfaceCommands(commands, intfs[j], paths[i]);
                if (!intfCommands) {
                    cout << "Command object creation for interface " << intfs[j] << " is failed" << endl;
                    continue;
                }

                sample->GetCurrentCommands()->RegisterChildCommands(key, intfCommands);
            }
            indexKeyMap[order] = key;
        }
        delete [] intfs;
    }
    delete [] paths;

    int index = ReadIndex();
    Commands* selected = sample->GetCurrentCommands()->GetChild(indexKeyMap[index]);
    sample->PushCommands(selected);
}

Commands* DeviceCommands::CreateInterfaceCommands(Commands* commands, const char* intfName, const char* objectPath)
{
    Commands* intfCommands = NULL;

    ControllerSample* sample = static_cast<DeviceCommands*>(commands)->GetControllerSample();
    DeviceInfoPtr& info = static_cast<DeviceCommands*>(commands)->GetDeviceInfo();

    if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.OffControl", strlen(intfName))) {
        intfCommands = new OffControlCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "org.alljoyn.SmartSpaces.Operation.OnOffStatus", strlen(intfName))) {
        intfCommands = new OnOffStatusCommands(sample, info, objectPath);
    } else if (!strncmp(intfName, "com.smartconn.SmartToys.Operation.WiFiOnOffStatus", strlen(intfName))) {
        intfCommands = new WiFiOnOffStatusCommands(sample, info, objectPath);
    }
    return intfCommands;
}

void DeviceCommands::OnCmdBack(Commands* commands, std::string& cmd)
{
    ControllerCommands::OnCmdBack(commands, cmd);
    ControllerSample* sample = static_cast<ControllerCommands*>(commands)->GetControllerSample();
    sample->DropDeviceSession();
}
