// *****************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under    *
// * GNU General Public License: https://www.gnu.org/licenses/gpl-3.0          *
// * Copyright (C) Zenju (zenju AT freefilesync DOT org) - All Rights Reserved *
// *****************************************************************************
#pragma once

#include <wx/log.h>
#include <wx/version.h>

#if !wxCHECK_VERSION(3, 3, 1)
class wxLogCollector : public wxLog
{
public:
    wxLogCollector() : m_logOrig(wxLog::SetActiveTarget(this))
    {
    }
    ~wxLogCollector() override
    {
        wxLog::SetActiveTarget(m_logOrig);
    }
    const wxString& GetMessages() const { return m_messages; }

    void Flush() override {} // Do not show any dialog

    wxLogCollector(const wxLogCollector&) = delete;
    wxLogCollector& operator=(const wxLogCollector&) = delete;

protected:
    void DoLogRecord(wxLogLevel, const wxString& msg, const wxLogRecordInfo&) override
    {
        if (!m_messages.empty())
            m_messages += '\n';
        m_messages += msg;
    }

    void DoLogText(const wxString& msg) override
    {
        if (!m_messages.empty())
            m_messages += '\n';
        m_messages += msg;
    }

private:
    wxString m_messages;
    wxLog* const m_logOrig;
};
#endif
