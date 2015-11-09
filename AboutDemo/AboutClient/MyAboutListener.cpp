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
#include "MySessionListener.h"
#include "MyAboutListener.h"
#include "AboutClientCommands.h"
#include "AllJoynContainer.h"

using namespace std;
using namespace ajn;

MyAboutListener::MyAboutListener(
    BusAttachment *pBus,
    AllJoynContainer *pAllJoynContainer,
    const char* interfaceName) : 
    m_pBus(pBus),
    m_allJoynContainer(pAllJoynContainer),
    m_interfaceName(interfaceName),
    m_sessionId(0)
{
    m_sessionListener.reset(new MySessionListener(this));
}

MyAboutListener::~MyAboutListener(void)
{

}

// Print out the fields found in the AboutData. Only fields with known signatures
// are printed out.  All others will be treated as an unknown field.
void MyAboutListener::printAboutData(
    AboutData& aboutData, 
    const char* language, 
    int tabNum)
{
    size_t count = aboutData.GetFields();

    unique_ptr<const char*[]> fields(new const char*[count]);
    aboutData.GetFields(fields.get(), count);

    for (size_t i = 0; i < count; ++i) 
    {
        cout << "[INFO]: ";

        for (int j = 0; j < tabNum; ++j) 
        {
            cout << "\t";
        }
        cout << "Key: " << fields[i];

        MsgArg* tmp = nullptr;
        aboutData.GetField(fields[i], tmp, language);
        cout << "\t";
        if (tmp->Signature() == "s") 
        {
            // This field is a string.
            const char* tmp_s = nullptr;
            tmp->Get("s", &tmp_s);
            cout << tmp_s;
        } 
        else if (tmp->Signature() == "as") 
        {
            // This field is an array of strings.
            size_t las = 0;
            MsgArg* as_arg = nullptr;
            tmp->Get("as", &las, &as_arg);
            for (size_t j = 0; j < las; ++j) 
            {
                const char* tmp_s = nullptr;
                as_arg[j].Get("s", &tmp_s);
                cout << tmp_s << " ";
            }
        } 
        else if (tmp->Signature() == "ay") 
        {
            // This field is an array of bytes.
            size_t lay = 0;
            uint8_t* pay = nullptr;
            tmp->Get("ay", &lay, &pay);
            for (size_t j = 0; j < lay; ++j) 
            {
                cout << "0x" << hex << setfill('0') << setw(2) << static_cast<unsigned int>(pay[j]) << " ";
            }
        } 
        else 
        {
            cout << "User Defined Value\tSignature: " << tmp->Signature().c_str();
        }

        cout << endl;
    }
}

void MyAboutListener::Announced(
    const char* busName, 
    uint16_t version, 
    ajn::SessionPort port, 
    const ajn::MsgArg& objectDescriptionArg, 
    const ajn::MsgArg& aboutDataArg)
{
    cout << "*********************************************************************************" << endl;
    cout << "[INFO]: Announce signal discovered." << endl;
    cout << "[INFO]: \tFrom bus " << busName << "." << endl;
    cout << "[INFO]: \tAbout version " << version << "." << endl;
    cout << "[INFO]: \tSessionPort " << port << "." << endl;

    AboutObjectDescription objectDescription(objectDescriptionArg);
    cout << "[INFO]: \tObjectDescription:" << endl;

    size_t cntPaths = objectDescription.GetPaths(nullptr, 0);
    unique_ptr<const char*[]> paths(new const char*[cntPaths]);

    objectDescription.GetPaths(paths.get(), cntPaths);
    for (size_t i = 0; i < cntPaths; ++i) 
    {
        cout << "[INFO]: \t\t" << paths[i] << endl;
        size_t cntIntfs = objectDescription.GetInterfaces(paths[i], nullptr, 0);
        
        unique_ptr<const char*[]> intfs(new const char*[cntIntfs]);
        objectDescription.GetInterfaces(paths[i], intfs.get(), cntIntfs);
        for (size_t j = 0; j < cntIntfs; ++j) 
        {
            cout << "[INFO]: \t\t\t" << intfs[j] << endl;
        }
    }
    
    cout << "[INFO]: \tAboutData:" << endl;
    AboutData aboutData(aboutDataArg);
    printAboutData(aboutData, nullptr, 2);
    cout << "*********************************************************************************" << endl;
    
    QStatus status = ER_OK;
    if (m_pBus != nullptr) 
    {
        SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
        m_pBus->EnableConcurrentCallbacks();

        status = m_pBus->JoinSession(busName, port, m_sessionListener.get(), m_sessionId, opts);
        cout << "[INFO]: SessionJoined sessionId = " << m_sessionId <<", status = 0x" 
            << hex << status << " = " << QCC_StatusText(status) << "." << endl;
        if ((status == ER_OK) && (m_sessionId != 0)) 
        {
            AboutProxy aboutProxy(*m_pBus, busName, m_sessionId);
            MsgArg objArg;

            aboutProxy.GetObjectDescription(objArg);
            cout << "*********************************************************************************" << endl;
            cout << "[INFO]: AboutProxy.GetObjectDescription:" << endl;

            AboutObjectDescription objectDescriptionProxy(objArg);
            size_t cntPathsProxy = objectDescriptionProxy.GetPaths(nullptr, 0);
            unique_ptr<const char*[]> pathsProxy(new const char*[cntPathsProxy]);
            objectDescriptionProxy.GetPaths(pathsProxy.get(), cntPathsProxy);
            for (size_t i = 0; i < cntPathsProxy; ++i) 
            {
                cout << "[INFO]: \t" << pathsProxy[i] << endl;
                size_t cntIntfsProxy = objectDescriptionProxy.GetInterfaces(pathsProxy[i], nullptr, 0);

                unique_ptr<const char*[]> intfsProxy(new const char*[cntIntfsProxy]);
                objectDescriptionProxy.GetInterfaces(pathsProxy[i], intfsProxy.get(), cntIntfsProxy);
                for (size_t j = 0; j < cntIntfsProxy; ++j) 
                {
                    cout << "[INFO]: \t\t" << intfsProxy[j] << endl;
                }
            }

            MsgArg aArg;
            aboutProxy.GetAboutData("en", aArg);
            cout << "*********************************************************************************" << endl;
            cout << "[INFO]: AboutProxy.GetAboutData: (Default Language)" << endl;
            AboutData aboutDataProxy(aArg);
            printAboutData(aboutDataProxy, nullptr, 1);

            size_t cntLangs = 0;
            cntLangs = aboutDataProxy.GetSupportedLanguages();
            // If the lang_num == 1, we only have a default language.
            if (cntLangs > 1) 
            {
                unique_ptr<const char*[]> langs(new const char*[cntLangs]);
                aboutDataProxy.GetSupportedLanguages(langs.get(), cntLangs);

                char* defaultLang = nullptr;
                aboutDataProxy.GetDefaultLanguage(&defaultLang);
                // Print out the AboutData for every language but the
                // default because it has already been printed.
                for (size_t i = 0; i < cntLangs; ++i) 
                {
                    if (strcmp(defaultLang, langs[i]) != 0) 
                    {
                        status = aboutProxy.GetAboutData(langs[i], aArg);
                        if (status == ER_OK) 
                        {
                            aboutDataProxy.CreatefromMsgArg(aArg, langs[i]);
                            cout << "[INFO]: AboutProxy.GetAboutData: (" << langs[i] << ")" << endl;
                            printAboutData(aboutDataProxy, langs[i], 1);
                        }
                    }
                }
            }

            uint16_t ver = 0;
            aboutProxy.GetVersion(ver);
            cout << "*********************************************************************************" << endl;
            cout << "[INFO]: AboutProxy.GetVersion " << ver << "." << endl;
            cout << "*********************************************************************************" << endl;

            const char* intfPath = nullptr;
            objectDescription.GetInterfacePaths(m_interfaceName.c_str(), &intfPath, 1);
            cout << "[INFO]: "<< intfPath << "/" << m_interfaceName << " is available for being called." << endl;

            unique_ptr<ProxyBusObject> proxyObject(new ProxyBusObject(*m_pBus, busName, intfPath, m_sessionId));
            m_allJoynContainer->SetProxyBusObject(proxyObject);
        }
    } 
    else 
    {
        cout << "[ERROR]: BusAttachment is NULL." << endl;
    }
}

void MyAboutListener::SessionLost(
    ajn::SessionId sessionId, 
    ajn::SessionListener::SessionLostReason reason)
{
    if (m_sessionId == sessionId)
    {
        m_allJoynContainer->Unjoin();
    }
}