#include "mainFrame.hpp"

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
    wxMenu *fileMenu = new wxMenu;

    wxMenu *helpMenu = new wxMenu;

    helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"), wxT("Show about dialog"));

    fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));

    wxRichTextCtrl* m_richText1;
    m_richText1 = new wxRichTextCtrl( this, wxID_ANY,wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );

    //wxButton* HelloWorld;
    //HelloWorld = new wxButton(this, wxID_ANY, _T("Hello World"), wxDefaultPosition, wxDefaultSize, 0);

    //this->showTxt(m_richText1->GetValue());

    SetMenuBar(menuBar);

    //CreateStatusBar(2);
    //SetStatusText(wxT("Welcome to wxWidgets!"));

    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnQuit, this, wxID_EXIT);
}

void MainFrame::OnQuit(wxCommandEvent& event) {
    int dialog_return_value = wxNO;
    wxMessageDialog* dial = new wxMessageDialog(NULL, _("Do you really want to quit?"), _("Quit"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
    dialog_return_value = dial->ShowModal();
    switch(dialog_return_value) {
        case wxID_YES :
            Close(true);
            break;
        case wxID_NO :
            break;
    };
}

void MainFrame::OnAbout(wxCommandEvent& event) {
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, wxT("About Minimal"), wxOK | wxICON_INFORMATION, this);
}

// void MainFrame::showTxt(const wxString& txt) {
//     wxMessageBox(txt, wxT("About Minimal"));
// }
