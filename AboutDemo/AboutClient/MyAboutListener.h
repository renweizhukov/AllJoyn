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

class MyAboutListener : public ajn::AboutListener
{
private:
    ajn::BusAttachment *m_pBus;
    const std::string m_interfaceName;
    std::unique_ptr<MySessionListener> m_sessionListener;

    void printAboutData(
        ajn::AboutData& aboutData, 
        const char* language, 
        int tabNum);

public:
    MyAboutListener(
        ajn::BusAttachment *pBus,
        const char* interfaceName);
    ~MyAboutListener(void);

    void Announced(
        const char* busName, 
        uint16_t version, 
        ajn::SessionPort port, 
        const ajn::MsgArg& objectDescriptionArg, 
        const ajn::MsgArg& aboutDataArg);
};