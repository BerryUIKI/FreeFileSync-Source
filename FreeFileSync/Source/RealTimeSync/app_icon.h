// *****************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under    *
// * GNU General Public License: https://www.gnu.org/licenses/gpl-3.0          *
// * Copyright (C) Zenju (zenju AT freefilesync DOT org) - All Rights Reserved *
// *****************************************************************************
#pragma once

#include <wx/icon.h>
#include <wx+/image_resources.h>

namespace zen
{
inline
wxIcon getRtsIcon() //see FFS/app_icon.h
{
    assert(loadImage("RealTimeSync").GetWidth () == loadImage("RealTimeSync").GetHeight() &&
           loadImage("RealTimeSync").GetWidth() == dipToScreen(128));
    wxIcon icon;
    icon.CopyFromBitmap(loadImage("RealTimeSync", dipToScreen(64)));
    return icon;

}
}
