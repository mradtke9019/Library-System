#pragma once
#include "wx/wx.h"
#include <wx/richtext/richtextctrl.h>
#include <wx/headerctrl.h>


class cHeader : public wxControl
{
public:
	cHeader();
	cHeader(wxWindow* parent, wxWindowID id, const wxColor color, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0L, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxControlNameStr);
	~cHeader();
	int centerOffset(int, int);

public:
	wxButton* accountBtn = nullptr;
	wxImage* icon = nullptr;
	wxRichTextCtrl * title = nullptr;
	wxFont* font = nullptr;
};

