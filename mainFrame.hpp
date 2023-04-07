#include <wx/wx.h>
#include <iostream>
#include <wx/richtext/richtextctrl.h>
#include "./fileEngine/fileEngine.hpp"

class MainFrame : public wxFrame {
    private:
        wxRichTextCtrl* m_richText1;
    public:
        MainFrame(const wxString& title);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnNew(wxCommandEvent& event);
        //void showTxt(const wxString& txt);
};