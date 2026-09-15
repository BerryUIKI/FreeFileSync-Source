// *****************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under    *
// * GNU General Public License: https://www.gnu.org/licenses/gpl-3.0          *
// * Copyright (C) Zenju (zenju AT freefilesync DOT org) - All Rights Reserved *
// *****************************************************************************
#pragma once

#include <wx/string.h>
#include "config.h"

namespace rts
{
enum class CancelReason
{
    requestGui,
    requestExit
};
CancelReason runFolderMonitor(const FfsRealConfig& config, const wxString& jobname); //jobname may be empty
}
