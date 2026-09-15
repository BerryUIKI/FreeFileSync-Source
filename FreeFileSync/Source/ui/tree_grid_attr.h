// *****************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under    *
// * GNU General Public License: https://www.gnu.org/licenses/gpl-3.0          *
// * Copyright (C) Zenju (zenju AT freefilesync DOT org) - All Rights Reserved *
// *****************************************************************************
#pragma once

#include <vector>
#include <cassert>
#include <wx+/dc.h>

namespace fff
{
enum class ColumnTypeOverview
{
    folder,
    itemCount,
    bytes,
};

struct ColumnAttribOverview
{
    ColumnTypeOverview type = ColumnTypeOverview::folder;
    int                offset  = 0;
    int                stretch = 0;
    bool               visible = false;
};


inline
std::vector<ColumnAttribOverview> getOverviewDefaultColAttribs()
{
    using namespace zen;
    return //harmonize with tree_view.cpp::onGridLabelContext() => expects stretched folder and non-stretched other columns!
    {
        {ColumnTypeOverview::folder,   - 2 * dipToWxsize(70), 1, true},
        {ColumnTypeOverview::itemCount, dipToWxsize(70), 0, true},
        {ColumnTypeOverview::bytes,     dipToWxsize(70), 0, true},
    };
}

const               bool overviewPanelShowPercentageDefault = true;
const ColumnTypeOverview overviewPanelLastSortColumnDefault = ColumnTypeOverview::bytes;

inline
bool getDefaultSortDirection(ColumnTypeOverview colType)
{
    switch (colType)
    {
        case ColumnTypeOverview::folder:
            return true;
        case ColumnTypeOverview::itemCount:
            return false;
        case ColumnTypeOverview::bytes:
            return false;
    }
    assert(false);
    return true;
}
}
