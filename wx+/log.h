// *****************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under    *
// * GNU General Public License: https://www.gnu.org/licenses/gpl-3.0          *
// * Copyright (C) Zenju (zenju AT freefilesync DOT org) - All Rights Reserved *
// *****************************************************************************
#pragma once

#include <wx/log.h>
#include <wx/version.h>

#if !wxCHECK_VERSION(3, 3, 1)
class wxLogCollector
{
    class Formatter : public wxLogFormatter
    {
        wxString Format(wxLogLevel, const wxString& msg, const wxLogRecordInfo&) const override { return msg; }
    };

public:
    wxLogCollector() : m_logOrig{wxLog::SetActiveTarget(&m_logBuf)}
    {
        delete m_logBuf.SetFormatter(new Formatter{});
    }
    ~wxLogCollector()
    {
        m_logBuf.Clear();
        wxLog::SetActiveTarget(m_logOrig);
    }
    const wxString& GetMessages() const { return m_logBuf.GetBuffer(); }

    wxLogCollector(const wxLogCollector&) = delete;
    wxLogCollector& operator=(const wxLogCollector&) = delete;

private:
    wxLogBuffer m_logBuf;
    wxLog* const m_logOrig;
};
#endif
