#include "cMain.h"



// Define name of class it is handling events for and its base class
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Library System", wxPoint(30, 30), wxSize(800, 600))
{
	// Parent window is responsible of handling events for children
	m_btn1 = new wxButton(this, 10001, "Click me(Label)", wxPoint(10, 10), wxSize(150, 50));
	m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
	m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
	db = new Sqlite("C:\\Users\\mradt\\source\\repos\\Library-System\\Library-System\\Library.db");

}

cMain::~cMain()
{
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	auto books = db->Select<Books>("Books", "", Books::selectCallback);
	for (int i = 0; i < books->size(); i++)
	{
		std::string row = "";
		for (int j = 0; j < books->at(i)->Columns().size(); j++)
		{
			row += books->at(i)->Values().at(j) + " ";
		}
		m_list1->Append(row);
	}
	m_list1->Append(m_txt1->GetValue());

	evt.Skip();
}