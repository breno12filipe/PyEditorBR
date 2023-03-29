#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>

class MainFrame : public wxFrame {
    public:
        MainFrame(const wxString& title);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //void showTxt(const wxString& txt);
};