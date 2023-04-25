#include "./fileEngine/fileEngine.hpp"
#include <iostream>
#include <wx/dirdlg.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/textdlg.h>
#include <wx/wx.h>
#include <wx/event.h>

class MainFrame : public wxFrame {
private:
  wxRichTextCtrl *m_richText1;
  bool autoSave = false;
  std::string fileName_;
  const char* GetVirtualKeyCodeName(int keycode);
  wxString GetKeyName(const wxKeyEvent &event);
public:
  MainFrame(const wxString &title);
  void OnQuit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnOpen(wxCommandEvent &event);
  void OnNew(wxCommandEvent &event);
  void OnSave(wxCommandEvent& event);
  void OnKeyDown(wxKeyEvent &event);
  void ToggleAutoSave(wxCommandEvent &event);
};