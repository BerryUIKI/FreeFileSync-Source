// *****************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under    *
// * GNU General Public License: https://www.gnu.org/licenses/gpl-3.0          *
// * Copyright (C) Zenju (zenju AT freefilesync DOT org) - All Rights Reserved *
// *****************************************************************************
#pragma once

#include <zen/zstring.h>

namespace fff
{
//------------------------------------------------------------------------------
//global program directories
//------------------------------------------------------------------------------
Zstring getResourceDirPath();
Zstring getConfigDirPath();
//------------------------------------------------------------------------------


Zstring getInstallDirPath();

Zstring getFreeFileSyncLauncherPath(); //throw FileError
//full path to application launcher C:\...\FreeFileSync.exe
}
