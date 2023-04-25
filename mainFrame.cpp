#include "mainFrame.hpp"
#include "maps.h"

MainFrame::MainFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title) {
  wxMenu *fileMenu = new wxMenu;
  wxMenu *helpMenu = new wxMenu;
  wxMenuBar *menuBar = new wxMenuBar();
  this->m_richText1 = new wxRichTextCtrl(
      this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 9999);

  fileMenu->Append(wxID_NEW, wxT("New File"), wxT("New file"));
  fileMenu->Append(wxID_OPEN, wxT("Open File"), wxT("Open a file"));
  fileMenu->Append(wxID_SAVE, wxT("Save\tCtrl-S"), wxT("Save File"));
  fileMenu->Append(wxID_SAVEAS, wxT("&Auto Save...\tF1"), wxT("AutoSave"));
  fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("Quit this program"));
  helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"), wxT("Show about dialog"));

  menuBar->Append(fileMenu, wxT("&File"));
  menuBar->Append(helpMenu, wxT("&Help"));

  SetMenuBar(menuBar);

  Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MainFrame::OnQuit, this, wxID_EXIT);
  Bind(wxEVT_MENU, &MainFrame::OnOpen, this, wxID_OPEN);
  Bind(wxEVT_MENU, &MainFrame::OnNew, this, wxID_NEW);
  Bind(wxEVT_MENU, &MainFrame::OnSave, this, wxID_SAVE);
  Bind(wxEVT_MENU, &MainFrame::ToggleAutoSave, this, wxID_SAVEAS);
  this->m_richText1->Connect(
      wxEVT_KEY_DOWN, wxKeyEventHandler(MainFrame::OnKeyDown), NULL, this);
  // this->m_richText1->Hide();
  this->m_richText1->SetEditable(false);
}

void MainFrame::OnQuit(wxCommandEvent &event) {
  if (wxMessageDialog(NULL, _("Do you really want to quit?"), _("Quit"),
                          wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION).ShowModal() == wxID_YES) {
                            Close(true);
  }
}

void MainFrame::OnAbout(wxCommandEvent &event) {
  wxString msg;
  msg.Printf(wxT("Hello and welcome to %s"), wxVERSION_STRING);
  wxMessageBox(msg, wxT("About Minimal"), wxOK | wxICON_INFORMATION, this);
}

void MainFrame::OnOpen(wxCommandEvent &event) {
  wxFileDialog *openFileDialog = new wxFileDialog(this);
  this->m_richText1->Clear();

  if (openFileDialog->ShowModal() == wxID_OK) {
    wxString fileName = openFileDialog->GetPath();
    std::string fname = fileName.ToStdString();

    this->fileName_ = fname;

    auto *fileEngine = new FileEngine(fname);

    // this->m_richText1->Show();
    this->m_richText1->SetEditable(true);

    this->m_richText1->AppendText(fileEngine->getFileData());

    delete fileEngine;
  }
}

void MainFrame::OnNew(wxCommandEvent &event) {
  // Pega o nome do arquivo
  wxTextEntryDialog *nameDialog = new wxTextEntryDialog(
      this, "File Name", wxGetTextFromUserPromptStr, wxEmptyString,
      wxTextEntryDialogStyle, wxDefaultPosition);
  nameDialog->ShowModal();
  std::string fileName = nameDialog->GetValue().ToStdString();

  // Pega o caminho do arquivo
  wxDirDialog *dirDialog = new wxDirDialog(
      this, wxDirSelectorPromptStr, wxEmptyString, wxDD_DEFAULT_STYLE,
      wxDefaultPosition, wxDefaultSize, wxDirDialogNameStr);
  dirDialog->ShowModal();
  std::string fileDir = dirDialog->GetPath().ToStdString();

  std::string completeFileName = fileDir + "/" + fileName;

  this->fileName_ = completeFileName;

  // Cria o arquivo de fato
  auto *fileEngine = new FileEngine(completeFileName);
  fileEngine->createFile();

  wxMessageBox("File Created Successfully", wxT("Success"),
               wxOK | wxICON_INFORMATION, this);

  this->m_richText1->Clear();
  // this->m_richText1->Show();
  this->m_richText1->SetEditable(true);
  this->m_richText1->AppendText(fileEngine->getFileData());
}

// Auto save and highlight functions entrypoint
// Este método ainda não está funcionando, ele só grava o ultimo caractere
// escrito
void MainFrame::OnKeyDown(wxKeyEvent &event) {
  if (this->autoSave) {
    std::string s = keyCodeMap.at(event.GetKeyCode());
    auto *fileEngine = new FileEngine(this->fileName_);
    fileEngine->saveFile(s);
  }
  event.Skip();
}

void MainFrame::OnSave(wxCommandEvent &event) {
  auto *fileEngine = new FileEngine(this->fileName_);
  std::string s = this->m_richText1->GetValue().ToStdString();
  fileEngine->saveFile(s);
}

void MainFrame::ToggleAutoSave(wxCommandEvent &event) {
  if (this->autoSave) {
    this->autoSave = false;
    wxMessageBox("Auto Save Disabled", wxT("Auto Save"),
                 wxOK | wxICON_INFORMATION, this);
  } else {
    this->autoSave = true;
    wxMessageBox("Auto Save Enabled", wxT("Auto Save"),
                 wxOK | wxICON_INFORMATION, this);
  }
}
