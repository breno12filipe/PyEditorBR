#include "pyEditorBr.hpp"
#include "mainFrame.hpp"

IMPLEMENT_APP(PyEditorBr)

bool PyEditorBr::OnInit() {
    MainFrame *frame = new MainFrame(wxT("PyEditorBr 0.1"));
    frame->Show(true);
    return true;
}