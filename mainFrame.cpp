#include "mainFrame.hpp"

MainFrame::MainFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title) {
  wxMenu *fileMenu = new wxMenu;
  wxMenu *helpMenu = new wxMenu;
  wxMenuBar *menuBar = new wxMenuBar();
  this->m_richText1 = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString,
                                         wxDefaultPosition, wxDefaultSize, 0);

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
  this->m_richText1->Hide();
}

void MainFrame::OnQuit(wxCommandEvent &event) {
  int dialog_return_value = wxNO;
  wxMessageDialog *dial =
      new wxMessageDialog(NULL, _("Do you really want to quit?"), _("Quit"),
                          wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
  dialog_return_value = dial->ShowModal();
  switch (dialog_return_value) {
  case wxID_YES:
    Close(true);
    break;
  case wxID_NO:
    break;
  };
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

    this->m_richText1->Show();

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
  this->m_richText1->Show();
  this->m_richText1->AppendText(fileEngine->getFileData());
}

// Auto save and highlight functions entrypoint
// Este método ainda não está funcionando, ele só grava o ultimo caractere escrito
void MainFrame::OnKeyDown(wxKeyEvent& event) {
    if (this->autoSave){
        std::string s = this->GetKeyName(event).ToStdString();
        auto *fileEngine = new FileEngine(this->fileName_);
        fileEngine->saveFile(s);
        event.Skip();
    }
}

void MainFrame::OnSave(wxCommandEvent& event) {
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

// helper function that returns textual description of wx virtual keycode
const char* MainFrame::GetVirtualKeyCodeName(int keycode) {
    switch ( keycode )
    {
#define WXK_(x) \
        case WXK_##x: return #x;

        WXK_(BACK)
        WXK_(TAB)
        WXK_(RETURN)
        WXK_(ESCAPE)
        WXK_(SPACE)
        WXK_(DELETE)
        WXK_(START)
        WXK_(LBUTTON)
        WXK_(RBUTTON)
        WXK_(CANCEL)
        WXK_(MBUTTON)
        WXK_(CLEAR)
        WXK_(SHIFT)
        WXK_(ALT)
        WXK_(CONTROL)
        WXK_(MENU)
        WXK_(PAUSE)
        WXK_(CAPITAL)
        WXK_(END)
        WXK_(HOME)
        WXK_(LEFT)
        WXK_(UP)
        WXK_(RIGHT)
        WXK_(DOWN)
        WXK_(SELECT)
        WXK_(PRINT)
        WXK_(EXECUTE)
        WXK_(SNAPSHOT)
        WXK_(INSERT)
        WXK_(HELP)
        WXK_(NUMPAD0)
        WXK_(NUMPAD1)
        WXK_(NUMPAD2)
        WXK_(NUMPAD3)
        WXK_(NUMPAD4)
        WXK_(NUMPAD5)
        WXK_(NUMPAD6)
        WXK_(NUMPAD7)
        WXK_(NUMPAD8)
        WXK_(NUMPAD9)
        WXK_(MULTIPLY)
        WXK_(ADD)
        WXK_(SEPARATOR)
        WXK_(SUBTRACT)
        WXK_(DECIMAL)
        WXK_(DIVIDE)
        WXK_(F1)
        WXK_(F2)
        WXK_(F3)
        WXK_(F4)
        WXK_(F5)
        WXK_(F6)
        WXK_(F7)
        WXK_(F8)
        WXK_(F9)
        WXK_(F10)
        WXK_(F11)
        WXK_(F12)
        WXK_(F13)
        WXK_(F14)
        WXK_(F15)
        WXK_(F16)
        WXK_(F17)
        WXK_(F18)
        WXK_(F19)
        WXK_(F20)
        WXK_(F21)
        WXK_(F22)
        WXK_(F23)
        WXK_(F24)
        WXK_(NUMLOCK)
        WXK_(SCROLL)
        WXK_(PAGEUP)
        WXK_(PAGEDOWN)
        WXK_(NUMPAD_SPACE)
        WXK_(NUMPAD_TAB)
        WXK_(NUMPAD_ENTER)
        WXK_(NUMPAD_F1)
        WXK_(NUMPAD_F2)
        WXK_(NUMPAD_F3)
        WXK_(NUMPAD_F4)
        WXK_(NUMPAD_HOME)
        WXK_(NUMPAD_LEFT)
        WXK_(NUMPAD_UP)
        WXK_(NUMPAD_RIGHT)
        WXK_(NUMPAD_DOWN)
        WXK_(NUMPAD_PAGEUP)
        WXK_(NUMPAD_PAGEDOWN)
        WXK_(NUMPAD_END)
        WXK_(NUMPAD_BEGIN)
        WXK_(NUMPAD_INSERT)
        WXK_(NUMPAD_DELETE)
        WXK_(NUMPAD_EQUAL)
        WXK_(NUMPAD_MULTIPLY)
        WXK_(NUMPAD_ADD)
        WXK_(NUMPAD_SEPARATOR)
        WXK_(NUMPAD_SUBTRACT)
        WXK_(NUMPAD_DECIMAL)
        WXK_(NUMPAD_DIVIDE)

        WXK_(WINDOWS_LEFT)
        WXK_(WINDOWS_RIGHT)
#ifdef __WXOSX__
        WXK_(RAW_CONTROL)
#endif
#undef WXK_

    default:
        return NULL;
    }
}

// helper function that returns textual description of key in the event
wxString MainFrame::GetKeyName(const wxKeyEvent &event)
{
    int keycode = event.GetKeyCode();
    const char* virt = GetVirtualKeyCodeName(keycode);
    if ( virt )
        return virt;
    if ( keycode > 0 && keycode < 32 )
        return wxString::Format("Ctrl-%c", (unsigned char)('A' + keycode - 1));
    if ( keycode >= 32 && keycode < 128 )
        return wxString::Format("'%c'", (unsigned char)keycode);

#if wxUSE_UNICODE
    int uc = event.GetUnicodeKey();
    if ( uc != WXK_NONE )
        return wxString::Format("'%c'", uc);
#endif

    return "unknown";
}
