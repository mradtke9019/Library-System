#pragma once
#include "wx/wx.h"
#include <string>
#include "cHeader.h"
#include "../Library-System/Books.h"
#include "../Library-System/Model.h"
#include "../Library-System/Sqlite.h"
#include "../Library-System/Authors.h"
#include <vector>
#include "../Library-System/Contributors.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	cMain(const wxString& title, const wxPoint& pos, const wxSize& size);

public:
	wxButton* m_btn1 = nullptr;
	wxTextCtrl* m_txt1 = nullptr;
	wxListBox *m_list1 = nullptr;
	cHeader* menu = nullptr;
	Sqlite* db = nullptr;

	void OnButtonClicked(wxCommandEvent& evt);

private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

enum
{
	ID_Hello = 1
};
