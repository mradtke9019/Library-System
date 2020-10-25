#pragma once
#include "wx/wx.h"
#include <string>
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

public:
	wxButton* m_btn1 = nullptr;
	wxTextCtrl* m_txt1 = nullptr;
	wxListBox *m_list1 = nullptr;
	//Sqlite* db = nullptr;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

