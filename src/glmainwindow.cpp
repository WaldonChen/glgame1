#include "glmainwindow.h"
#include "glmaincanvas.h"

#include <iostream>

//(*InternalHeaders(GLMainWindow)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(GLMainWindow)
const long GLMainWindow::ID_STATUSBAR = wxNewId();
//*)

BEGIN_EVENT_TABLE(GLMainWindow,wxFrame)
//(*EventTable(GLMainWindow)
//*)
END_EVENT_TABLE()

GLMainWindow::GLMainWindow(wxWindow* parent,wxWindowID id,const wxPoint& pos,
                           const wxSize& size)
{
    //(*Initialize(GLMainWindow)
    Create(parent, id, _("GLMainWindow"), wxDefaultPosition, wxDefaultSize,
           wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX,
           _T("id"));
    SetClientSize(800, 600);
    Move(wxDefaultPosition);
    m_statusbar = new wxStatusBar(this, ID_STATUSBAR, 0, _T("ID_STATUSBAR"));
    int __wxStatusBarWidths[1] = { -1 };
    int __wxStatusBarStyles[1] = { wxSB_NORMAL };
    m_statusbar->SetFieldsCount(1, __wxStatusBarWidths);
    m_statusbar->SetStatusStyles(1, __wxStatusBarStyles);
    SetStatusBar(m_statusbar);
    //*)

    m_statusbar->SetStatusText(_T("Ready..."));

    int attriblist[] = {
        WX_GL_RGBA, WX_GL_MIN_RED, 1, WX_GL_MIN_GREEN, 1,
        WX_GL_MIN_BLUE, 1, WX_GL_DEPTH_SIZE, 1, WX_GL_DOUBLEBUFFER, 0
    };
    m_GLMainCanvas = new GLMainCanvas(this, wxID_ANY, attriblist, wxDefaultPosition,
                                      GetClientSize(), wxSUNKEN_BORDER);
    m_GLMainCanvas->Start();
}

GLMainWindow::~GLMainWindow()
{
    //(*Destroy(GLMainWindow)
    //*)
    delete m_GLMainCanvas;
}
