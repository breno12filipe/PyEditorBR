#include "mainFrame.hpp"

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
    wxMenu *fileMenu = new wxMenu;

    wxMenu *helpMenu = new wxMenu;

    fileMenu->Append(wxID_NEW,  wxT("New File"),       wxT("New file"));
    fileMenu->Append(wxID_OPEN, wxT("Open File"),      wxT("Open a file"));
    fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"),   wxT("Quit this program"));

    helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"), wxT("Show about dialog"));

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));

    // wxButton* HelloWorld;
    // HelloWorld = new wxButton(this, wxID_ANY, _T("Hello World"), wxDefaultPosition, wxDefaultSize, 0);
    
    //wxRichTextCtrl* m_richText1;
    this->m_richText1 = new wxRichTextCtrl(this, wxID_ANY,wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);

    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnQuit,  this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::OnOpen,  this, wxID_OPEN);
    Bind(wxEVT_MENU, &MainFrame::OnNew,   this, wxID_NEW);
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

void MainFrame::OnOpen(wxCommandEvent& event) {
    wxFileDialog * openFileDialog = new wxFileDialog(this);
    this->m_richText1->Clear();

    if (openFileDialog->ShowModal() == wxID_OK){
        wxString fileName = openFileDialog->GetPath();
        std::string fname = fileName.ToStdString();

        auto *fileEngine = new FileEngine(fname);

        this->m_richText1->AppendText(fileEngine->getFileData());

        delete fileEngine;
    }
}

void MainFrame::OnNew(wxCommandEvent& event) {
    // Pega o nome do arquivo
    wxTextEntryDialog *nameDialog = new wxTextEntryDialog(this, "File Name", wxGetTextFromUserPromptStr, wxEmptyString, wxTextEntryDialogStyle, wxDefaultPosition);
    nameDialog->ShowModal();
    std::string fileName = nameDialog->GetValue().ToStdString();

    // Pega o caminho do arquivo
    wxDirDialog* dirDialog = new wxDirDialog(this, wxDirSelectorPromptStr,  wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, wxDirDialogNameStr);
    dirDialog->ShowModal();
    std::string fileDir = dirDialog->GetPath().ToStdString();

    std::string completeFileName = fileDir + "/" + fileName;

    // Cria o arquivo de fato
    auto *fileEngine = new FileEngine(completeFileName);
    fileEngine->createFile();

    wxMessageBox("File Created Successfully", wxT("Success"), wxOK | wxICON_INFORMATION, this);

    this->m_richText1->Clear();
    this->m_richText1->AppendText(fileEngine->getFileData());
}
