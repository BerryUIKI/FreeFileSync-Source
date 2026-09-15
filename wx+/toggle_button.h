// *****************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under    *
// * GNU General Public License: https://www.gnu.org/licenses/gpl-3.0          *
// * Copyright (C) Zenju (zenju AT freefilesync DOT org) - All Rights Reserved *
// *****************************************************************************
#pragma once

#include <wx/bmpbuttn.h>
#include <wx+/bitmap_button.h>

namespace zen
{
class ToggleButton : public wxBitmapButton
{
public:
    //wxBitmapButton constructor
    ToggleButton(wxWindow*          parent,
                 wxWindowID         id,
                 const wxBitmap&    bitmap,
                 const wxPoint&     pos = wxDefaultPosition,
                 const wxSize&      size = wxDefaultSize,
                 long               style = 0,
                 const wxValidator& validator = wxDefaultValidator,
                 const wxString&    name = wxASCII_STR(wxButtonNameStr)) :
        wxBitmapButton(parent, id, bitmap, pos, size, style, validator, name) {}

    //wxButton constructor
    ToggleButton(wxWindow*          parent,
                 wxWindowID         id,
                 const wxString&    label,
                 const wxPoint&     pos = wxDefaultPosition,
                 const wxSize&      size = wxDefaultSize,
                 long               style = 0,
                 const wxValidator& validator = wxDefaultValidator,
                 const wxString&    name = wxASCII_STR(wxButtonNameStr)) :
        wxBitmapButton(parent, id,
                       //(FreeFileSync_x86_64:77379): Gtk-CRITICAL **: 11:04:31.752: IA__gtk_widget_modify_style: assertion 'GTK_IS_WIDGET (widget)' failed
                       rectangleImage({1, 1}, *wxRED),
    pos, size, style, validator, name)
    {
        SetLabel(label);
    }

    void init(const wxImage& imgActive,
              const wxImage& imgInactive, int pad);

    void setActive(bool value);
    bool isActive() const { return active_; }
    void toggle()         { setActive(!active_); }

private:
    bool active_ = false;
    int pad_ = 0;
    wxImage imgActive_;
    wxImage imgInactive_;
};







//######################## implementation ########################
inline
void ToggleButton::init(const wxImage& imgActive,
                        const wxImage& imgInactive, int pad)
{
    imgActive_   = imgActive;
    imgInactive_ = imgInactive;
    pad_         = pad;

    //ensure both images have same size to avoid "wobble" effect when toggling button:
    const wxSize maxSize = getMaxSize(imgActive.GetSize(), imgInactive.GetSize());

    if (imgActive_  .GetSize() != maxSize) imgActive_   = resizeCanvas(imgActive_,   maxSize, wxALIGN_CENTER);
    if (imgInactive_.GetSize() != maxSize) imgInactive_ = resizeCanvas(imgInactive_, maxSize, wxALIGN_CENTER);

    active_ = !active_;
    setActive(!active_);
}


inline
void ToggleButton::setActive(bool value)
{
    if (active_ != value)
    {
        active_ = value;
        setButtonLabel(*this, active_ ? imgActive_ : imgInactive_, pad_);
    }
}
}
