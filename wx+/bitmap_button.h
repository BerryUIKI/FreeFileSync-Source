// *****************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under    *
// * GNU General Public License: https://www.gnu.org/licenses/gpl-3.0          *
// * Copyright (C) Zenju (zenju AT freefilesync DOT org) - All Rights Reserved *
// *****************************************************************************
#pragma once

#include <wx/bmpbuttn.h>
#include <wx/settings.h>
#include <wx/statbmp.h>
#include "image_tools.h"
#include "std_button_layout.h"
#include "dc.h"

namespace zen
{
//zen::BitmapTextButton is identical to wxBitmapButton, but preserves the label via SetLabel(), which wxFormbuilder would ditch!
class BitmapTextButton : public wxBitmapButton
{
public:
    BitmapTextButton(wxWindow* parent,
                     wxWindowID id,
                     const wxString& label,
                     const wxPoint& pos           = wxDefaultPosition,
                     const wxSize& size           = wxDefaultSize,
                     long style                   = 0,
                     const wxValidator& validator = wxDefaultValidator,
                     const wxString& name         = wxASCII_STR(wxButtonNameStr)) :
        wxBitmapButton(parent, id,
                       //(FreeFileSync_x86_64:77379): Gtk-CRITICAL **: 11:04:31.752: IA__gtk_widget_modify_style: assertion 'GTK_IS_WIDGET (widget)' failed
                       rectangleImage({1, 1}, *wxRED),
    pos, size, style, validator, name)
    {
        SetLabel(label);
    }
};

//wxButton::SetBitmap() also supports "image + text", but screws up proper gap and border handling
void setButtonLabel(wxAnyButton& btn, const wxImage& img, const wxString& text, int gap = dipToWxsize(5), int pad = dipToWxsize(5));
void setButtonLabel(wxAnyButton& btn, const wxImage& img,                                                 int pad = dipToWxsize(5));

//set bitmap label flicker free:
void setImage(wxStaticBitmap& staticBmp, const wxImage& img);

inline wxColor getColorToggleButtonBorder() { return {0x79, 0xbc, 0xed}; } //medium blue
inline wxColor getColorToggleButtonFill  () { return {0xcc, 0xe4, 0xf8}; } //light blue








//################################### implementation ###################################
inline
void setButtonLabel(wxAnyButton& btn, const wxImage& img, const wxString& text, int gap, int pad)
{
    assert(gap >= 0);
    gap = std::max(0, gap);

    wxImage imgTxt = createImageFromText(text, btn.GetFont(), btn.GetForegroundColour());
    if (img.IsOk())
        imgTxt = btn.GetLayoutDirection() != wxLayout_RightToLeft ?
                 stackImages(img, imgTxt, ImageStackLayout::horizontal, ImageStackAlignment::center, wxsizeToScreen(gap)) :
                 stackImages(imgTxt, img, ImageStackLayout::horizontal, ImageStackAlignment::center, wxsizeToScreen(gap));

    setButtonLabel(btn, imgTxt, pad);
}


inline
void setButtonLabel(wxAnyButton& btn, const wxImage& img, int pad)
{
    if (!img.IsOk())
    {
        btn.SetBitmapLabel   (wxNullBitmap);
        btn.SetBitmapDisabled(wxNullBitmap);
        return;
    }


    btn.SetBitmapLabel(toDpiScaledBitmap(img));

    //wxWidgets excels at screwing up consistently once again:
    //the first call to SetBitmapLabel() *implicitly* sets the disabled bitmap, too, subsequent calls, DON'T!
    btn.SetBitmapDisabled(toDpiScaledBitmap(img.ConvertToDisabled()));

    const int margin = 0;
    const int border = 1;
    //const int padding = 5;
    assert(pad >= 0);
    const int extra = margin + border + pad; //SetMinSize() relates to *outer* button size including margin + border + padding
    
    const int minBtnSize = wxButton::GetDefaultSize().GetHeight(); //buffered by wxWidgets

    wxSize minSize{std::max(screenToWxsize(img.GetWidth ()) + 2 * extra, minBtnSize /*[!] for width, too, avoid needless rectangle button*/),
                   std::max(screenToWxsize(img.GetHeight()) + 2 * extra, minBtnSize)};

    //SetMinSize() instead of SetSize() is needed for wxWidgets layout determination to work correctly
    btn.SetMinSize(minSize);
}


inline
void setImage(wxStaticBitmap& staticBmp, const wxImage& img)
{
    staticBmp.SetBitmap(toDpiScaledBitmap(img));
}



inline
wxImage generatePressedButtonBack(const wxSize& sz)
{
#if 1
    return rectangleImage(sz, wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW), {0x11, 0x79, 0xfe} /*light blue*/, dipToScreen(2));

#else //rectangle border with gradient as background
    wxBitmap bmp(wxsizeToScreen(sz.x),
                 wxsizeToScreen(sz.y)); //seems we don't need to pass 24-bit depth here even for high-contrast color schemes
    bmp.SetScaleFactor(getScreenDpiScale());
    {
        //draw rectangle border with gradient
        const wxColor colFrom = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE);
        const wxColor colTo(0x11, 0x79, 0xfe); //light blue

        wxMemoryDC dc(bmp);
        dc.SetPen(*wxTRANSPARENT_PEN); //wxTRANSPARENT_PEN is about 2x faster than redundantly drawing with col!

        wxRect rect(sz);

        const int borderSize = dipToWxsize(3);
        for (int i = 1 ; i <= borderSize; ++i)
        {
            const wxColor colGradient((colFrom.Red  () * (borderSize - i) + colTo.Red  () * i) / borderSize,
                                      (colFrom.Green() * (borderSize - i) + colTo.Green() * i) / borderSize,
                                      (colFrom.Blue () * (borderSize - i) + colTo.Blue () * i) / borderSize);
            dc.SetBrush(colGradient);
            dc.DrawRectangle(rect);
            rect.Deflate(dipToWxsize(1));
        }

        dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
        dc.DrawRectangle(rect);
    }
    wxImage img = bmp.ConvertToImage();
    convertToVanillaImage(img);
    return img;
#endif
}
}
