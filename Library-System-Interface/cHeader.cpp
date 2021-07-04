#include "cHeader.h"

//this, 10001, "Click me(Label)", wxPoint(10, 10), wxSize(150, 50)
//wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name
//wxWindow* parent, wxWindowID id, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = 0L, const wxValidator &validator = wxDefaultValidator, const wxString &name = wxControlNameStr
cHeader::cHeader(wxWindow* parent, wxWindowID id, const wxColor color, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
	: wxControl(parent, id, pos , size, style, validator , name)
{
	int btnWidth = 100;
	int btnHeight = this->GetSize().y / 3;
	int titleHeight = this->GetSize().y - 10;

	this->SetBackgroundColour(color);

	accountBtn = new wxButton(this, wxID_ANY, "Account", wxPoint(this->GetSize().x - (50 + btnWidth), centerOffset(btnHeight, this->GetSize().y)), wxSize(btnWidth, btnHeight));
	title = new wxRichTextCtrl(this, wxID_ANY, "New London Library System", wxPoint(centerOffset(400, this->GetSize().x), centerOffset(titleHeight, this->GetSize().y)), wxSize(400, titleHeight), wxTE_READONLY);
	title->SetFont(wxFont(wxFontInfo(30).Bold().Underlined()));
	title->SetBackgroundColour(color);
	//title->car
	//header = new wxHeaderCtrl();
	//wxRichTextCtrl()
}

cHeader::~cHeader()
{
}

	
int cHeader::centerOffset(int size, int containerSize)
{
	int x = (containerSize / 2) - (size / 2);
	return x;
}

